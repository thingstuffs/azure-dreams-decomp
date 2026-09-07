#include "common.h"

#ifndef NULL
#define NULL 0
#endif

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *func_8003FD64(s32, void *);
extern void func_800B835C(void *, s32 *, s32, s32);
extern void func_800A56E0(s32, void *);
extern void func_800C4944(void);

extern u8 D_80083498[12];
extern u8 D_800DCF78[12];
extern u8 D_80083460[12];

void func_800C4AFC(void *arg0, s32 arg1, s32 arg2)
{
    s32 init[2];
    void *object;
    register unsigned long temp ASM_REG("$3");
    u8 *state;
    u8 *effect;
    u16 value;

    object = func_8003FD64(0x202, D_80083498);
    if (object == NULL) {
        return;
    }

        init[0] = 0x01000340;
        temp = 0x00200020;
        effect = D_800DCF78;
        effect -= 0x10;
        *(volatile s32 *)D_800DCF78 = arg1;
        init[1] = (s32)temp;
        func_800B835C(effect, init, 1, 0);

        state = (u8 *)object + 0x20;
        FIELD(state, u16, 2) = 0x40;
        FIELD(object, void *, 0x10) = (void *)func_800C4944;
        temp = (long)FIELD(object, void *, 8);
        value = FIELD(arg0, u16, 2);
        FIELD((void *)temp, u16, 2) = value;
        FIELD(state, u16, 0x20) = value;
        value = FIELD(arg0, u16, 6);
        FIELD((void *)temp, u16, 6) = value;
        FIELD(state, u16, 0x22) = value;
        value = FIELD(arg0, u16, 0xA);
        FIELD((void *)temp, u16, 0xA) = value;
        FIELD(state, u16, 0x24) = value;
        FIELD(state, void *, 0x1C) = arg0;
        FIELD(state, s32, 0x28) = arg2;
        func_800A56E0(0x702, state);
        temp = (unsigned long)D_80083460;
        FIELD((void *)temp, u16, 0xA)++;
}

/* MECHANISM: The 0x30 frame, s1/s2/s3 argument holds, two-word init record, and callee ABIs
   reproduce the retail structure. Moving init[1]'s store immediately before func_800B835C
   schedules move a3,zero at word 25 and the stack store into the jal delay slot at word 28. */
