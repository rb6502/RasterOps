#asm
  public endmydrvr
endmydrvr
#endasm
/* Format Block */
#asm
  dc.l  0      ; For alignment (probably not necessary)
formatblock
  public  directory
  dc.l  ((directory-formatblock)&$00FFFFFF) ; Negative offset to beginning (sResource Directory)
;  dc.l  (thatisit-directory)                ; CRC Length
;  dc.l  0            ; CRC
 dc.l  1         ; TEMPORARY ROM LENGTH OF 1
 dc.l  $3C       ; TEMPORARY ROM CHECKSUM OF 3C (LAST BYTE IN ROM [ByteLanes])
  dc.b  1            ; Revision 1 ROM
  dc.b  1            ; Apple Format ROM
  dc.l  $5A932BC7    ; Test Pattern
  dc.b  0            ; Reserved (Must be 0)
  dc.b  $3C          ; Only Lowest Byte in Longwords used
thatisit
#endasm
