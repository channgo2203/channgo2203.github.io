---
layout: post
title: Reactive and Synchronous Reactive Programming
published: true
---

The term _reactive system_ was introduced by David Harel and Amir Pnueli to distingish it from _transformational system_. For example, a compiler and usual programs are considered as transformational systems since they will be terminated and compute outputs from the initial inputs. While an operating system is a reactive system, in which it communicates continously with its environment. However, the communication is determined by the own speed of the operating system and it can synchronize with its environments, for instance when users press a menu from the operatiing system interface, who need to wait until the OS completes the task relating to this menu to see the next screen. The users cannot make the next menu appear at the speed they want. We call this class of reactive systems _interactive systems_. 

_Synchronous reactive system_ is an instance of of reactive system. It is different from the interactive systems in the sense that it interacts with its environment at the speed of the environment, meaning that the environment cannot wait. Typical examples are cyber physical systems, real-time safety-critical embedded systems (e.g., nuclear reactors, fly by wire systems).

In general, reactive systems can be implemented by a single infinite loop, in which two schemes are used as follows.

<script src="https://gist.github.com/channgo2203/c4b008f5f80966d72b0f08a0d1476032.js"></script>

