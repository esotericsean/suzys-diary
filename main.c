#include <gb/gb.h>
#include <gb/cgb.h>
#include <stdio.h>
#include "Suzy.h"
#include "BGTiles.h"
#include "BGMap.h"
#include "GameCharacter.c"

struct GameCharacter suzy;
UINT8 i = 1;
UINT8 lastdirection = 0; //0 down, 1 right, 2 up, 3 left
UINT8 walktimer = 1; //counter for changing animated walk cycle frames

const UWORD backgroundpalette[] = {
    BGTilesCGBPal0c0, BGTilesCGBPal0c1, BGTilesCGBPal0c2, BGTilesCGBPal0c3,
    BGTilesCGBPal1c0, BGTilesCGBPal1c1, BGTilesCGBPal1c2, BGTilesCGBPal1c3,
    BGTilesCGBPal2c0, BGTilesCGBPal2c1, BGTilesCGBPal2c2, BGTilesCGBPal2c3
};

const UWORD spritepalette[] = {
    SuzySpritesCGBPal0c0, SuzySpritesCGBPal0c1, SuzySpritesCGBPal0c2, SuzySpritesCGBPal0c3,
    SuzySpritesCGBPal1c0, SuzySpritesCGBPal1c1, SuzySpritesCGBPal1c2, SuzySpritesCGBPal1c3
};

// once they're setup, we can move them as a whole so they line up as a single game character
// GameCharacter needs to be a pointer so it moves the ACTUAL character and not a "copy"
void movegamecharacter (struct GameCharacter* character, UINT8 x, UINT8 y, BOOLEAN flipped) {
    if (flipped == 0) {
        move_sprite (character->spriteid[0], x, y);
        move_sprite (character->spriteid[1], x + 8, y);
        move_sprite (character->spriteid[2], x, y + 8);
        move_sprite (character->spriteid[3], x + 8, y + 8);
    }
    if (flipped == 1) {
        move_sprite (character->spriteid[0], x, y);
        move_sprite (character->spriteid[1], x - 8, y);
        move_sprite (character->spriteid[2], x, y + 8);
        move_sprite (character->spriteid[3], x - 8, y + 8);
    }
}

void setupbackground() {
    set_bkg_palette (0, 3, &backgroundpalette[0]);

    set_bkg_data (0, 20, BGTiles);

    VBK_REG = 1;

    set_bkg_tiles (0, 0, BGMapWidth, BGMapHeight, BGMapPLN1); //load bg palette array

    VBK_REG = 0;

    set_bkg_tiles (0, 0, BGMapWidth, BGMapHeight, BGMapPLN0); //load bg tiles
}

void setupsuzy() {
    suzy.x = 80;
    suzy.y = 72;
    suzy.width = 16;
    suzy.height = 16;

    // start at 0, load 2 palettes, from spritepallet into sprite palette memory
    set_sprite_palette (0, 2, &spritepalette[0]);

    // start at tile 0 and load n amount from "sprites" array
    set_sprite_data (0, 37, SuzySprites);

    set_sprite_tile (0, 1); //sets sprite 0 to tile 0 from memory
    set_sprite_prop (0, 0); //sets sprite 0 to use palette 0
    suzy.spriteid[0] = 0;   //sets spriteid array position 0 to sprite 0
    
    set_sprite_tile (1, 2);
    set_sprite_prop (1, 0);
    suzy.spriteid[1] = 1;
    
    set_sprite_tile (2, 3);
    set_sprite_prop (2, 1);
    suzy.spriteid[2] = 2;
    
    set_sprite_tile (3, 4);
    set_sprite_prop (3, 1);
    suzy.spriteid[3] = 3;

    // see below, arranges suzy's sprites how they're supposed to be and moves it to
    // whatever/wherever we set suzy.x and suzy.y to in the struct
    movegamecharacter (&suzy, suzy.x, suzy.y, 0);
}

