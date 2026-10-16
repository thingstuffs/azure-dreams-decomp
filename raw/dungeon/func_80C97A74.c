#include "common.h"
typedef void (*ActionCallback)(void *,void *,void *,void *);
typedef struct {
 u8 pad[0x8C];
 ActionCallback handler;
} CallbackState;
extern s32 func_800AC7EC(void *,void *,void *,void *);
extern void func_8017102C(void *,void *,void *,void *);
/* Resume the action dispatcher after the resident action completes. */
void func_80175274(CallbackState *state,void *position,void *sprite,void *entity) {
 if(func_800AC7EC(state,position,sprite,entity) != 0)
  state->handler=func_8017102C;
}
