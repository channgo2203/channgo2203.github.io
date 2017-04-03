---
layout: post
title: Constant-time List Truncation Implementation in OCaml
date: 2017-03-01T00:00:00.000Z
excerpt: An example of constant-time implementation for truncating a list in OCaml.
categories:
  - Programming/OCaml/Security/Side-channel Attacks
tags:
  - security
  - side-channel attacks
  - OCaml
  - functional programming
published: true
comments: true
---
In this post, I want to demonstrate how a side channel can happen in functional programming. Interested readers can know more about side channel leakage [here][1]. Assume that we want to implement a function named `truncate` which takes two arguments: an integer value and an integer list. It will return the sublist of the input list from the first occurrence of the input value to the end of the list.

Consider the following implementation of `truncate`. Let's assume futher that any evaluation of conditional in the `if` expression takes `1` time unit and the evaluation of `nil` value also takes `1` time unit. We can call these parameters a `cost model`. Then it is obvious that the implementation is not `constant` provided that the length of the input list is fixed.

```ocaml
let rec truncate a l =
match l with
 | [] -> []
 | x::xs -> if (x = a) then 
              xs 
            else 
              truncate a xs
```

[1]: https://en.wikipedia.org/wiki/Side-channel_attack