---
layout:     post
title:      Is HD Map Safe? 
date:       2021-05-16
excerpt:    Is HD Map Safe
categories: [Research, Robustness, Safety, Automated Driving Software]
tags:
 - research
 - robustness
 - safety
 - automated driving software
comments: true
---

The [incident][1] of Waymo's automated driving taxi happened few days ago. It reminds me about my personal opinion about automated driving technology obstacles that I'd like to recall here.

1. The machine learning (ML)-based software modules, by their nature, such as object detection and tracking (using camera or Lidar data inputs) are not reliable and robust. When we train a model, achieving 90% of accuracy is considered very high. It is great for many applications. However, it is __nothing__ for safety-critical applications like self-driving cars. For example, the probability of making a wrong detection within __1 hour of operation is 1__. Please have a look at [this post][2] for details, and [my proposal][3] for asserting ML-based software module.

2. The high definition (HD) maps, there is no ways to update the HD maps in real-time w.r.t the changes of the roads, building, landmarks,... We see in this case of Waymo's automated driving taxi, it seems that the planning algorithms rely on HD maps for making decisions. And the road cones and the HD maps do not agree each other, thus, it makes the car confused. Thus, HD maps __should__ be complementary, __not main source of making decisions__.

[1]: https://mashable.com/article/waymo-autonomous-car-gets-stuck/
[2]: https://channgo2203.github.io/unreliable-perception/
[3]: https://channgo2203.github.io/statistical-robustness/
