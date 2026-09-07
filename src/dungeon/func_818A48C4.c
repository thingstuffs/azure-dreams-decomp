#include "common.h"

typedef struct {
    u8 pad14[0x14];
    u16 flags;
    u8 pad1a[4];
    s16 value;
} Func818A48C4Object;

extern void func_8003DB94(void *, void *, s32);
extern void func_800478B8(void *);
extern s32 rand(void);
extern u8 D_80025238[];

void func_818A48C4(Func818A48C4Object **arg0, s32 arg1,
                   Func818A48C4Object *arg2) {
    Func818A48C4Object *temp_v1;
    s32 temp_v0;

    temp_v1 = *arg0;
    temp_v1->flags += 1;
    func_800478B8(arg2);
    temp_v0 = rand();
    arg2->value = (s16)(temp_v0 % 0x1000);
    if (arg2->flags & 0x6000) {
        func_8003DB94(arg2, D_80025238, 0);
    }
}
