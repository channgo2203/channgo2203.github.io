---
layout: post
title: Dynamic Permutation
category: articles
tag: [dynamic permutation, OCaml]
comments: true
---

In the [previous post](http://channgo2203.github.io/permutations), I analyzed a common 
recursive implementation of permutation generation. Due to its n! complexity, a stack 
overflow will occurs soon with the number of elements is beyon 9.

To overcome this, one technique is to generate a different permutation at a time, 
in which the complexity of this one permutation generation is linear. I show how this 
technique can be implemented using OCaml with the 
[Johnson Trotter algorithm](https://en.wikipedia.org/wiki/Steinhaus–Johnson–Trotter_algorithm). 

{% highlight ocaml linenos %}
let insert_all_positions x l = 
let rec aux prev acc l = 
match l with
| [] -> (prev @ [x]) :: acc |> List.rev
| hd::tl as l -> aux (prev @ [hd]) ((prev @ [x] @ l) :: acc) tl 
in aux [] [] l;;


let rec permutation l = 
match l with 
| [] -> []
| hd::[] -> [[hd]]
| hd::tl -> List.fold_left (fun acc p -> acc @ insert_all_positions hd p) [] (permutation tl);;
{% endhighlight %}