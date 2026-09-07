#include "common.h"

typedef struct S_80171094_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xA];
    union { s16 s; u16 u; } unk_A6;   /* accessed as both */
    u8 pad_A8[0x4];
    union { s16 s; u16 u; } unk_AC;   /* accessed as both */
} S_80171094_0;   /* arg0 in func_80171094 */

typedef struct S_80171094_1 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    u32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    union { s16 s; u16 u; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x1C];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_80171094_1;   /* arg3 in func_80171094 */

typedef struct S_80171094_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80171094_2;   /* arg2 in func_80171094 */

typedef struct S_80171094_3 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80171094_3;   /* D_800814A8 in func_80171094 */

typedef struct S_80171094_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171094_4;   /* actor in func_80171094 */

typedef struct S_80171094_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171094_5;   /* origin in func_80171094 */



typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_801716D8(void);
extern void func_801718B4(void *, void *, void *, void *);
extern s32 func_80171FFC(void *, void *, void *, void *);
extern void func_801721C0(void *, void *, void *, void *);
extern s32 func_80172438(void *, void *, void *, void *);
extern void func_8017272C(void *, void *, void *, void *);
extern void func_8017283C(void *, void *, void *, void *);
extern void func_8017294C(void *, void *, void *, void *);
extern s32 func_80172A5C(void *, void *, void *, s32);
extern void func_80174520(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170838[16];
extern u8 D_80171094[];
extern u8 D_80176460[];
extern u8 D_80176468[];
extern u8 D_80176470[];
extern u8 D_801764A8[];

void func_80171094(void *arg0_, void *arg1_, void *arg2_, void *arg3_)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
        &&jt_s0, &&jt_s1, &&jt_s2, &&jt_s3, &&jt_s4
    };
    void *arg0 = arg0_;
    void *arg1 = arg1_;
    register void *arg2 ASM_REG("$18") = arg2_;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    void *arg3 = arg3_;
    s16 sp18;
    s8 tile;
    s32 kind;
    u16 field46;

    if (D_80083462 & 0x1000) {
        ((S_80171094_0 *)arg0)->unk_9A = 14;
        func_801716D8();
        return;
    }

    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg2);   /* MATCH pin: retail basic-block layout depends on it */

    if (((S_80171094_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80171094_2 *)arg2)->unk_2C == D_80176470) {
            return;
        }
        {
            u8 *table = D_80176468;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(
                arg2,
                table[((D_80083228 + ((S_80171094_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171094_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80171094_2 *)arg2)->unk_2C == D_80176470) {
            ((S_80171094_0 *)arg0)->unk_9A = 13;
            ((S_80171094_0 *)arg0)->unk_9B = 1;
            ((S_80171094_0 *)arg0)->unk_8C = 0;
            ((S_80171094_1 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80176468) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80171094_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((S_80171094_0 *)arg0)->unk_9A != 14) {
            ((S_80171094_0 *)arg0)->unk_9A = 14;
        }

        if (((S_80171094_2 *)arg2)->unk_2C != D_80176460) {
            u8 *table = D_80176460;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(
                arg2,
                table[((D_80083228 + ((S_80171094_1 *)arg3)->unk_2A.s + 0x100) >> 9) & 7],
                0);
            ((S_80171094_2 *)arg2)->unk_05 = 1;
            ((S_80171094_0 *)arg0)->unk_A6.s = 0;
            ((S_80171094_0 *)arg0)->unk_AC.s = 0;
        }

        {
            u32 flags = ((S_80171094_1 *)arg3)->unk_1C;
            u16 tail_value;

            if (flags & 0x20) {
                ((S_80171094_1 *)arg3)->unk_1C = flags & ~0x40000;
                tail_value = ((S_80171094_0 *)arg0)->unk_98 | 8;
                goto store_98;
            }

            ((S_80171094_1 *)arg3)->unk_1C = flags | 0x40000;
            tail_value = ((S_80171094_0 *)arg0)->unk_98 & 0xFFF7;

store_98:
            ((S_80171094_0 *)arg0)->unk_98 = tail_value;
        }

        if (((S_80171094_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_801764A8) != 0) {
                return;
            }
        }

        if (((S_80171094_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            ((S_80171094_0 *)arg0)->unk_92 -= ((S_80171094_0 *)arg0)->unk_A6.u;
            ((S_80171094_0 *)arg0)->unk_A6.u = 0;
            ((S_80171094_0 *)arg0)->unk_AC.u = 0;
            func_80174520(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(((S_80171094_2 *)arg2)->unk_24.at00.v, ((S_80171094_2 *)arg2)->unk_24.at01.v);
    ((S_80171094_2 *)arg2)->unk_26 = tile;

    if (((S_80171094_1 *)arg3)->unk_6D > 0) {
        if (((S_80171094_1 *)arg3)->unk_1C & 0x20) {
            goto jt_c12;
        }
        if (((S_80171094_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }
        field46 = ((S_80171094_1 *)arg3)->unk_46;
        if ((field46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)((S_80171094_3 *)D_800814A8)->unk_58 + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172A5C(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            field46 = ((S_80171094_1 *)arg3)->unk_46 | 0x4000;
            ((S_80171094_1 *)arg3)->unk_46 = field46;
            if ((field46 & 0x8000) == 0) {
                goto jt_default;
            }
        }

        kind = (((S_80171094_1 *)arg3)->unk_46 & 0x3FFF) - 1;
        if ((u32)kind >= 12U) {
            goto jt_default;
        }
        (void)jt_keep;
        goto *D_80170808[kind];

jt_c9:
        if ((s16)func_80171FFC(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_801721C0(arg0, arg1, arg2, arg3);
        return;

jt_c8:
        if (((S_80171094_1 *)arg3)->unk_1C & 0x400) {
            register s32 val ASM_REG("$2");   /* MATCH pin: retail register colouring depends on it */
            val = ((S_80171094_1 *)arg3)->unk_14;
            if (val >= 0) {
                val |= 0x80000000;
                ((S_80171094_1 *)arg3)->unk_14 = val;
                ((S_80171094_1 *)arg3)->unk_2A.u += (func_800A6D30() & 7) << 9;
            }
        }
        kind = (s16)(func_80172438(arg0, arg1, arg2, arg3) + 1);
        if ((u32)kind >= 5U) {
            return;
        }
        goto *(((void **)D_80170838)[kind]);

jt_s0:
        func_8017272C(arg0, arg1, arg2, arg3);
        return;

jt_s1:
        func_8017283C(arg0, arg1, arg2, arg3);
        return;

jt_s2:
        func_8017294C(arg0, arg1, arg2, arg3);
        return;

jt_s3:
jt_s4:
jt_c5:
jt_c6:
jt_c7:
        {
            s16 res = func_800A0818(
                ((S_80171094_2 *)arg2)->unk_24.at00.v, ((S_80171094_2 *)arg2)->unk_24.at01.v,
                D_80082E80[0x24], D_80082E80[0x25], &sp18);
            void *actor = D_800814A8;
            ((S_80171094_1 *)arg3)->unk_2A.s = res;
            if (((S_80171094_4 *)actor)->unk_9A == 0x11) {
                goto jt_call;
            }
        }

jt_c12:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
jt_call:
        func_800AAF00(arg0, arg1, arg2, D_80176460, D_80171094);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_801718B4(arg0, arg1, arg2, arg3);
        return;
    }

    {
        u32 flags = ((S_80171094_1 *)arg3)->unk_1C;

        if (!(flags & 0x2000)) {
            s32 index = (s8)tile;

            if ((index < 0) ||
                !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
                if (!(flags & 0x430)) {
                    void *origin = D_80082E80;
                    if ((s16)func_8009FD7C(
                            ((S_80171094_2 *)arg2)->unk_24.at00.v, ((S_80171094_2 *)arg2)->unk_24.at01.v,
                            ((S_80171094_5 *)origin)->unk_24, ((S_80171094_5 *)origin)->unk_25) != 0) {
                        ((S_80171094_1 *)arg3)->unk_2A.s = func_800A0818(
                            ((S_80171094_2 *)arg2)->unk_24.at00.v, ((S_80171094_2 *)arg2)->unk_24.at01.v,
                            ((S_80171094_5 *)origin)->unk_24, ((S_80171094_5 *)origin)->unk_25,
                            &sp18);
                    }
                }
            }
        }
    }
}
