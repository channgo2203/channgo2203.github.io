---
layout: post
title: Constant-time List Copy Implementation in OCaml
date: 2017-03-01
excerpt: An example of constant-time implementation for copying a sub-list in OCaml.
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

```ocaml
let copy l len index =
let rec aux lin len index pos lout =
match lin with
 | [] -> lout
 | x::xs -> if (pos >= index) && (pos < index + len) then 
              aux xs len index (pos+1) (x::lout) 
            else lout
in List.rev (aux l len index 0 [])
```
