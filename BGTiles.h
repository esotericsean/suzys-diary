/*

 BGTILES.H

 Include File.

 Info:
  Form                 : All tiles as one unit.
  Format               : Gameboy 4 color.
  Compression          : None.
  Counter              : None.
  Tile size            : 8 x 8
  Tiles                : 0 to 19

  Palette colors       : Included.
  SGB Palette          : None.
  CGB Palette          : 1 Byte per entry.

  Convert to metatiles : No.

 This file was generated by GBTD v2.2

*/


/* Bank of tiles. */
#define BGTilesBank 0

/* Gameboy Color palette 0 */
#define BGTilesCGBPal0c0 14970
#define BGTilesCGBPal0c1 12889
#define BGTilesCGBPal0c2 11799
#define BGTilesCGBPal0c3 0

/* Gameboy Color palette 1 */
#define BGTilesCGBPal1c0 12889
#define BGTilesCGBPal1c1 12889
#define BGTilesCGBPal1c2 7505
#define BGTilesCGBPal1c3 0

/* Gameboy Color palette 2 */
#define BGTilesCGBPal2c0 28381
#define BGTilesCGBPal2c1 12889
#define BGTilesCGBPal2c2 23065
#define BGTilesCGBPal2c3 0

/* CGBpalette entries. */
extern unsigned char BGTilesCGB[];

/* Start of tile array. */
extern unsigned char BGTiles[];

/* End of BGTILES.H */
