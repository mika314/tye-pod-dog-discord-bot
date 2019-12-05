#!/bin/bash
cd build
make -j7 VERBOSE=1
scp echo_bot mika@tye-pod-dog.mika.global:tye-pod-dog/echo_bot_tmp
ssh mika@tye-pod-dog.mika.global "mv -f tye-pod-dog/echo_bot_tmp tye-pod-dog/echo_bot && killall echo_bot"
