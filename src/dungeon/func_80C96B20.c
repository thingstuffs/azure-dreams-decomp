#include "modules/dungeon_ovl_cb3000.h"

s32 advance_boss_command_stream(void *point, void *position, void *color) {
 void *next;
 for (;;) {
  project_visible_effect_quad(point,position,color,0);
  next=((CB_80174320_S_80174320_0_pre *)point)[-1].unk_00;
  point=next+0x20;
  if(next==0) break;
  position=((CB_80174320_S_80174320_1 *)next)->unk_08;
  color=((CB_80174320_S_80174320_1 *)next)->unk_0C;
 }
 return 0;
}
