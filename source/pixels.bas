DIM x(16), y(16)

x(0) = 0: y(0) = 0
x(1) = 1: y(1) = 0
x(2) = 2: y(2) = 0
x(3) = 3: y(3) = 0

x(4) = 0: y(4) = 1
x(5) = 1: y(5) = 1
x(6) = 2: y(6) = 1
x(7) = 3: y(7) = 1

x(8) = 0: y(8) = 2
x(9) = 1: y(9) = 2
x(10) = 2: y(10) = 2
x(11) = 3: y(11) = 2

x(12) = 0: y(12) = 3
x(13) = 1: y(13) = 3
x(14) = 2: y(14) = 3
x(15) = 3: y(15) = 3

FOR n = 1 TO 100
  p1 = INT(RND(1) * 16)
  p2 = INT(RND(1) * 16)
  
  SWAP x(p1), x(p2)
  SWAP y(p1), y(p2)
NEXT

PRINT "x=";

FOR n = 0 TO 15
  PRINT STR$(x(n));
NEXT

PRINT

PRINT "y=";

FOR n = 0 TO 15
  PRINT STR$(y(n));
NEXT

PRINT

