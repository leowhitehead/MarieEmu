# MarieEmu
An emulator for the MARIE instruction set

Still work in progress, doesn't work on MARIE's multiplication example, but works relatively well otherwise. Input is only supported with raw binary files.

Input/output is formatted as hex.

Example compilation and use:

```
$ cd src
$ make
gcc main.c -o marie -Wall -Wpedantic -std=c11
$ xxd add.rom
00000000: 5000 2007 5000 2008 3007 6000 7000 0000  P. .P. .0.`.p...
00000010: 0000
$ ./marie add.rom
2
3
5
```
