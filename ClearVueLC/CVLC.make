# Make 1.0 ROM for Mac II CVLC
C -E200 "+BU" "+I{MPW}azAll:all.h" Lane3ROMtail.c
C -dTESTING=0 -E200 "+BU" "+2" "+I{MPW}azAll:all.h" RomCVLCd1.c
ln RomCVLCd1.o "+d" -o ROM.CVXL -lc Lane3ROMtail.o
s1tool ROM.CVLC
DownLoad64 ROM.CVLC.S1.8K
Burn
