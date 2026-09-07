#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800C542C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_800C542C_0;   /* object in func_800C542C */

typedef struct S_800C542C_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    void * unk_08;
    s32 unk_0C;
    u8 pad_10[0x10];
    s16 unk_20;
} S_800C542C_1;   /* display in func_800C542C */

typedef struct S_800C542C_2_pre {
    void * unk_00;
    s32 unk_04;
    u8 pad_08[0x10];
} S_800C542C_2_pre;   /* the 0x18 bytes before arg0 in func_800C542C, addressed as arg0[-1] */

typedef struct S_800C542C_2 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_800C542C_2;   /* arg0 in func_800C542C */

typedef struct S_800C542C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C542C_3;   /* target in func_800C542C */

typedef struct S_800C542C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800C542C_4;   /* source in func_800C542C */

typedef struct S_800C542C_5 {
    u8 pad_00[0x1C];
    void * unk_1C;
    s32 unk_20;
    void * unk_24;
    u8 pad_28[0x2];
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
    s16 unk_32;
    u8 pad_34[0x2];
    s16 unk_36;
} S_800C542C_5;   /* record in func_800C542C */



extern u8 D_800C4F20[];
extern u8 D_800C55A0[];
extern u8 D_800DF630[];

extern void *func_8003FC64(s32);
extern void func_8004491C(void *, void *);
extern s16 rand(void *, void *);
extern void func_800A56E0(s32);

void *func_800C542C(void *arg0, s16 arg1, s32 arg2, s16 arg3)
{
    void *object;
    S_800C542C_1 *display;
    S_800C542C_4 *source;
    S_800C542C_3 *target;
    S_800C542C_5 *record;
    void *callback;
    void *call_object;
    register s16 stored_arg3 ASM_REG("$22");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s16 mode;
    s32 scaled;
    s32 parent;

    object = func_8003FC64(0x12);
    stored_arg3 = arg3;
    if (object != NULL) {
        call_object = object;
        ASM_KEEP(call_object);   /* MATCH pin: retail schedule: same instructions, different order without it */
        callback = D_800C4F20;
        ASM_KEEP(callback);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_800C542C_0 *)object)->unk_10 = callback;
        func_8004491C(call_object, D_800C55A0);

        display = ((S_800C542C_0 *)object)->unk_0C;
        display->unk_0C = 0x808080;
        display->unk_08 = D_800DF630;
        display->unk_06 = 0xC;

        source = ((S_800C542C_2_pre *)arg0)[-1].unk_00;
        target = ((S_800C542C_0 *)object)->unk_08;
        target->unk_02 = source->unk_02;
        target->unk_06 = source->unk_06;
        record = (u8 *)object + 0x20;
        target->unk_0A = source->unk_0A;

        scaled = arg2 << 0x10;
        record->unk_30 = arg1;
        record->unk_1C = source;
        parent = ((S_800C542C_2_pre *)arg0)[-1].unk_04;
        record->unk_2E = (s16)(scaled >> 5);
        record->unk_24 = arg0;
        record->unk_20 = parent;
        display->unk_20 = 0x2000;
        record->unk_32 = 0x400;
        record->unk_2C = rand(source, display);

        if (arg3 == 1) {
            record->unk_2A = 0;
        } else {
            if (arg3 == 0) {
                func_800A56E0(0x802);
                mode = 0x10;
            } else {
                func_800A56E0(0x802);
                mode = 0x20;
            }
            record->unk_2A = mode;
        }

        record->unk_36 = stored_arg3;
        ((S_800C542C_2 *)arg0)->unk_14 |= 0x100000;
    }
    return object;
}

/* MECHANISM: The true rowbase function uses a 0x30 frame with s2/s4/s5/s3
   holding the four arguments, a post-call s6 copy, and s1/s0 object bases.
   The 800C5558/800C555C targets are local mode-store joins, not tail calls. */
