---
layout: post
title: Synchronous Programming of Reactive Embedded Systems
published: true
---

1. Some important design issues:
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

