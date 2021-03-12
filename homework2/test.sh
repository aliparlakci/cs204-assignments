#!/bin/bash

g++ aliparlakci_parlakci_ali_hw2.cpp

if [ $? -eq 0 ]
then
    for i in {1..7}
    do  
        cat "./tests/input$i.txt" | ./a.out | diff "./tests/output$i.txt" -

        if [ $? -eq 0 ]
        then
            echo "SUCCESSFUL: test $i"
        else
            echo "FAILED: test $i"
        fi
        
    done
fi