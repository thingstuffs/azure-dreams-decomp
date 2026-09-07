#include "common.h"

extern u32 func_800AB1C0(void);
extern void func_800AD594(void *, s32);
extern void func_800A4ACC(void *);
extern s32 func_800AD9B4(void *, void *);

extern u16 D_80083462[];
extern u8 D_80171A80[];

void func_80172FEC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    void *value = arg2;
    void *actor = arg3;

    if (func_800AB1C0() != 0) {
        if (*(u8 *)((u8 *)arg0 + 0xB5) == 0) {
            func_800AD594(actor, 4);
            func_800A4ACC(actor);
            if ((func_800AD9B4(value, actor) << 16) <= 0) {
                return;
            }
        } else {
            func_800AD594(actor, 0x10);
            func_800A4ACC(actor);
        }
        *(void **)((u8 *)arg0 + 0x8C) = D_80171A80;
    }

    if (D_80083462[0] & 0x80) {
        *(s16 *)((u8 *)arg0 + 0x92) = -0x20;
        if (*(u8 *)((u8 *)arg0 + 0xB5) != 0) {
            *(s16 *)((u8 *)arg0 + 0x92) = 0;
        }
    }
}
