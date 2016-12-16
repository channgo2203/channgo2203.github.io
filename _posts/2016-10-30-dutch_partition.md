---
layout: post-no-feature
title: Dutch Partition
comments: true
---

This post describes the implementation of the "Dutch partition" problem using OCaml such that the memory space complexity is constant.

## Description
The Dutch partition arises when we want to optimize the quick sort: given
an array A whose elements are comparable and an index i of an element in the
array. Reorder the array such that the initial elements are smaller than A[i],
and are followed by elements that equal to A[i], the final elements are bigger
than A[i], using constant memory space complexity O(1).

I implement the problem using OCaml. The main idea is the use of 3 flags to  determine
the 3 regions above.

- A[0 .. smaller-1] : smaller region
- A[smaller .. equivalent-1] : equivalent region
- A[equivalent .. larger] : unclassified region
- A[larger+1 .. size-1]: larger region

The "smaller" and "equivalent" flags are initialized 0 and "larger" is
initialized (size - 1). That means at the beginning the whole array is
unclassified. We use a recursive function to reduce the number of
elements in unclassified region is 0.  

## Code
The source code can be obtained at <script src="https://gist.github.com/channgo2203/e432f08220a7c0f9bc8827f141c45124.js"></script>
