#!/bin/bash

# unworking .sh, need to fix

PID=$(cat /tmp/ex1.pid)

if [ -z "$PID" ]; then
    echo "Failed to get the PID."
    exit 1
fi

echo "Searching for the password..."
sudo grep -a "pass:" /proc/$PID/mem

sudo kill -9 $PID
echo "Process $PID terminated."
