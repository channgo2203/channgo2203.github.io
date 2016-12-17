---
layout: post-no-feature
title: "Shortest Substring Contains a List of Strings"
description: "Given a string str and a list of strings lstr. Find a shortest substring of str that 
contains all strings in a list of strings lstr."
category: articles
tags: [shortest string, OCaml]
comments: true
---

For example, given str = “this is a test string this a” and lstr = [“is”; "this"; "a"], then the output string is “this a”.

### Simple Solution

- Generate all substrings of str.
- For each substring, check that it contains all strings in lstr.
- Print out the smallest one.

### Complexity

The complexity depends on the number of substrings which is \\(O(n^2)\\), where \\(n\\) is the length of str (since the number of substring with the length \\(m\\) is \\((n - m) + 1)\\). If finding each substring is \\(O(n)\\). Then, the complexity is \\(O(n^3).\\) 

### Efficient Solution

- Find the first occurence of a substring of str containing all strings in lstr.
- If there exists one, called substr, then store its length as the indices of its first and last characters in str in a list. 
- Create a new string from str from the index of the character after the first character of substr,called str1. If it is empty, return the list. Otherwise find the first occurence of a substring of str1 that contains all strings in lstr. Compare its length with the store value in the list, if it is smaller or equal, then add the string indices in the list.
- Repeat the steps above.

### Complexity

The complexity is \\(nm\\) where \\(m\\) is number of substrings containing all strings in lstr such that its leftmost and rightmost substrings are strings in lstr, and \\(n\\) is the length of str. In the worst-case, it is \\(O(n^2)\\) when str is string of same characters and lstr is list of this single character strings. 

In the following, I show how to implement the algorithm above in the functional language OCaml. All other utility functions can be 
downloaded on my [Github](https://github.com/channgo2203/puzzleset/tree/master/string/prob1). 
<script src="https://gist.github.com/channgo2203/be41cd8837f6f28dd0c1417842af8933.js"></script>