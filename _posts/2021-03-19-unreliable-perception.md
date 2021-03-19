---
layout:     post
title:      Is ML Algorithm-based Perception Safe? 
date:       2021-03-19
excerpt:    Is ML Algorithm-based Perception Safe
categories: [Research, Robustness, Safety, Automated Driving Software]
tags:
 - research
 - robustness
 - safety
 - automated driving software
comments: true
---

I want to recall that [Tesla autopilot][1] has failed for more than one time because of the perception module. It shows the unreliable nature of general machine learning (ML) algorithms. We know that 90% precision level is very high for almost very highly trained ML models. It is great for many applications, however, it is __dangerous__ for mission-critical applications such as automated driving.

We can consider self-driving cars are __probabilistic robots__ in which there are many uncertainties. One of them is the __unpredictable environment__ where the robots operating. Thus, the training set size of the perception module is very small compared with the number of all possible scenarios in the environment. In summary, we could say that we are deploying a unreliable module into a safety-critical system. 

People can say that we have high definition (HD) maps to support the decision of the automated driving system. However, HD maps cannot deal with __dynamic objects__ such as other vehicles (e.g. the semi-truck). Therefore, it seems that it is not safe when the system's logic relies on perception outputs only to make decision. 

It suggests that we might need to think about other solution instead of relying on ML algorithms-based perception. One of the possible solution is reasoning about the robustness of perception and other modules in the automated driving system with respect to the uncertainties as discussed in [this post][2].


Now, we think a little about a perception (object detection and tracking) whose accuracy is 90%. Let's assume that it runs with the frequency of 10Hz. We want to know what is the __probability__ that it makes __a wrong detection__ during one hour of operation. In one hour, it performs $$10 \times 60 \times 60 = 36000$$ inferences. Thus, the probability is $$1 - 0.9^{36000}$$ which is very closed to $$1.0$$.

[1]: https://www.theverge.com/2019/5/17/18629214/tesla-autopilot-crash-death-josh-brown-jeremy-banner
[2]: https://channgo2203.github.io/statistical-robustness/
