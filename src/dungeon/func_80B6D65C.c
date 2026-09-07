#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80170E5C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { s16 s; u16 u; } unk_A4;   /* accessed as both */
} S_80170E5C_0;   /* arg0 in func_80170E5C */

typedef struct S_80170E5C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80170E5C_1;   /* arg3 in func_80170E5C */

typedef struct S_80170E5C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170E5C_2;   /* arg2 in func_80170E5C */


typedef struct S_80170E5C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170E5C_4;   /* origin in func_80170E5C */

typedef struct S_80170E5C_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E5C_5;   /* global in func_80170E5C */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s32 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_801713D4(void);
extern void func_8017162C(void *, void *, void *, void *);
extern s32 func_80171DD8(void *, void *, void *, void *);
extern void func_80171F9C(void *, void *, void *, void *);
extern s32 func_801720B4(void *, void *, void *, s32);
extern void func_80173AC0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *const D_80170808[];
extern u8 D_80173D0C[];
extern u8 D_80173D14[];
extern u8 D_80173D1C[];
extern u8 D_80173D3C[];
extern u8 D_80173D44[];
extern u8 D_80173D4C[];

void func_80170E5C(void *in0, void *in1, void *in2, void *in3)
{
    void *arg0;
    register void *arg1 ASM_REG("$16");   /* MATCH pin: load-bearing for the whole function shape */
    void *arg2;
    void *arg3;
    u8 *table;
    s32 result;
    s32 scratch;
    s16 countdown;
    u32 initial_flags = D_80083462;

    arg0 = in0;
    arg1 = in1;
    arg2 = in2;
    arg3 = in3;

    if (initial_flags & 0x1000) {
        ((S_80170E5C_0 *)arg0)->unk_9A = 0xE;
        func_801713D4();
        return;
    }

    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg1);   /* MATCH pin: retail basic-block layout depends on it */

    if (((S_80170E5C_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80170E5C_2 *)arg2)->unk_2C == D_80173D4C) {
            return;
        }
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80173D44;
        func_80047784(arg2,
            D_80173D44[((D_80083228 + ((S_80170E5C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_80170E5C_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80170E5C_2 *)arg2)->unk_2C == D_80173D4C) {
            ((S_80170E5C_0 *)arg0)->unk_9A = 0xD;
            ((S_80170E5C_0 *)arg0)->unk_9B = 1;
            ((S_80170E5C_0 *)arg0)->unk_8C = 0;
            ((S_80170E5C_1 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80173D44)) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80170E5C_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((S_80170E5C_0 *)arg0)->unk_9A != 0xE) {
            u8 state = 0xE;

            if (((S_80170E5C_2 *)arg2)->unk_2C != D_80173D0C) {
                s32 delay_value = 10;

                ((S_80170E5C_0 *)arg0)->unk_A4.s = delay_value;
                (*(void * *)((u8 *)arg2 + 0x2C)) = D_80173D14;
                func_80047784(arg2,
                    D_80173D14[((D_80083228 + ((S_80170E5C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170E5C_0 *)arg0)->unk_9A = state;
        }

        ((S_80170E5C_0 *)arg0)->unk_98 &= 0xFFF3;
        if (((S_80170E5C_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80173D1C)) {
                return;
            }
        }

        if (((S_80170E5C_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173AC0(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_80170E5C_2 *)arg2)->unk_24.at00.v, ((S_80170E5C_2 *)arg2)->unk_24.at01.v);
    ((S_80170E5C_2 *)arg2)->unk_26 = result;

    if (((S_80170E5C_1 *)arg3)->unk_6D > 0) {
        if (((S_80170E5C_1 *)arg3)->unk_1C & 0x20) {
            goto special_cleanup;
        }
        if (((S_80170E5C_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((S_80170E5C_1 *)arg3)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            ((S_80170E5C_1 *)arg3)->unk_46 |= 0x4000;
            if (!(((S_80170E5C_1 *)arg3)->unk_46 & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        {
            static void *const sw_keep[] = {
                &&aaf_cleanup, &&aaf_cleanup, &&aaf_cleanup,
                &&ordinary_cleanup,
                &&coords_case, &&coords_case, &&coords_case,
                &&handler_case, &&handler_case,
                &&ordinary_cleanup, &&ordinary_cleanup,
                &&special_cleanup,
            };
            u32 swi = (((S_80170E5C_1 *)arg3)->unk_46 & 0x3FFF) - 1;

            if (swi >= 12) {
                goto ordinary_cleanup;
            }
            (void)sw_keep;
            goto *D_80170808[swi];
        }

handler_case:
        if ((s16)func_80171DD8(arg0, arg1, arg2, arg3) == 0) {
            func_80171F9C(arg0, arg1, arg2, arg3);
        }
        return;

coords_case:
        {
            u8 *origin = D_80082E80;
            void *global;
            s32 direction;

            direction = func_800A0818(
                ((S_80170E5C_2 *)arg2)->unk_24.at00.v, ((S_80170E5C_2 *)arg2)->unk_24.at01.v,
                ((S_80170E5C_4 *)origin)->unk_24, ((S_80170E5C_4 *)origin)->unk_25,
                &scratch);
            global = D_800814A8;
            ((S_80170E5C_1 *)arg3)->unk_2A = direction;
            if (((S_80170E5C_5 *)global)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
        }

special_cleanup:
        func_800A9A0C(arg3);
        return;

aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_80173D3C, func_80170E5C);
        return;

ordinary_cleanup:
        func_8017162C(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((S_80170E5C_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((S_80170E5C_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(((S_80170E5C_2 *)arg2)->unk_24.at00.v,
                        ((S_80170E5C_2 *)arg2)->unk_24.at01.v, ((S_80170E5C_4 *)origin)->unk_24,
                        ((S_80170E5C_4 *)origin)->unk_25) != 0) {
                    ((S_80170E5C_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_80170E5C_2 *)arg2)->unk_24.at00.v, ((S_80170E5C_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E5C_4 *)origin)->unk_24, ((S_80170E5C_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170E5C_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    table = D_80173D0C;
    if (((S_80170E5C_2 *)arg2)->unk_2C == table) {
        return;
    }
    countdown = ((S_80170E5C_0 *)arg0)->unk_A4.u - 1;
    ((S_80170E5C_0 *)arg0)->unk_A4.s = countdown;
    if (countdown > 0) {
        return;
    }
    ((S_80170E5C_0 *)arg0)->unk_A4.s = -1;

    (*(void * *)((u8 *)arg2 + 0x2C)) = table;
    func_80047784(arg2,
        table[((D_80083228 + ((S_80170E5C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
}
