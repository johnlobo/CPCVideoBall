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
#include <entities.h>

// Máscara de transparencia
cpctm_createTransparentMaskTable(c_tablatrans, 0x100, M0, 0);

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

void interrupcion() {
   static u8 kk;

   if (++kk == 5) {
      playmusic();
      cpct_scanKeyboard_if();
      kk = 0;
   }
}

void dibujarMapa() {
   cpct_etm_drawTilemap2x4(g_map1_W, g_map1_H, ORIGEN_MAPA, mapa);
}

u8 compruebaTeclas(const cpct_keyID* k, u8 numk) {
   u8 i;
//   cpct_scanKeyboard_if();
   if (cpct_isAnyKeyPressed()) {
      for(i=1; i <= numk; i++, k++) {
         if (cpct_isKeyPressed(*k))
            return i;
      }
   }
   return 0;
}

void inicializar() {
   cpct_disableFirmware();
   cpct_setVideoMode(0);
   cpct_setPalette(g_palette, 16);
   cpct_setBorder(HW_BLACK);
   cpct_etm_setTileset2x4(g_tileset);
   dibujarMapa();
   dibujarProta();
   cpct_akp_musicInit(G_song);
   cpct_setInterruptHandler(interrupcion);
}


void main(void) {

   inicializar();

   // Loop forever
   while (1) {
      ejecutarEstado();
      if (prota.mover) {
         seleccionarSpriteProta();
         cpct_waitVSYNC();
         redibujarProta();
         prota.mover = NO;
      }
   }

    
}
