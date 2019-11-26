#!/bin/bash

g++ -std=c++11 ./src/server.cpp -o ./build/server -L/usr/local/lib -lzmq -lPocoJSON -lPocoFoundation
