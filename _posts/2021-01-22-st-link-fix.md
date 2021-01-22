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

When we run [st-link](https://github.com/stlink-org/stlink) on Ubuntu to `reset` or `erease` the STM32 blue pill board. 

```shell
$ st-flash reset
st-flash 1.6.1
2021-01-21T01:35:02 WARN usb.c: NRST is not connected
2021-01-21T01:35:02 WARN common.c: unknown chip id! 0x3748
Failed to connect to target
```

```shell
$ st-flash erase
st-flash 1.6.1
2021-01-21T01:43:16 WARN usb.c: NRST is not connected
2021-01-21T01:43:16 WARN common.c: unknown chip id! 0x3748
Failed to connect to target
```

We get the error messages

> unknown chip id! or Failed to connect to target

The following shows a `possible way` to resolve this issue.

## How to fix

We can perform the following steps to resolve the issue.

* Step 1: Set the board into `programming mode` as shown in the image

![Programming mode]({{ site.url }}/images/STM32-BOOT-ProMode.jpeg)

* Step 2: Run the command `st-flash erase` while press the `reset button`

```shell
$ st-flash erase
st-flash 1.6.1
2021-01-21T01:43:22 INFO common.c: F1xx Medium-density: 20 KiB SRAM, 0 KiB flash in at least 1 KiB pages.
Mass erasing
```
