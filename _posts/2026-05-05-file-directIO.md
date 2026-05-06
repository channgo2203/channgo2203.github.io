---
layout:     post
title:      File Copy using DirectIO 
date:       2026-06-06
excerpt:    Linux Kernel Virtual Memory DirectIO
categories: [Research, Embedded Linux, Linux Kernel, Programming]
tags:
 - research
 - embedded linux
 - linux kernel
 - programming
comments: true
---

## Concepts

- Direct I/O transfers data directly between the storage device and the application buffer, bypassing the OS page cache entirely. This avoids the double copy of data, reducing CPU overhead and preventing page cache pollution due to read-aheads, but requires the application to carefully manage aligned buffers.

- When using O_DIRECT, the Linux kernel requires that every write operation is a multiple of the device's logical block size (typically 512 or 4096 bytes).
If your file size isn't a perfect multiple of this size, you must "over-write" the final block with padded data and then use ftruncate to remove the extra bytes. 

## Key Logic Steps

- Padding Calculation: When `bytes_read` is not a multiple of ALIGNMENT, the code calculates a larger `write_size` that satisfies the kernel's requirements.

- Zero-Padding: It is critical to memset the extra space in your aligned buffer to 0 so you don't leak random memory data into your file.

- Final Truncation: After closing the O_DIRECT file descriptor, we use `truncate` (or `ftruncate` on a non-direct handle) to strip away those extra padding bytes, ensuring the destination file is an identical byte-for-byte copy. 


```C
#define _GNU_SOURCE
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <cstring>
#include <sys/stat.h>
#include <algorithm>

int main() {
    const char* src_path = "source.bin";
    const char* dest_path = "flash_dest.bin";
    const size_t CHUNK_SIZE = 1024 * 1024; // 1MB
    const size_t ALIGNMENT = 4096;         // Use 4096 for modern flash/NVMe

    int src_fd = open(src_path, O_RDONLY | O_DIRECT);
    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC | O_DIRECT, 0644);

    struct stat st;
    fstat(src_fd, &st);
    size_t total_original_size = st.st_size;

    void* buffer = nullptr;
    posix_memalign(&buffer, ALIGNMENT, CHUNK_SIZE);

    ssize_t bytes_read;
    size_t total_written = 0;

    while ((bytes_read = read(src_fd, buffer, CHUNK_SIZE)) > 0) {
        size_t write_size = bytes_read;

        // Check if this is the last, unaligned chunk
        if (write_size % ALIGNMENT != 0) {
            // Round UP to the next alignment boundary
            write_size = ((write_size / ALIGNMENT) + 1) * ALIGNMENT;
            
            // Clear the padding area in the buffer to avoid writing garbage
            std::memset((char*)buffer + bytes_read, 0, write_size - bytes_read);
        }

        if (write(dest_fd, buffer, write_size) < 0) {
            perror("Aligned write failed");
            break;
        }

        total_written += write_size;
    }

    // Clean up buffer and close O_DIRECT handle
    free(buffer);
    close(src_fd);
    close(dest_fd);

    // IMPORTANT: Remove the padding bytes to restore the original file size
    // Note: ftruncate can be called on the path or a new non-O_DIRECT descriptor
    if (truncate(dest_path, total_original_size) == 0) {
        std::cout << "Transfer complete. Final size: " << total_original_size << " bytes." << std::endl;
    } else {
        perror("Truncate failed");
    }

    return 0;
}
```
