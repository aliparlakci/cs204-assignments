#!/bin/bash

./build.sh

if [ $? -eq 0 ]
then
    for i in {1..6}
    do  
        cat "./tests/input$i.txt" | ./aliparlakci_Parlakci_Ali_hw3 | diff -Z --strip-trailing-cr "./tests/output$i.txt" -

        if [ $? -eq 0 ]
        then
            echo "SUCCESSFUL: test $i"
        else
            echo "FAILED: test $i"
        fi
        
    done
fi