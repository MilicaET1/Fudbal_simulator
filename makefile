.PHONY : all
all : Fudbal_simulator
Fudbal_simulator : zadatak2.c
	gcc -o Fudbal_simulator zadatak2.c
