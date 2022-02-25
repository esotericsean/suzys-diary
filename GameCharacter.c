#include <gb/gb.h>

struct GameCharacter {
    UBYTE spriteid[4]; // all characters use 4 sprites
    UINT8 x;
    UINT8 y;
    UINT8 width;
    UINT8 height;
}