#!/bin/bash

rm -r latex_new
sleep 5
doxygen Doxyfile || exit
cd latex_new || exit
make