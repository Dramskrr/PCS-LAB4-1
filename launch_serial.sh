#!/bin/bash

sed -i "5,+0 s|.*|export THREADS_CONFIG=1|g" launch.sh

./launch.sh