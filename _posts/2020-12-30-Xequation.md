---
layout:     post
title:      An Introduction to Xequation
date:       2020-12-30
excerpt:    An Introduction to Xequation
categories: [Xequation, Autonomous Vehicles, Self-Driving Cars, Perception, Localization, Motion Planning, Control, Real-time Embedded Programming]
tags:
 - programming
 - real-time embedded
 - deep learning
 - machine learning
 - autonomous vehicles
 - self-driving cars
 - autopilot
 - xequation
comments: true
---

In this post, I am excited to introduce __`Xequation`__.

{:refdef: style="text-align: center;"}
![Xequation]({{ site.url }}/img/Xequation.png){:height="36%" width="36%"}
{: refdef}

Generally, machine learning (ML) based applications are required to be 
generalized such that they can work correctly with unseen samples. However, 
ML algorithms, including highly trained and smooth neutral networks optimized for 
perception tasks, have been shown to lack `robustness to small changes of inputs`, 
known as `perturbations`. __`Xequation`__ is a new framework for verifying 
the `robustness of ML-based safety-critical applications`. The analysis is fully 
automatic and derives the estimated probability of how robust a model is w.r.t 
perturbations, called statistical robustness.

The new technique combines the model checking techniques with temporal logics for 
probabilistic programs with an adaptation of multi-level splitting, a method for 
estimating the probability of rare events to the statistical robustness. 
As a result, the framework provides a unifying formalization of the perturbation 
generation process and a definition of robustness from a formal methods perspective. 
An advantage of the technique is that it has an ability to scale to much larger ML 
models, e.g. deep neutral networks used in autonomous driving software stack, than 
formal methods approaches such as using an automated theorem prover. 
The effectiveness of the technique is demonstrated with a prototype implementation 
that is able to automatically verify on benchmark problems, while scaling to larger 
deep neutral networks. Experimental results indicate that the derived probability 
is reliable and accurate.

The objective of __`Xequation`__ is to provide <strong><em>Solutions and tool development for verifying the robustness and reliability from a formal methods perspective for Machine Learning (ML)-based safety-critical applications such as localization, perception, and planning modules in autnomous driving software stack</em></strong>
