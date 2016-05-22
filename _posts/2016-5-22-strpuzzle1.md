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

In the following, I show how to implement the algorithm above in the functional language OCaml. All other utility functions can be 
downloaded on Github at 

{% highlight ocaml %}
(*
 * find the shortest substring that containing all strings in the list
 * str : the string for searching
 * lstr : list of searching strings
 * n : the number of substrings containing all strings in lstr
 * lshortest_substr : return a list of (findex,lindex) indicate the locations of shortest substrings containing all strings in the lstr
 *)
let rec find_shortest_substrings_aux n lshortest_substr str lstr offset = 
  if (String.is_empty str) then
    (n, lshortest_substr)
  else
    begin
      (* find forward a substring containing the strings in lstr *)
      let substr_index = sub_lstr str lstr in 
      if (substr_index = (-1, -1)) then 
        (* not found return the result *)
        (n, lshortest_substr)
      else 
        (* updated lshortest_substr an find the next substring from fi + 1 to the end of str *)
        let fi, li = substr_index in 
        find_shortest_substrings_aux (n + 1) (update_lshortest_substr lshortest_substr (fi + offset, li + offset)) (String.sub str (fi + 1) (String.length str - (fi + 1))) lstr (offset + fi + 1)
    end

let find_shortest_substrings str list_strings = 
  (* remove all empty strings in the lstr *)
  let lstr_tmp = List.filter list_strings (fun x -> not (String.is_empty x)) in 
  (* remove all duplicate strings in lstr_tmp *)
  let lstr = List.dedup ~compare:(compare) lstr_tmp in 
  if (List.is_empty lstr) then 
    (-1, [(0,-1)]) (* empty string *)
  else if (String.is_empty str) then
   (0, [(-1,-1)])
  else
    begin
      (* find the first occurrence of substring containing the strings in lstr *)
      let substr_index = sub_lstr str lstr in 
        if (substr_index = (-1,-1)) then 
          (0, [(-1,-1)])
        else 
          begin
            let fi, li = substr_index in 
            let (n, lshortest_substr) = find_shortest_substrings_aux 1 [substr_index] (String.sub str (fi + 1) (String.length str - (fi + 1))) lstr (fi + 1) in 
            (* remove all duplicates before return *)
            (n, List.dedup ~compare:(index_compare) lshortest_substr)
          end
    end		
{% endhighlight %}