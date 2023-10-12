# Make 1.0 ROM for 8/LC
C -E200 "+BU" "+I{MPW}azAll:all.h" Lane3ROMtail.c
C -E200 "+BU" "+2" "+I{MPW}azAll:all.h" 8LC.c
ln 8LC.o "+d" -o 8LC -lc Lane3ROMtail.o
s1tool 8LC
DownLoad256 8LC.S1.32K
Burn
