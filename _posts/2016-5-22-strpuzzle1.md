---
layout: post
title: Find a Shortest Substring Contains the Given Strings
published: true
---

Given a string str and a list of strings lstr. Find a shortest substring of str that 
contains all strings in a list of strings lstr. 

For example, given str = “this is a test string this a” and lstr = [“is”; "this"; "a"], then the output string is “this a”.

### Simple Solution

- Generate all substrings of str
- For each substring, check that it contains all strings in lstr
- Print out the smallest one

### Complexity

The complexity depends on the number of substrings which is \\(O(n^2)\\), where \\(n\\) is the length of str (since the number of substring with the length \\(m\\) is \\((n - m) + 1)\\). If finding each substring is \\(O(n)\\). Then, the complexity is \\(O(n^3).\\) 

### Efficient Solution

- Find the first occurence of a substring of str containing all strings in lstr
- If there exists one, called substr, then store its length as the indices of the its first and last characters in str in a list. 
- Create a new string from str from the index of the character after the first character of substr,called str1. If it is empty, return the list. Otherwise find the first occurence of a substring of str1 that contains all strings in lstr
- Repeat the steps above

### Complexity

The complexity is \\(nm\\) where \\(m\\) is number of substrings containing all strings in lstr such that its leftmost and rightmost substrings are strings in lstr, and \\(n\\) is the length of str. In the worst-case, it is \\(O(n^2)\\) when str is string of same characters and lstr is list of this single character strings. 

In the following, I show how to implement the algorithm above in the functional language OCaml. First, we define some utilities functions. 
{% highlight ocaml %}
(* 
 * find substring sub in string str forward from pos 
 *)
let find_sub str pos sub = 
	let r = Str.regexp_string sub in
	Str.search_forward r str pos 

(* 
 * find substring sub in string str backward from pos 
 *)
let rfind_sub str pos sub = 
	let r = Str.regexp_string sub in
	Str.search_backward r str pos 

(*
 * get the substring from findex to lindex inclding characters at findex and lindex
 *)
let get_substring str findex lindex = 
	try 
		let sub = String.sub str findex (lindex - findex + 1) in
		Some sub
	with 
		Invalid_argument e -> None

{% endhighlight %}
