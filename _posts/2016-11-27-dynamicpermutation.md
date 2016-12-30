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
(************************************)
(*          Permutation             *)
(*          Van Chan Ngo            *)
(************************************)

(** Permutation over ordered types *)

type order = Lt
           | Eq
           | Gt

type direction = L
               | R
               
module type ComparedType =
  sig
    type t
           (** the type of the elements. *)
    val compare : t -> t -> order
    val to_string : t -> string
  end

module type Permutation =
  sig
    type element
           (** the type of the elements. *)
    type permutation
           (** the type of a permutation. *)
    val empty : unit -> permutation
           (** empty permutation. *)
    val is_empty : permutation -> bool
    val of_list : element list -> permutation
    val stream_permutation : permutation -> permutation Stream.t
    val to_string : permutation -> string
  end

module Int : ComparedType with type t = int

module Make (El : ComparedType) : Permutation with type element = El.t
```

```ocaml
type order = Lt
           | Eq
           | Gt

type direction = L
               | R
               
module type ComparedType =
  sig
    type t
           (** the type of the elements. *)
    val compare : t -> t -> order
    val to_string : t -> string
  end

module type Permutation =
  sig
    type element
           (** the type of the elements. *)
    type permutation
           (** the type of a permutation. *)
    val empty : unit -> permutation
           (** empty permutation. *)
    val is_empty : permutation -> bool
    val of_list : element list -> permutation
    val stream_permutation : permutation -> permutation Stream.t
    val to_string : permutation -> string
  end

module Int =
  struct
    type t = int
    let to_string x = string_of_int x
    let compare x y =
      if x > y then
        Gt
      else if x < y then
        Lt
      else
        Eq
  end
  
module Make (El : ComparedType) =
  struct
    type element = El.t

    type permutation = element list

    let empty () = []

    let is_empty p =
      match p with
      | [] -> true
      | _ -> false

    let of_list l = l

    let to_string p =
      List.fold_left (fun acc x -> acc ^ " " ^ (El.to_string x)) "" p

    let stream_permutation p =
      let attach_direction a =
        Array.map (fun x -> (x, L)) a
      in

      let swap a i j =
        let tmp = a.(j) in
        a.(j) <- a.(i);
        a.(i) <- tmp
      in

      let is_movable a i =
        let x, d = a.(i) in

        match d with
        | L ->
           begin
             if i > 0 then
               match El.compare x (fst a.(i-1)) with
               | Gt -> true
               | _ -> false
             else
               false
           end
             
        | R ->
           begin
             if i < Array.length a - 1 then
               match El.compare x (fst a.(i+1)) with
               | Gt -> true
               | _ -> false
             else
               false
           end
      in
      
    let move a i =
      let x, d = a.(i) in
      if is_movable a i then
        match d with
        | L -> swap a i (i-1)
        | R -> swap a i (i+1)
      else
        failwith "not movable"
    in

    let scan_movable_largest a =
      let rec aux acc i =
        if i >= Array.length a then
          acc
        else if not (is_movable a i) then
          aux acc (i+1)
        else
          let x, _ = a.(i) in
          match acc with
          | None -> aux (Some i) (i+1)
          | Some j ->
             match El.compare x (fst a.(j)) with
             | Lt -> aux acc (i+1)
             | _ -> aux (Some i) (i+1)
      in
      aux None 0
    in

    let flip d =
      match d with
      | L -> R
      | R -> L
    in

    let scan_flip_larger x a =
      Array.iteri (fun i (y, d) ->
          match El.compare y x with
          | Gt -> a.(i) <- (y, flip d)
          | _ -> ())
                  a
    in

    let permutations_generator l =
      let a = Array.of_list l |> attach_direction in
      let r = ref (Some l) in
      let next () =
        let p = !r in
        (match scan_movable_largest a with (* find the largest movable *)
         | None -> r := None (* no more permutations *)
         | Some i ->
            let x, _ = a.(i) in
            (
              move a i; (* move *)
              scan_flip_larger x a; (* after move, scan to flip *)
              r := Some (Array.map fst a |> Array.to_list)
            )
        );
        p
      in
      next
    in

    let generator = permutations_generator p in
    Stream.from (fun _ -> generator ())
                        
  end
```

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
