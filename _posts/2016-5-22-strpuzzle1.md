---
layout: post
title: Find a Shortest Substring Contains the Given Strings
published: true
---

Given a string str and a list of strings lstr. Find a shortest substring of str that 
contains all strings in a list of strings lstr. 

For example, given str = “this is a test string this a” and lstr = [“is”; "this"; "a"], then the output string is “this a”.

1. Simple Solution

- Generate all substrings of str
- For each substring, check that it contains all strings in lstr
- Print out the smallest one

2. Complexity 

The complexity depends on the number of substrings which is \\(O(n^2)\\), where \\(n\\) is the length of str (since the number of substring with the length \\(m\\) is \\((n - m) + 1)\\), then if finding each substring is \\(O(n)\\). Hence, the complexity is \\(O(n^3).\\) 
