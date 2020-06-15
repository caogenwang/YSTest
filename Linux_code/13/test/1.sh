#!/bin/bash

first=0
second=0

read -p "Please Input First Number:" first
read -p "Please Input First Number:" second

result=$[$first+$second]

echo "Result is:$result"
exit 0