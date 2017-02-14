---
layout:     post
title:      Reactive and Synchronous Reactive Programming
date:       2016-06-01
excerpt:    Reactive and synchronous reactive programming.
categories: [Research]
tags:
 - research
 - synchronous program
 - Signal
 - Lustre
 - Esterel
comments: true
---

The term __reactive system__ was introduced by David Harel and Amir Pnueli to distingish 
it from __transformational system__. For example, a compiler and usual programs are 
considered as transformational systems since they will be terminated and compute outputs 
from the initial inputs. While an operating system is a reactive system, in which it 
communicates continously with its environment. However, the communication is determined 
by the own speed of the operating system and it can synchronize with its environments, 
for instance when users press a menu from the operatiing system interface, who need to 
wait until the OS completes the task relating to this menu to see the next screen. The 
users cannot make the next menu appear at the speed they want. We call this class of 
reactive systems __interactive systems__. 

__Synchronous reactive system__ is an instance of of reactive system. It is different 
from the interactive systems in the sense that it interacts with its environment at the 
speed of the environment, meaning that the environment cannot wait. Typical examples 
are cyber physical systems, real-time safety-critical embedded systems (e.g., nuclear 
reactors, fly by wire systems).

In general, reactive systems can be implemented by a single infinite loop, in which two 
schemes are used as follows.

```c
/* event-drivent scheme */
InitializeMemory();

foreach input_event do
  ComputeOutput();
  UpdateMemory();
end

/* sampling scheme */
InitializeMemory();

foreach period do 
  ReadInputs();
  ComputeOutput();
  UpdateMemory();
end
```
