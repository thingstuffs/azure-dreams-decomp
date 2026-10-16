#include "common.h"
typedef void (*ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; ActorAction handler; s32 timer; } ActionState;
extern void func_80170E5C(void *,void *,void *,void *);
extern s32 func_800AB1C0(void *,void *,void *,void *);
extern void func_800AD594(void *,s32);
extern void func_800A4ACC(void *);
extern s32 func_800AD9B4(void *,void *);
void func_8017246C(ActionState *state,void *motion,void *sprite,void *actor) {
 if(func_800AB1C0(state,motion,sprite,actor)!=0) {
  func_800AD594(actor,4);
  func_800A4ACC(actor);
  if((func_800AD9B4(sprite,actor)<<16)>0) {
   state->handler=func_80170E5C;
   state->timer=0;
  }
 }
}
