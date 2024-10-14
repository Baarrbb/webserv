#!/bin/bash

HOST=0.0.0.0
PORT=5500

(
echo "GET / HTTP/1.1"
echo "Host:   d     "
echo ""
) | nc $HOST $PORT