void suzystanddown() {
    set_sprite_prop (0, 0);
    set_sprite_tile (0, 1);

    set_sprite_prop (1, 0);
    set_sprite_tile (1, 2);
    
    set_sprite_prop (2, 1);
    set_sprite_tile (2, 3);
    
    set_sprite_prop (3, 1);
    set_sprite_tile (3, 4);

    movegamecharacter (&suzy, suzy.x, suzy.y, 0);
}

void suzystandup() {
    set_sprite_prop (0, 0);
    set_sprite_tile (0, 25);

    set_sprite_prop (1, 0);
    set_sprite_tile (1, 26);
    
    set_sprite_prop (2, 1);
    set_sprite_tile (2, 27);
    
    set_sprite_prop (3, 1);
    set_sprite_tile (3, 28);

    movegamecharacter (&suzy, suzy.x, suzy.y, 0);
}

void suzystandright() {
    set_sprite_prop (0, 0);
    set_sprite_tile (0, 13);

    set_sprite_prop (1, 0);
    set_sprite_tile (1, 14);
    
    set_sprite_prop (2, 1);
    set_sprite_tile (2, 15);
    
    set_sprite_prop (3, 1);
    set_sprite_tile (3, 16);

    movegamecharacter (&suzy, suzy.x, suzy.y, 0);
}

void suzystandleft() {
    set_sprite_tile (0, 13);
    set_sprite_prop (0, 0|S_FLIPX);

    set_sprite_tile (1, 14);
    set_sprite_prop (1, 0|S_FLIPX);

    set_sprite_tile (2, 15);
    set_sprite_prop (2, 1|S_FLIPX);

    set_sprite_tile (3, 16);
    set_sprite_prop (3, 1|S_FLIPX);

    movegamecharacter (&suzy, suzy.x, suzy.y, 1);
}

void suzystand() {
    if (lastdirection == 0)
        suzystanddown();
    else if (lastdirection == 1)
        suzystandright();
    else if (lastdirection == 2)
        suzystandup();
    else if (lastdirection == 3)
        suzystandleft();
}

void suzywalkdown() {
    //frame 1 - left foot up
    if (walktimer >= 1 && walktimer <= 12) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 5);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 6);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 7);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 8);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 2 - "stand"
    if (walktimer > 12 && walktimer <= 24) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 1);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 2);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 3);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 4);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 3 - right foot up
    if (walktimer > 24 && walktimer <= 36) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 9);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 10);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 11);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 12);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 4 - "stand"
    if (walktimer > 36 && walktimer <= 48) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 1);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 2);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 3);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 4);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }
}

void suzywalkright() {
    //frame 1 - left foot up
    if (walktimer >= 1 && walktimer <= 12) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 17);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 18);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 19);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 20);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 2 - "stand"
    if (walktimer > 12 && walktimer <= 24) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 13);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 14);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 15);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 16);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 3 - right foot up
    if (walktimer > 24 && walktimer <= 36) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 21);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 22);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 23);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 24);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 4 - "stand"
    if (walktimer > 36 && walktimer <= 48) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 13);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 14);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 15);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 16);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }
}

void suzywalkup() {
    //frame 1 - left foot up
    if (walktimer >= 1 && walktimer <= 12) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 29);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 30);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 31);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 32);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 2 - "stand"
    if (walktimer > 12 && walktimer <= 24) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 25);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 26);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 27);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 28);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 3 - right foot up
    if (walktimer > 24 && walktimer <= 36) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 33);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 34);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 35);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 36);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }

    //frame 4 - "stand"
    if (walktimer > 36 && walktimer <= 48) {
        set_sprite_prop (0, 0);
        set_sprite_tile (0, 25);

        set_sprite_prop (1, 0);
        set_sprite_tile (1, 26);
        
        set_sprite_prop (2, 1);
        set_sprite_tile (2, 27);
        
        set_sprite_prop (3, 1);
        set_sprite_tile (3, 28);

        movegamecharacter (&suzy, suzy.x, suzy.y, 0);
    }
}

