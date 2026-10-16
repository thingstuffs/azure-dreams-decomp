#include "common.h"
typedef void (*ActorAction)(void *,void *,void *,void *);
typedef struct { u8 pad00[0x8C]; ActorAction handler; s32 timer; } ActionState;
extern void func_80170E5C(void *,void *,void *,void *);
extern s32 func_800ABDBC(void *,void *,void *,void *);
/* Resume the bank action after the resident callback completes. */
void func_8017321C(ActionState *state,void *motion,void *sprite,void *actor) {
 if(func_800ABDBC(state,motion,sprite,actor) != 0) state->handler=func_80170E5C;
}
