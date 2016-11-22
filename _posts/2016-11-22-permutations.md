---
layout: post
title: Permutations
published: true
---

In this post, I will talk about a common approach for generating all permutations, its complexity, and how big the argument list can be that makes the stack overflow using OCaml. I borrow some pictures and work from [typeocaml](http://typeocaml.com/2015/05/05/permutation/).

## The insert-into-all-positions solution

Let assume that we have a set of all permutations for a set of 3 elements (thus totally there are 6 permutations). For example, let 3 elements are [1;2;3], then 6 permutations should be [1;2;3], [2;1;3], [2;3;1], [1;3;2], [3;1;2], [3;2;1].

So now what if we put a new element, say 4, into the set of 4 elements [1;2;3;4]? What we need to do is combining the new element 4 into the previous set of permutations to generate a new set of permutations.

Let's see how a new element is inserted into a permutation. Consider a permutation of 3 elements [1;2;3], there are 4 possible positions (before 1, 2, 3, and after 3) to insert 4 as shown in the figure.

[<img src="{{ site.baseurl }}/images/permutations_1.jpg" alt="Insert a new element" style="width: 400px;"/>]({{ site.baseurl }}/)



