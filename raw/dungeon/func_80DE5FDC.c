#include "common.h"
#include "shared/game_work.h"
#define gameWork D_80083160
extern GameWork D_80083160;
typedef void (*ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; ActorAction handler; s32 timer; } ActionState;
extern void func_80170E5C(void *,void *,void *,void *);
typedef struct {u8 pad00[0x2C];u8 *frames;} RenderState;
typedef struct {u8 pad00[0x1C];s32 flags;u8 pad20[0xA];s16 facing;} RenderActor;
extern s32 func_800AC82C(void *,void *,void *,void *);
extern s32 func_800AD9B4(void *,void *);
extern void func_80047784(void *,u8,s32);

extern u8 D_80174518[8],D_80174538[8];
void func_801737DC(ActionState *state,void *motion,RenderState *sprite,RenderActor *actor) {
 if(func_800AC82C(state,motion,sprite,actor)!=0) {
  if((func_800AD9B4(sprite,actor)<<16)>0) state->handler=func_80170E5C;
 } else if(sprite->frames==D_80174538 && !(actor->flags&0x208)) {
  sprite->frames=D_80174518;
  func_80047784(sprite,D_80174518[((gameWork.view.viewAngle+actor->facing+0x100)>>9)&7],0);
 }
}
