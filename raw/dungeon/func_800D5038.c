#include "common.h"

typedef struct {
    u8 before_callback[0x8C];
    void *callback;
} CallbackOwner;
extern s32 func_800ACE34(void);
extern u8 D_800D8C64[];

void func_800DA798(CallbackOwner *owner) {
    if (func_800ACE34() != 0) {
        owner->callback = D_800D8C64;
    }
}
