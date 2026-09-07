#include "common.h"

typedef struct S_800D904C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    s16 unk_8A;
} S_800D904C_0;   /* state in func_800D904C */

typedef struct S_800D904C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    void * unk_2C;
} S_800D904C_1;   /* arg2 in func_800D904C */

typedef struct S_800D904C_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800D904C_2;   /* entry in func_800D904C */

typedef struct S_800D904C_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_800D904C_3;   /* arg0 in func_800D904C */

typedef struct S_800D904C_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_800D904C_4;   /* (u8 *)state + ((S_800D904C_0 *)state)->unk_8A in func_800D904C */



extern void func_8003DB94(void *, void *, s32);
extern void func_8009A21C(s32, s32, s32);
extern void func_8009A3D0(s32, s32, s32);
extern s16 func_8009A66C(s16, void *, void *, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800D910C(void *, void *, void *);
extern void func_800D9240(void);
extern void func_800D9298(void);
extern void func_800D9820(void *, s32, void *, void *);

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800E260C[];

void func_800D904C(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    register void *state ASM_REG("$17") = arg3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *current;
    s32 mode;
    s16 first_result;
    s16 second_result;
    s32 old_x;
    s32 old_y;
    s32 count;
    void *entry;

    if ((((S_800D904C_0 *)state)->unk_71.s > 0) &&
        ((s32)((S_800D904C_0 *)state)->unk_71.u > ((S_800D904C_0 *)state)->unk_8A)) {
        current = ((S_800D904C_1 *)arg2)->unk_2C;
        if (current != D_800E260C) {
            void *dispatch;

            (*(void * *)((u8 *)arg2 + 0x2C)) = D_800E260C;
            dispatch = D_800E260C +
                (((D_80083228 + ((S_800D904C_0 *)state)->unk_2A + 0x100) >> 7) & 0x1C);
            ASM_TAILSLOT_PIN(dispatch);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
            func_800D910C(arg2, D_800E260C, current);
            return;
        }

        if (((S_800D904C_1 *)arg2)->unk_14 & 0x6000) {
            func_8003DB94(
                arg2,
                *(void **)(D_800E260C +
                    (((D_80083228 + ((S_800D904C_0 *)state)->unk_2A + 0x100) >> 7) & 0x1C)),
                0);
        }

        old_x = ((S_800D904C_1 *)arg2)->unk_24;
        old_y = ((S_800D904C_1 *)arg2)->unk_25;
        mode = 0x3000;
        if (((S_800D904C_0 *)state)->unk_1C & 0x2000) {
            mode = 0x300;
        }
        func_8009A3D0(old_x, old_y, mode);

        entry = (u8 *)state + ((S_800D904C_0 *)state)->unk_8A;
        first_result = func_800A0818(old_x, old_y,
                                    ((S_800D904C_2 *)entry)->unk_74,
                                    ((S_800D904C_2 *)entry)->unk_7C,
                                    (u8 *)arg0 + 0x98);
        second_result = func_8009A66C(first_result, arg2, state, 0x20);

        ((S_800D904C_1 *)arg2)->unk_24 =
            ((S_800D904C_4 *)((u8 *)state + ((S_800D904C_0 *)state)->unk_8A))->unk_74;
        mode = 0x3000;
        ((S_800D904C_1 *)arg2)->unk_25 =
            ((S_800D904C_4 *)((u8 *)state + ((S_800D904C_0 *)state)->unk_8A))->unk_7C;
        ((S_800D904C_0 *)state)->unk_8A = (u16)((S_800D904C_0 *)state)->unk_8A + 1;

        {
            s32 nx = ((S_800D904C_1 *)arg2)->unk_24;
            s32 ny = ((S_800D904C_1 *)arg2)->unk_25;
            if (((S_800D904C_0 *)state)->unk_1C & 0x2000) {
                mode = 0x300;
            }
            func_8009A21C(nx, ny, mode);
        }

        ((S_800D904C_0 *)state)->unk_2A = first_result;
        if ((second_result == 3) &&
            ((D_80083462 & 0x80) || (((S_800D904C_1 *)arg2)->unk_14 & 0x8000))) {
            ((S_800D904C_3 *)arg0)->unk_9A = 0xF;
            func_800D9240();
            return;
        }

        func_800D9820(arg0, arg1, arg2, state);
        ((S_800D904C_3 *)arg0)->unk_8C = 0;
        (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
        if (D_80083462 & 0x80) {
            ((S_800D904C_3 *)arg0)->unk_96 = 0;
            return;
        }

        ((S_800D904C_3 *)arg0)->unk_96 = 8;
        count = ((S_800D904C_0 *)state)->unk_71.u;
        if (count > 0) {
            ((S_800D904C_3 *)arg0)->unk_96 = 8 / count;
        }
    }
}
