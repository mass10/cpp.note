#!/bin/bash
# valgrind --leak-check=yes --verbose app/main arg1 arg2
valgrind --leak-check=yes app/main arg1 arg2
