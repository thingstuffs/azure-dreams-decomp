#include "modules/dungeon_ovl_be1084.h"

void func_80170BFC(FadeEffect *effect,EffectMotion *motion) {
 s32 red,green,blue;
 s16 remaining;
 motion->x+=motion->dx;
 motion->y+=motion->dy;
 motion->z+=motion->dz;
 motion->dx/=2;
 motion->dy/=2;
 motion->dz/=2;
 red=effect->red*effect->remaining;
 effect->current.color.red=red/effect->total;
 green=effect->green*effect->remaining;
 effect->current.color.green=green/effect->total;
 blue=effect->blue*effect->remaining;
 effect->current.color.blue=blue/effect->total;
 remaining=effect->remaining-1;
 effect->remaining=remaining;
 effect->output=effect->current.packed;
 if(remaining<=0) {
  *(u16 *)((u8 *)effect-2)|=0x8000;
  object_flag_block.flags|=0x8000;
 }
}
