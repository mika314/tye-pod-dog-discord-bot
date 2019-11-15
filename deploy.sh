#!/bin/bash
cd build
make -j7 VERBOSE=1
scp echo_bot mika@tye-pod-dog.mika.global:tye-pod-dog-dev/echo_bot_dev_tmp
ssh mika@tye-pod-dog.mika.global "mv -f tye-pod-dog-dev/echo_bot_dev_tmp tye-pod-dog-dev/echo_bot_dev && killall echo_bot_dev"
