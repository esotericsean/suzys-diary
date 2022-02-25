c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o Suzy.o Suzy.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o BGTiles.o BGTiles.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -c -o BGMap.o BGMap.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j  -c -o main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wl-yp0x143=0x80 -o main.gb Suzy.o BGTiles.o BGMap.o main.o

DEL *.lst
DEL *.o
DEL *.map
DEL *.sym