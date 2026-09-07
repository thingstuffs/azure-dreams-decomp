#include "common.h"

extern u16 D_80013714[5];
extern u8 D_80083460[0x14];
extern u8 *D_800E3D7C[];
extern u8 D_80175392[];

extern void func_800353F4(void *, void *);
extern void func_80164BA4(void *);
extern void func_8016A36C(void);

void func_8016CAE8(void *arg0, void *arg1, void *arg2, u8 *arg3)
{
    s32 i;
    u16 count;
    u16 flags;
    u8 *base;
    u8 *object;
    u8 *flags_page;
    u8 *state;

    flags_page = (u8 *)0x80010000;
    state = D_80083460;
    
    flags = *(u16 *)(flags_page + 0x3714);
    count = *(u16 *)(state + 0xA);
    *(u16 *)(flags_page + 0x3714) = flags | 8;
    *(u16 *)(state + 0xA) = count + 1;
    if (*(u32 *)(state + 0x10) == (u32)(arg3 - 0x20)) {
        *(u32 *)(state + 0x10) &= 0x7FFFFFFF;
    }

    func_800353F4(D_80175392, state);
    i = 0;
    arg3[0x6D] = 0;
    ((u8 *)arg0)[0x9B] = 0;
    *(void **)((u8 *)arg0 + 0x8C) = (void *)func_8016A36C;

    do {
        object = *(u8 **)(D_800E3D7C[0] + (i * 4) + 0xAC);
        if (object != 0) {
            func_80164BA4(object);
            base = *(u8 **)(D_800E3D7C[0] + (i * 4) + 0xAC) - 0x20;
            *(u32 *)(base + 0x10) |= 0x80000000;
        }
        i++;
    } while (i < 2);
}

/* MECHANISM: The natural C holds arg0/arg3 and emits the 0x28 frame with s4,s0,s3,s2,s1.
   A guarded a0 page-base pin plus tied volatile keep places both global bases before the late saves.
   Separate u16 flags/count loads keep v0/v1 live together and fill the flags-load delay slot. */
