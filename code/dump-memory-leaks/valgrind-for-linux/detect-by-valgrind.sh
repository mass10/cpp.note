#!/bin/bash
# valgrind --leak-check=yes --verbose app/main arg1 arg2
# valgrind --leak-check=yes --track-origins=yes app/main arg1 arg2
valgrind --leak-check=full --track-origins=yes app/main arg1 arg2
