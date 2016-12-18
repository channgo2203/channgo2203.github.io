---
layout:     post
title:      Dynamic Permutation
date:       2016-11-27
summary:    Dynamic permutation implementation in OCaml.
categories: Programming
thumbnail: cogs
tags:
 - dynamic permutation
 - permutation
 - OCaml
 - programming
---

In the [previous post][1], I analyzed a common 
recursive implementation of permutation generation. Due to its $$n!$$ complexity, a stack 
overflow will occurs soon with the number of elements is beyon 9.

To overcome this, one technique is to generate a different permutation at a time, 
in which the complexity of this one permutation generation is linear. I show how this 
technique can be implemented using OCaml with the 
[Johnson Trotter algorithm][2]. 

[1]: http://channgo2203.github.io/permutations
[2]: https://en.wikipedia.org/wiki/Steinhaus–Johnson–Trotter_algorithm