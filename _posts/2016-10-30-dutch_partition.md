---
layout:     post
title:      Dutch Partition
date:       2016-10-30
excerpt:    Dutch partition problem implementation in OCaml.
categories: [Programming]
tags:
 - Dutch partition
 - algorithm
 - OCaml
 - programming
comments: true
---

This post describes the implementation of the __Dutch partition__ problem using OCaml 
such that the memory space complexity is constant.

## Description
The Dutch partition arises when we want to optimize the quick sort: given
an array `A` whose elements are comparable and an index `i` of an element in the
array. Reorder the array such that the initial elements are smaller than `A[i]`,
and are followed by elements that equal to `A[i]`, the final elements are bigger
than `A[i]`, using constant memory space complexity $$O(1)$$.

I implement the problem using OCaml. The main idea is the use of 3 flags to  determine
the 3 regions above.
* `A[0 .. smaller-1]` : smaller region
* `A[smaller .. equivalent-1]` : equivalent region
* `A[equivalent .. larger]` : unclassified region
* `A[larger+1 .. size-1]`: larger region

The "smaller" and "equivalent" flags are initialized 0 and "larger" is
initialized `(size - 1)`. That means at the beginning the whole array is
unclassified. We use a recursive function to reduce the number of
elements in unclassified region is 0.  

## Code
The [source code][1] is given as follows.

```ocaml
let swap i j a =
  try
    let tmp = a.(j) in
    a.(j) <- a.(i);
    a.(i) <- tmp; a
  with
    _ -> raise (Invalid_argument "out-of-range")
               
(* auxiliary function *)
(* a[0 .. smaller - 1] : smaller region
   a[smaller .. equivalent - 1] : equivalent region
   a[equivalent .. larger] : unclassified region
   a[larger + 1 ... size - 1] : larger region
 *)
let rec partition smaller equivalent larger pivot a =
  if equivalent <= larger then
    begin
      try
        if a.(equivalent) < pivot then
          (* put a.(equivalent) to the smaller region *)
          partition (smaller+1) (equivalent+1) larger pivot (swap smaller equivalent a)
        else
          if a.(equivalent) = pivot then
            (* move to the next element in the unclassified region *)
            partition smaller (equivalent+1) larger pivot a
          else
            (* move a.(equivalent) to the larger region *)
            partition smaller equivalent (larger-1) pivot (swap equivalent larger a)
      with
        _ -> raise (Invalid_argument "out-of-range")
    end
  else
    a

let dutch_partition pivot_index a =
  try
    partition 0 0 (pred (Array.length a)) (a.(pivot_index)) a
  with
    _ -> raise (Invalid_argument "out-of-range")

open Printf               
(* test *)               
let _ =
  Array.iter (printf "%d; ") (dutch_partition 3 [|0;1;9;9;9;9;2;3;4;5;6;7;8;9;10;11;12;13;14;15;16;17;18;19|])
```

[1]: https://gist.github.com/channgo2203/e432f08220a7c0f9bc8827f141c45124#file-dutch_partition-ml
