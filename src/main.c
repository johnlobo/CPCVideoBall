//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2015 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include <game.h>

// Máscara de transparencia
cpctm_createTransparentMaskTable(g_tablatrans, 0x100, M0, 0);

u8* mapa;
u8  num_mapa;
TProta prota;

void playmusic() {
   __asm
      exx
      .db #0x08
      push af
      push bc
      push de
      push hl
      call _cpct_akp_musicPlay
      pop hl
      pop de
      pop bc
      pop af
      .db #0x08
      exx
   __endasm;
}

void interruptHandler() {
   static u8 i;

   i++;
   switch(i) {
      case 7:
         cpct_scanKeyboard_if();
         break;
      case 8:
         // Play music
         playmusic();
         break;
      case 12:
         i=0;
   }
}

void initCPC() {
   cpct_disableFirmware();
   cpct_setVideoMode(0);
   cpct_setPalette(g_palette, 16);
   cpct_setBorder(HW_BLACK);
   cpct_etm_setTileset2x4(g_tileset);
   cpct_akp_musicInit(G_song);
   cpct_setInterruptHandler(interruptHandler);
}


void main(void) {
   // Set up new location for the stack (to use 0x8000-0xBFFF as backbuffer)
   cpct_setStackLocation((void*)0x8000);

   // Initialize
   initCPC();
   while (1) {
      u8 cont;
      GM_startmenu();
      GM_startgame();

      // Loop while game runs
      do {
         cont = GM_update();
         GM_draw();
      } while (cont);

      GM_gameOver();
   }
}

