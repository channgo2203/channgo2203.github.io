---
layout:     post
title:      Additional Functions for Lists
date:       2016-05-23
summary:    Additional Functions for Lists in Standard Library.
categories: OCaml
thumbnail: cogs
tags:
 - lists
 - standard library
 - algorithm
 - OCaml
 - programming
---

In this post, I will propose the implementation of some extra functions for data structure 
list in OCaml. The functionality is self-defined in the [source code][1].

```ocaml
(******************************************************)
(*                                                                        
 *		Listplus                                                                                                    
 *                                                                        
 *		Copyright 2016 Van-Chan Ngo.                                        
 *                                                                        
 *)                                                                        
(******************************************************)

(** This module provides some extra useful functions for OCaml list. *)

val last : 'a list -> 'a option 
(** Return the last element of the given list. *)

val biggest_prefix : 'a list -> 'a list
(** Return the prefix without the last element of the given list. 
	For example, [biggest_prefix [1;2;3]] = [[1;2]].
*)

val truncate : 'a -> 'a list -> 'a list
(** [truncate a l] truncates list [l] from the first occurrence of [a]. 
	Return [l] if [a] is not found in [l]. 
*)
	
val catenate : 'a list -> 'a list -> 'a list
(** Catenate two lists. *)
	
val prefixes : 'a list -> 'a list list
(** Return a list of all prefixes of the given list in increasing order of length. 
	For example, [prefixes [1;2;3]] = [[[];[1];[1;2];[1;2;3]]].
*)
	  
val suffixes : 'a list -> 'a list list
(** Return a list of all suffixes of the given list in decreasing order of length. 
	For example, [suffixes [1;2;3]] = [[[1;2;3];[2,3];[3],[]]].
*)

val print : 'a list -> ('a -> string) -> unit
(** Print the list content to standard stdout. *)

val print_pre_suffixes : 'a list list -> ('a -> string) -> unit
(** Print the prefixes or suffixes of a list to standard stdout. *)

let rec last l = 
  match l with 
  | [] -> None
  | [x] -> Some x
  | _::t -> last t
	
let biggest_prefix l = 
  let rec bpre_aux xs ys = match xs with 
  | [] -> ys
  | [x] -> ys
  | h::t -> bpre_aux t (h::ys)
  in
  List.rev (bpre_aux l [])
	
let rec truncate a l = 
  match l with 
  | [] -> []
  | h::t -> 
  if (h = a) then t
  else truncate a t

let rec catenate l1 l2 = 
  match l1 with 
  | [] -> l2
  | h::t -> h::(catenate t l2)

let prefixes l = 
  let rec pre_aux xs ys = match xs with 
  | [] -> ys
  | h::t -> let bpre = biggest_prefix xs in pre_aux bpre (bpre::ys)
  in pre_aux l [l]

let rec suffixes l = 
  match l with 
  | [] -> [ [] ]
  | h::t -> l::(suffixes t)

let print l f = 
  let rec print_aux al printfunction = match al with 
  | [] -> ()
  | h::t -> print_string (" " ^ (printfunction h)); print_aux t printfunction
  in
  print_string "["; print_aux l f; print_string " ]"

let print_pre_suffixes l f = 
  let rec print_aux al printfunction = match al with
  | [] -> ()
  | h::t ->  print_string " "; print h printfunction; print_aux t printfunction
  in
  print_string "["; print_aux l f; print_string " ]"
```

[1]: https://github.com/channgo2203/Functional-Data-Structures/tree/master/List


