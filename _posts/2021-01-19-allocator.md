---
layout:     post
title:      Memory Management with std::allocator in C++
date:       2021-01-19
excerpt:    How to manage memory with std::allocator in C++
categories: [Tutorials, C/C++, Real-time Embedded Programming]
tags:
 - tutorials
 - programming
 - C++ standard library
 - real-time embedded
comments: true
---

In this post, I will talk about memory management with `std::allocator` in C++

## Introduction

As we know all the STL containers in C++ have an `Allocator` as a type parameter which is `std::allocator` by default. 
Underlying, it uses the `new` and `delete` operators to allocate and deallocate memory.

By definition, allocators are objects responsible for encapsulating memory management. It is useful when we want to `separate memory allocation and object construction in two steps and separate deallocation and object destruction in two steps as well`.

So what does this mean? For example, consider the following code:

```cpp
std::vector<int>* vPtr = new std::vector<int>[3];
```

With `new` operator, it forces us to allocate and construct all objects, `3` integer values, at the same time. Let's say we only want to allocate (or preserve) `3` integer size memory areas and construct these integer values later, for instance we only want to construct the first integer value. `std::allocator` can help us to do that.

## Allocators

The allocator is responsible for managing raw memory storage and also for constructing and  destroying allocated objects in two seperated steps. Its declaration is:

```cpp
template <class T> class allocator;
```


