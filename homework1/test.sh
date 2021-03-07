#!/bin/bash

g++ aliparlakci_parlakci_ali_hw1.cpp

if [ $? -eq 0 ]
then
    for i in {1..8}
    do  
        echo "./cases/test$i.txt" | ./a.out | diff "./cases/out$i.txt" -

        if [ $? -eq 0 ]
        then
            echo "SUCCESSFUL: case $i"
        else
            echo "FAILED: case $i"
        fi
        
    done
fi