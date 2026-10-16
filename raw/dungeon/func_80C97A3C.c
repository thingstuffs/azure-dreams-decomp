#include "common.h"
typedef void (*ActionCallback)(void *,void *,void *,void *);
typedef struct {
 u8 pad[0x8C];
 ActionCallback handler;
} CallbackState;
extern s32 func_800AB464(void *,void *,void *,void *);
extern void func_8017102C(void *,void *,void *,void *);
/* Resume the action dispatcher after the resident action completes. */
void func_8017523C(CallbackState *state,void *position,void *sprite,void *entity) {
 if(func_800AB464(state,position,sprite,entity) > 0)
  state->handler=func_8017102C;
}
