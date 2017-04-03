---
layout: post
title: Constant-time List Truncation Implementation in OCaml
date: {}
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

Consider the following implementation of `truncate`. Let's assume futher that any evaluation of conditional in the `if` expression takes `1` time unit and the evaluation of `nil` value also takes `1` time unit. We can call these parameters a `cost model`. Then it is obvious that the implementation is not `constant` provided that the length of the input list is fixed. Because the execution time of the implementation depends on the position of the first element in the list which is equal to input value. For example, `truncate 3 [1;2;3;4;5;6]` consumes `3` time units, while `truncate 3 [1;2;4;5;6;3]` takes `6` time units to complete. 

```ocaml
let rec truncate a l =
match l with
 | [] -> []
 | x::xs -> if (x = a) then 
              xs 
            else 
              truncate a xs
```

Assume that there is an attacker who cannot see the content of the input list and the output of the function. But she can see the input value, the length of the input list, and she can measure the execution time of the function. 

> Does she know exactly the position of the first occurrence of the input value in the list? 

The answer is `yes` if we assume that the attacker can distinguish the execution time in terms of one time unit. Otherwise, she can at least know the input value is in the list or not if the measurement is not very fine-grained.

[1]: https://en.wikipedia.org/wiki/Side-channel_attack
