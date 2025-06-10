#!/bin/bash

g++ main_serial.cpp -o main_serial
nvcc main_parallel.cu -o main_parallel