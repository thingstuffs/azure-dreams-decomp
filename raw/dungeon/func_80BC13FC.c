#include "common.h"
#include "shared/object_flags.h"
typedef struct { s32 x,y,z,dx,dy,dz; } EffectMotion;
typedef struct {
 u8 red,green,blue,pad03;
 union {struct {u8 red,green,blue,pad;} color;s32 packed;} current;
 s32 output;
 u8 pad0c[0x26];
 s16 remaining,total;
} FadeEffect;
/* Advance and damp motion; scale the current color by the remaining lifetime. */
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
  objectFlagBlock.flags|=0x8000;
 }
}
