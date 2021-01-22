---
layout:     post
title:      Fix ST-Link for STM32 Blue Pill
date:       2021-01-22
excerpt:    Fix ST-Link for STM32 Blue Pill
categories: [Tutorials, ARM Assembly, Real-time Embedded Programming]
tags:
 - tutorials
 - programming
 - ARM assembly
 - real-time embedded
comments: true
---

In this post of fixing ST-link utility on Linux such as Ubuntu.

## Issues

When we run [st-link](https://github.com/stlink-org/stlink) on Ubuntu to `reset` or `erease` the STM32 blue pill board. We get the error messages

> unknown chip id!
> Failed to connect to target

The following shows a `possible way` to resolve this issue.

## How to fix

