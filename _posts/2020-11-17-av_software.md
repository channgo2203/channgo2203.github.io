---
layout:     post
title:      Autonomous Vehicles Software Stack Overview
date:       2020-11-17
excerpt:    Autonomous Vehicles Software Stack Overview
categories: [Tutorials, Autonomous Vehicles, Self-Driving Cars, Perception, Localization, Motion Planning, Control, Real-time Embedded Programming]
tags:
 - tutorials
 - programming
 - real-time embedded
 - deep learning
 - machine learning
 - autonomous vehicles
 - self-driving cars
 - autopilot
comments: true
---

In this post, I want to discuss about `autonomous vehicles software stack`: the common software modules, the basic control and data-flow of the software stack, and the basics of the algorithm behind each software module.

Roundly speaking, the inputs of an autonomous vehicles software system are:
* __Point cloud data__: from Lidar, radar, and IMU sensors
* __3D map data__: from the mapping packages
* __Image data__: from cameras and Lidar sensors

Its output is:
* __Velocity__: as command to the vehicle drive-by-wire controller
* __Angle__: as command to the vehicle drive-by-wire controller
