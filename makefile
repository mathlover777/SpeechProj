all:generate driver wavToInput InputToWav run
generate:generate.c
	g++ -g generate.c -o generate

driver:driver.cpp frame.cpp fileio.c LPC.c FILTER.c
	g++ -g -o driver driver.cpp

wavToInput:wavToInput.c fileio.c
	g++ -g -o wavToInput wavToInput.c

InputToWav:InputToWav.c fileio.c
	g++ -g -o InputToWav InputToWav.c

run:run.c
	g++ -g -o run run.c