void suzywalkleft() {
    //frame 1 - left foot up
    if (walktimer >= 1 && walktimer <= 12) {
        set_sprite_tile (0, 17);
        set_sprite_prop (0, 0|S_FLIPX);

        set_sprite_tile (1, 18);
        set_sprite_prop (1, 0|S_FLIPX);

        set_sprite_tile (2, 19);
        set_sprite_prop (2, 1|S_FLIPX);

        set_sprite_tile (3, 20);
        set_sprite_prop (3, 1|S_FLIPX);

        movegamecharacter (&suzy, suzy.x, suzy.y, 1);
    }

    //frame 2 - "stand"
    if (walktimer > 12 && walktimer <= 24) {
        set_sprite_tile (0, 13);
        set_sprite_prop (0, 0|S_FLIPX);

        set_sprite_tile (1, 14);
        set_sprite_prop (1, 0|S_FLIPX);

        set_sprite_tile (2, 15);
        set_sprite_prop (2, 1|S_FLIPX);

        set_sprite_tile (3, 16);
        set_sprite_prop (3, 1|S_FLIPX);

        movegamecharacter (&suzy, suzy.x, suzy.y, 1);
    }

    //frame 3 - right foot up
    if (walktimer > 24 && walktimer <= 36) {
        set_sprite_tile (0, 21);
        set_sprite_prop (0, 0|S_FLIPX);

        set_sprite_tile (1, 22);
        set_sprite_prop (1, 0|S_FLIPX);

        set_sprite_tile (2, 23);
        set_sprite_prop (2, 1|S_FLIPX);

        set_sprite_tile (3, 24);
        set_sprite_prop (3, 1|S_FLIPX);

        movegamecharacter (&suzy, suzy.x, suzy.y, 1);
    }

    //frame 4 - "stand"
    if (walktimer > 36 && walktimer <= 48) {
        set_sprite_tile (0, 13);
        set_sprite_prop (0, 0|S_FLIPX);

        set_sprite_tile (1, 14);
        set_sprite_prop (1, 0|S_FLIPX);

        set_sprite_tile (2, 15);
        set_sprite_prop (2, 1|S_FLIPX);

        set_sprite_tile (3, 16);
        set_sprite_prop (3, 1|S_FLIPX);

        movegamecharacter (&suzy, suzy.x, suzy.y, 1);
    }
}

void main() {
    setupbackground(); //setup the first background (test bg)
    setupsuzy(); //load suzy's sprites, setup metasprite, etc.

    SHOW_SPRITES;
    SHOW_BKG;
    DISPLAY_ON;

    while (1) {
        if (joypad()) {
            walktimer++;

            if (walktimer > 48)
                walktimer = 1;
        }
        if (joypad() & J_LEFT) {
            if (lastdirection == 0) {
                suzy.y -= 0;    //refines the position of the sprite to be more accurate when turning
                suzy.x += 0;    //same but in the x direction
            }
            else if (lastdirection == 2) {
                suzy.y += 0;    //for some reason, only moving left needs this
                suzy.x += 0;
            }
            else if (lastdirection == 1) {
                suzy.x += 1;
            }
            suzywalkleft();
            suzy.x -= 1;
            lastdirection = 3;
        }
        if (joypad() & J_RIGHT) {
            if (lastdirection == 0)
                suzy.y -= 0;
            else if (lastdirection == 2)
                suzy.y += 0;
            else if (lastdirection == 3)
                suzy.x -= 1;
            suzywalkright();
            suzy.x += 1;
            lastdirection = 1;
        }
        if (joypad() & J_UP) {
            suzywalkup();
            suzy.y -= 1;
            lastdirection = 2;
        }
        if (joypad() & J_DOWN) {
            suzywalkdown();
            suzy.y += 1;
            lastdirection = 0;
        }

        //otherwise, if joypad is not being pressed, change sprite to stand in the last direction suzy moved
        else if (!joypad()) {
            suzystand();
            walktimer = 1; //reset walk animation when letting go of dpad
        }

        wait_vbl_done();
    }
}