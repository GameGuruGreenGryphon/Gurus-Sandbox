#!/bin/env bash

for i in $(seq 128); do
	"./cruntemp" "$i"
	sleep 0.2
	echo
done
