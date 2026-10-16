#include "modules/dungeon_ovl_cb9000.h"

s32 func_8016E320(void *point, void *position, void *color) {
 void *next;
 for (;;) {
  func_8016DE40(point,position,color,0);
  next=((CL_CB9000_80174320_S_80174320_0_pre *)point)[-1].unk_00;
  point=next+0x20;
  if(next==0) break;
  position=((CL_CB9000_80174320_S_80174320_1 *)next)->unk_08;
  color=((CL_CB9000_80174320_S_80174320_1 *)next)->unk_0C;
 }
 return 0;
}
