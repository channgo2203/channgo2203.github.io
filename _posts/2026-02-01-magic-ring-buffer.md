---
layout:     post
title:      Magic Ring Buffer
date:       2026-02-01
excerpt:    Linux Kernel Virtual Memory
categories: [Research, Embedded Linux, Linux Kernel, Programming]
tags:
 - research
 - embedded linux
 - linux kernel
 - programming
comments: true
---

A "Magic Ring Buffer" uses virtual memory mirroring to treat a circular buffer as a single, contiguous linear array. This eliminates the need for manual wrap-around logic.

Compared to a normal ring buffer, it provides several performance advantages: 

- Single memcpy instead of two: In a standard ring buffer, if a data write spans the end of the buffer, you must perform two separate memcpy operations—one to the end and one back at the start. With mirroring, you perform one continuous memcpy because the "overflow" region automatically points back to the physical start.

- Elimination of Branching Logic: Normal buffers require manual checks (if-statements or modulo operations) to detect and handle wrap-around. By removing these branches, you reduce CPU cycles and avoid potential branch mispredictions that slow down execution.

- Zero-Copy with External APIs: Many high-performance APIs (like those for network I/O or audio processing) expect a pointer to a single, contiguous block of memory. Without a magic ring buffer, you would have to copy non-contiguous "wrapped" data into a temporary linear buffer first. The magic ring buffer allows these APIs to read or write directly into the buffer in one go.

- Simplified Index Management: While you still track head and tail pointers, you can let them advance past the buffer's "official" end without immediate wrapping logic. This simplifies the math needed to calculate available space or data length.

## Memory Mirroring

To set up the mirrored map, a same physical memory is mapped to two adjacent virtual address regions.

```c
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct {
    uint8_t *buffer;    // Base virtual address
    size_t size;        // MUST be multiple of page size
    size_t head;        // Write offset
    size_t tail;        // Read offset
} MagicRingBuffer;

// Initialization (Linux/POSIX example)
void init_buffer(MagicRingBuffer *rb, size_t size) {
    int fd = memfd_create("ring_buffer", 0); // Create anonymous file, initially managed by the kernel using physical memory pages RAM
    ftruncate(fd, size);

    // Reserve 2x virtual space
    rb->buffer = mmap(NULL, 2 * size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    
    // Map same physical memory twice, back-to-back
    mmap(rb->buffer, size, PROT_REAuuD|PROT_WRITE, MAP_SHARED|MAP_FIXED, fd, 0);
    mmap(rb->buffer + size, size, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_FIXED, fd, 0);
    
    rb->size = size;
    rb->head = rb->tail = 0;
    close(fd);
}
```

## Buffer Operations

The code does not need to have wrap-around logic, e.g., avoid the implementation of modulo, because the hardware handles the wrap. This is why the buffer size must be a 
multiple of the system page size (usually 4KB)

```c
void write_data(MagicRingBuffer *rb, const void *data, size_t len) {
    // Linear copy: If writing past rb->size, it automatically 
    // appears at the start of the first mapping.
    memcpy(rb->buffer + rb->head, data, len);
    rb->head = (rb->head + len) % rb->size;
}

void read_data(MagicRingBuffer *rb, void *dest, size_t len) {
    // Linear read: Even if 'len' crosses the 'size' boundary, 
    // the mirror mapping makes it look contiguous.
    memcpy(dest, rb->buffer + rb->tail, len);
    rb->tail = (rb->tail + len) % rb->size;
}
```
