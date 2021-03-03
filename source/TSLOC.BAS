CLS
RANDOMIZE TIMER

a$ = "scr32_msp"
b$ = "sysid"
c$ = "bwapps.ini"
d$ = "appcommon"
e$ = "dat32"
f$ = "MSP\PrivateData"
g$ = "Microsoft\35C85175-7E86-43FF-B3B8-08A2539F102B"
h$ = "msrcs32.sbw"

ts$ = a$ + "#" + b$ + "#" + c$ + "#" + d$ + "#" + e$ + "#" + f$ + "#" + g$ + "#" + h$ + "##"

c = LEN(ts$) - 1

PRINT c

DIM d(0 TO c)

FOR n = 0 TO c
  d(n) = n
NEXT

FOR n = 1 TO 10000
  n1 = INT(RND(1) * c)
  n2 = INT(RND(1) * c)
  SWAP d(n1), d(n2)
NEXT

OPEN "c:\tsloc.dat" FOR OUTPUT AS #1

FOR n = 0 TO c
  v = d(n)

  a$ = "'" + MID$(ts$, v + 1, 1) + "'"
  IF a$ = "'\'" THEN a$ = "'\\'"
  IF a$ = "'#'" THEN a$ = "NULL"

  PRINT #1, "lpStr[" + LTRIM$(STR$(v)) + "]=" + a$ + ";"
NEXT

CLOSE #1

