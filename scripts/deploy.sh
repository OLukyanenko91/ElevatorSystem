#! /bin/bash

sshpass -p "$2" scp build/ElevatorSystem "$1@$3:/home/$1/ElevatorSystem/"
