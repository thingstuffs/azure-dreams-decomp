#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 func_800AC7EC(void);
extern u8 D_800D8C64[];

void func_800DA808(CallbackOwner *owner) {
    if (func_800AC7EC() > 0) {
        owner->callback = D_800D8C64;
    }
}
