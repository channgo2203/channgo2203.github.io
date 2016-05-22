---
layout: post
title: Find a Shortest Substring Contains the Given Strings
published: true
---

Given a string str and a list of strings lstr. Find a shortest substring of str that 
contains all strings in a list of strings lstr. 

For Example,
str : “this is a test string this a”
lstr : “is”; "this"; "a"
Output string: “this a”

1. Simple solution

- Generate all substrings of str
- For each substring, check that it contains all strings in lstr
- Print out the smallest one

Complexity: depend on the number of substrings which is O(n^2), where n is the length of 
str (since the number of substring with the length m is (n - m) + 1), then if finding each 
substring is O(n), the complexity is O(n^3)
