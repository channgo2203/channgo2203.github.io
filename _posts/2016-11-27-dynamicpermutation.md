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

{% highlight html linenos %}
<figure>
  <img src="/images/image-filename-1.jpg">
  <figcaption>Caption describing these two images.</figcaption>
</figure>
{% endhighlight %}