---
layout: post
title: Synchronous Programming of Reactive Embedded Systems
published: true
---

### Some important design issues
- Hard versus soft real-time
- Safety criticality: e.g. DO-178B/C defines 5 levels of safety:
A- the most critical level, a fault leads to catastrophic consequences, 
B- leads to severe consequences, 
C- leads to major consequences, 
D- leads to minor consequences, and 
E- leads to consequences without andy effect on the system.
- Determinism: very important property of embedded systems. It ensures that the system will always behave in the same manner, with respect to its expected functional requirements.
- Predictability: beyond the functional requirements, one must be able to predict at least the critical nonfunctional behavior of system, e.g. the timing constraints are always satisfied (response time or latency constraints, rate constraints, which rely on the number of events processed by a system during a time period)
- Distribution and heterogeneity
- Complexity and modularity

A real issue in real-time programming is how to deal with timing information. The form of timing information is based on the abstraction level adopted. The logical time is related to the physical time only at instants t1 (input event occurs) and t2 (output event of the system). 

The real-time programming models include: 

- Asynchronous

- Pre-estimated time

-  Synchronous

2. Reactive systems 
Reactive systems are systems that continuously react to their environment at a speed determined by this environment. Most industrial real-time systems are reactive. The main features of these systems are the following:
- Involve concurrency
- Submitted to strict time requirements: concern both their input rate and their inout/output response time
- Generally deterministic
- Reliability is an especially important goal
- Mix of software and hardware

3. Approaches

Classical approaches: Models include automata or Petri-net based models, task-based models, and communicating processes
- Deterministic automata: Automata are often used to implement the control kernel of a reactive system. A reaction is a block of code (neither loop nor recursive, no interrupt, no overhead due to process management), whose maximal execution time can be accurately bounded. Moreover, automata are well-known mathematical objects for which verification techniques are available (evaluation of temporal logic formulas, reduction and observation). However, automata are "flat" objects, without any hierarchical or parallel structure. As results, they are very difficult to use to design complex systems.
- Petri-net-based models: These models are mainly used to program industrial controllers, the inherent concurrency of these models reduces the complexity of system description. However, because of the lack of hierarchy, they are hard to apply to big systems. In addition, their semantics, especially concerning time aspects, is often unclear (or ambiguous).
- Task-based models: The approach consisting in designing a system as made of a set of sequential tasks, activated and controlled by a real-time operating system.
- Classical concurrent and real-time programming languages: Concurrent and real-time
programming languages such as ADA or OCCAM take concurrency as a primary
concern and support modularity. Communication and synchronization mechanisms use
rendez-vous, and fifo queues. However, they are essentially asynchronous and nondeterministic.
- The synchronous approach: The synchronous approach naturally expresses concurrency. It is deterministic and hierarchical, and possible to use automatic verification tools.

In the synchronous approach, time is abstracted by a partial order relation.
Events occurring during the same reaction are regarded as simultaneous. Time only increments
from one reaction to the next one. Durations between events are not specified. Under
this abstraction, computation is considered to take zero time. A synchronous program is
supposed to instantly and deterministically react to the events from its environment. To
illustrate the basic idea of synchronous approach, we consider an example in which
requires the two following constraints:
	- “The train must stop within 10 seconds”
	- “The train must stop within 100 meters”
These constraints can be expressed in completely different ways if the physical time is
considered. In the synchronous model, they will be expressed by the following constraints:
	- “The event stop must precede the 10th next occurrence of the event second”
	- “The event stop must precede the 100th next occurrence of the event meter”
The notion of instant is understood as a logical instant: the history of a system is a totally
ordered sequence of logical instants. At each instant, there are zero, one, or several events
that can occur. Events which occur at the same instants are considered as simultaneous. In
the duration between two instants, nothing happens either in the system or its environment.
Finally, all the processes of the system have the same knowledge of the events occurring at
a given instant. 
