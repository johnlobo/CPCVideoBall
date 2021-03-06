//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CodePrincess: A CPCtelera game made for #bitbitjam3
//  Copyright (C) 2016 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
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
#include "entities.h"

///////////////////////////////////////////////////////////////
/// GM_update
///   Updates the state of the game
///////////////////////////////////////////////////////////////
u8 GM_update() {
   if (LM_isLevelFinished() || cpct_isKeyPressed(Key_G))
      GM_nextLevel();
//   cpct_setBorder(HW_MAGENTA);
   EM_update();
   LM_update(hero->pos[2].x);
   EM_clear();
   CM_draw();
//   cpct_setBorder(HW_BLACK);
   cpct_waitVSYNC();

   return CM_getLife();
}

///////////////////////////////////////////////////////////////
/// GM_draw
///   Draws next frame of the game under execution
///////////////////////////////////////////////////////////////
void GM_draw() {
   LM_draw();
   EM_draw();
//   cpct_setBorder(HW_GREEN);
   cpct_waitVSYNC();
   SM_switchScreenBuffers();
}

///////////////////////////////////////////////////////////////
/// GM_gameOver
///   Initializes the menu
///////////////////////////////////////////////////////////////
void GM_gameOver() {
   u16 c = 1500;  // 30 secs

   while (--c) {
      cpct_drawStringM0 ("GAME OVER"
                        ,  cpctm_screenPtr(CPCT_VMEM_START, 20, 70)
                        ,  c & 0x0F, 1);
      if (cpct_isAnyKeyPressed())
         return;
      cpct_waitVSYNC();
   }
}

///////////////////////////////////////////////////////////////
/// GM_startmenu
///   Initializes the menu
///////////////////////////////////////////////////////////////
void GM_startmenu () {
   LM_initialize(getRand() & 1);
   LM_draw();

   while (1) {
      u16 c = 1000;  // 20 secs

      LM_setOffset(getRand());
      LM_drawBg(SM_scrBuf());

      cpct_drawStringM0 ("KUNG FU GUNS"
                        ,  cpctm_screenPtr(CPCT_VMEM_START, 13, 70)
                        ,  15, 1);

      cpct_drawStringM0 ("PRESS ANY KEY"
                        ,  cpctm_screenPtr(CPCT_VMEM_START, 12, 140)
                        ,  getRand() & 0x07 + 2, 10);

      while (--c) {
         if (cpct_isAnyKeyPressed())
            return;
         cpct_waitVSYNC();
      }
   }
}

///////////////////////////////////////////////////////////////
/// GM_startgame
///   Initializes a new game
///////////////////////////////////////////////////////////////
void GM_startgame() {
   // Initialize entity manager and create hero
   LM_initialize(0);
   EM_initialize();
   CM_inititalize(24, 0);
   hero = EM_createEntity(10, 95, E_Princess);
   hero->energy = 24;
   mgm_level = 0;
}




void drawMap() {
   cpct_etm_drawTilemap2x4(g_map1_W, g_map1_H, ORIGEN_MAPA, mapa);
}

u8 checkKeyboard(const cpct_keyID* k, u8 numk) {
   u8 i;
   if (cpct_isAnyKeyPressed()) {
      for(i=1; i <= numk; i++, k++) {
         if (cpct_isKeyPressed(*k))
            return i;
      }
   }
   return 0;
}

