#!/bin/bash

g++ -std=c++11 ./src/client.cpp -o ./build/client -L/usr/local/lib -lzmq -lPocoJSON -lPocoFoundation
