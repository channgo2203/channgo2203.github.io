---
layout:     post
title:      Linux Kernel Virtual Memory
date:       2024-11-17
excerpt:    Linux Kernel Virtual Memory
categories: [Research, Embedded Linux, Linux Kernel, Programming]
tags:
 - research
 - embedded linux
 - linux kernel
 - programming
comments: true
---

Linux, like many modern operating systems, employs virtual memory to provide an abstraction layer 
between the physical memory and the processes running on the system.

This allows processes to operate as if they have exclusive access to a large, contiguous memory 
space, even though the physical memory is limited and shared among multiple processes.

## Concepts

### Virtual Address Space

Each process has its own virtual address space, a large, contiguous range of addresses that the 
process can use to access memory.

### Physical Memory

The actual physical RAM and swap space on disk.

### Page Table

A [data structure][1] that maps virtual addresses to physical addresses.

### Page Fault

Occurs when a process tries to access a virtual memory page that is not currently mapped to physical memory.

### Page Allocation

Manages the allocation and deallocation of physical memory pages.

### Page Table Management

Handles the creation, modification, and deletion of page tables.

### Memory Mapping

Maps files and devices into the process's virtual address space.

### Swapping

Handles the swapping of pages between physical memory and disk.
By effectively managing virtual memory, the Linux kernel ensures efficient memory utilization, 
process isolation, and overall system stability.

## How it works

### Process Creation

When a process is created, the kernel allocates a virtual address space for it.

### Memory Access

When a process tries to access a memory location, the MMU (Memory Management Unit) translates the 
virtual address into a physical address using the page table.

### Page Fault Handling

If the page is not present in physical memory, a `page fault` occurs. The kernel then:
- Finds a free page in physical memory or swaps out an existing page to disk.
- Loads the required page from disk or another process's memory.
- Updates the page table to map the virtual address to the physical address.
- Restarts the instruction that caused the page fault.

## Benefits

### Isolation

Processes are isolated from each other, preventing one process from corrupting the memory of another.

### Efficient Memory Utilization

Physical memory can be shared among multiple processes, reducing memory fragmentation.

### Demand Paging

Only the necessary pages are loaded into physical memory, saving memory and improving performance.

### Memory Protection

The kernel can protect certain memory regions from being accessed by unauthorized processes.

## Example of Page Allocation and Fault

The following program in `C` demonstrates Linux lazy allocation for user space programs and page fault.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>

#define BUFFER_SIZE (1024 * 1024) // 1MB

void print_pgfaults(void)
{
    int ret;
    struct rusage usage;
    ret = getrusage(RUSAGE_SELF, &usage);
    if (ret == -1) {
        perror("getrusage");
    } else {
        printf ("Major page faults %ld\n", usage.ru_majflt);
        printf ("Minor page faults %ld\n", usage.ru_minflt);
    }
}

int main (int argc, char *argv[])
{
    unsigned char *p;
    printf("Initial state\n");
    print_pgfaults();
    p = malloc(BUFFER_SIZE);
    printf("After malloc\n");
    print_pgfaults();
    memset(p, 0x42, BUFFER_SIZE);
    printf("After memset\n");
    print_pgfaults();
    memset(p, 0x42, BUFFER_SIZE);
    printf("After 2nd memset\n");
    print_pgfaults();
    return 0;
}
```

When you run it, you will see something like this:

```shell
Initial state
Major page faults 0
Minor page faults 172
After malloc
Major page faults 0
Minor page faults 186
After memset
Major page faults 0
Minor page faults 442
After 2nd memset
Major page faults 0
Minor page faults 442
```

The important part is the increase when filling the memory with data: `442 - 186 = 256`. 
The buffer is `1MB`, which is `256` pages (`4KB` size), or there were `256 page faults`. 
The second call to `memset` makes no difference because all the pages are now mapped.

[1]: https://en.wikipedia.org/wiki/Page_table
