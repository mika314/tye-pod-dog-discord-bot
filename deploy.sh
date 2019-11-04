#!/bin/bash
cd build
make -j7
ssh mika@tye-pod-dog.mika.global killall echo_bot_dev
scp echo_bot mika@tye-pod-dog.mika.global:tye-pod-dog-dev/echo_bot_dev
