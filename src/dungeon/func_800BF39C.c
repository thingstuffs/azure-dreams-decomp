#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C4AFC_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x18];
    void * unk_1C;
    u16 unk_20;
    u16 unk_22;
    u16 unk_24;
    u8 pad_26[0x2];
    s32 unk_28;
} S_800C4AFC_0;   /* state in func_800C4AFC */

typedef struct S_800C4AFC_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    void * unk_10;
} S_800C4AFC_1;   /* object in func_800C4AFC */

typedef struct S_800C4AFC_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C4AFC_2;   /* arg0 in func_800C4AFC */

typedef struct S_800C4AFC_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C4AFC_3;   /* (void *)temp in func_800C4AFC */



extern void *func_8003FD64(s32, void *);
extern void func_800B835C(void *, s32 *, s32, s32);
extern void func_800A56E0(s32, void *);
extern void func_800C4944(void);

extern u8 D_80083498[12];
extern u8 D_800DCF78[12];
extern u8 D_80083460[12];

void func_800C4AFC(S_800C4AFC_2 *arg0, s32 arg1, s32 arg2)
{
    s32 init[2];
    void *object;
    register unsigned long temp ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
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
        ((S_800C4AFC_0 *)state)->unk_02 = 0x40;
        ((S_800C4AFC_1 *)object)->unk_10 = (void *)func_800C4944;
        temp = (long)((S_800C4AFC_1 *)object)->unk_08;
        value = arg0->unk_02;
        ((S_800C4AFC_3 *)((void *)temp))->unk_02 = value;
        ((S_800C4AFC_0 *)state)->unk_20 = value;
        value = arg0->unk_06;
        ((S_800C4AFC_3 *)((void *)temp))->unk_06 = value;
        ((S_800C4AFC_0 *)state)->unk_22 = value;
        value = arg0->unk_0A;
        ((S_800C4AFC_3 *)((void *)temp))->unk_0A = value;
        ((S_800C4AFC_0 *)state)->unk_24 = value;
        ((S_800C4AFC_0 *)state)->unk_1C = arg0;
        ((S_800C4AFC_0 *)state)->unk_28 = arg2;
        func_800A56E0(0x702, state);
        temp = (unsigned long)D_80083460;
        ((S_800C4AFC_3 *)((void *)temp))->unk_0A++;
}

/* MECHANISM: The 0x30 frame, s1/s2/s3 argument holds, two-word init record, and callee ABIs
   reproduce the retail structure. Moving init[1]'s store immediately before func_800B835C
   schedules move a3,zero at word 25 and the stack store into the jal delay slot at word 28. */
