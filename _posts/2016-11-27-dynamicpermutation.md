---
layout: post
title: Dynamic Permutation
date: 2016-11-27
summary: Dynamic permutation implementation in OCaml.
categories: Programming
thumbnail: cogs
tags:
  - dynamic permutation
  - permutation
  - OCaml
  - programming
published: true
---

In the [previous post][1], I analyzed a common 
recursive implementation of permutation generation. Due to its $$n!$$ complexity, a stack 
overflow will occurs soon with the number of elements is beyon 9.

To overcome this, one technique is to generate a different permutation at a time, 
in which the complexity of this one permutation generation is linear. I show how this 
technique can be implemented using OCaml with the 
[Johnson Trotter algorithm][2]. 

To make the implementation generic, I implement a functor which generates a 
Permutation module given a user-provided comparable type. For example, lets say 
I want to generate permutations over a list of pairs of integer values. I could with 
the functor to create a Permutation module over integer pairs. However it is possible 
to do permutation over any other value types as long as you provide an impplementation 
of that type.

```ocaml
module IntPair =
  struct
    type t = int * int

    let to_string x =
      let (x1,x2) = x in
      "(" ^ (string_of_int x1) ^ "," ^ (string_of_int x2) ^ ")"

    let compare (x1,y1) (x2,y2) =
      if x1 > x2 then
        Gt
      else if x1 < x2 then
        Lt
      else
        begin
          if y1 > y2 then
            Gt
          else if y1 < y2 then
            Lt
          else
            Eq
        end
  end
module P = Permutation.Make(IntPair)
```

[1]: http://channgo2203.github.io/programming/2016/11/22/permutation/
[2]: https://en.wikipedia.org/wiki/Steinhaus–Johnson–Trotter_algorithm
