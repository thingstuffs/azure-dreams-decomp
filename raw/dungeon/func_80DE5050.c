#include "common.h"
typedef void (*ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; ActorAction handler; s32 timer; } ActionState;
extern void func_80170E5C(void *,void *,void *,void *);
extern s32 func_800AB378(void *,void *,void *,void *);
extern s32 func_800AD9B4(void *,void *);
void func_80172850(ActionState *state,void *motion,void *sprite,void *actor) {
 if(func_800AB378(state,motion,sprite,actor)!=0 &&
    (func_800AD9B4(sprite,actor)<<16)>0) state->handler=func_80170E5C;
}
