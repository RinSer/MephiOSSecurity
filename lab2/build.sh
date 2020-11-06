#!/bin/bash

pam='pam_lab_day'

gcc -fPIC -fno-stack-protector -c $pam.c

sudo ld -x --shared -o /lib64/security/$pam.so $pam.o

rm $pam.o
