#include "common.h"

typedef struct DungeonState {
    u8 pad0[0xA];
    u16 counter;
} DungeonState;

extern DungeonState D_80083460;
extern u8 D_800E0458[];
extern u8 D_800E0C78[];

extern s32 func_800990FC(void *, void *);
extern s32 func_80099194(void *, s32);
extern s32 func_80099254(void *, s32);
extern void func_80099290(s32);
extern s32 func_8009929C(s32, s32);
extern s32 func_80099734(void *, s32);
extern void func_800A5720(s32);

void func_800ACF88(void *arg0, void *arg1) {
    u16 *flag_page;
    void *original_arg0;
    s32 first_result;
    s32 result;
    u16 counter;

    flag_page = (u16 *)0x80010000;
    original_arg0 = arg0;
    if (!(flag_page[0x3714 / 2] & 1)) {
        arg1 = (void *)0x800E0000;
        arg0 = (void *)0x80080000;
        ASM_KEEP(arg0);   /* MATCH pin: load-bearing for the whole function shape */
        arg0 = (u8 *)arg0 + 0x3460;
        counter = ((DungeonState *)arg0)->counter;
        ((s8 *)arg1)[-0x30B1] = 1;
        ((DungeonState *)arg0)->counter = counter + 1;
    }
    first_result = func_800990FC(arg0, arg1);
    result = func_80099194(D_800E0C78, func_80099734(original_arg0, first_result));
    if (!(flag_page[0x3714 / 2] & 1)) {
        result = func_80099254(D_800E0458,
            func_8009929C(0x4C, func_8009929C(0x11, result)));
    }
    func_80099290(result);
    func_800A5720(first_result);
}

/* MECHANISM: cdk holds the raw 0x80010000 flag page in s1; a counter local gives
   lhu/li/sb/addiu/sh without a load-delay nop. ASM_KEEP separates 0x80080000
   from +0x3460 so it emits lui/addiu, while original arg0/result reuse s0. */
