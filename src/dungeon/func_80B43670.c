#include "common.h"
#include "records/Rec_D_800814A8.h"


typedef struct DungeonRecord {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(u8, u8);
extern s32 func_8009FD7C(u8, u8, u8, u8);
extern s16 func_800A0818();
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_801713B0(void) __attribute__((noreturn));
extern void func_801713D4(void *);
extern void func_8017162C(void *, void *, void *, void *);
extern s32 func_80171DD8(void *, void *, void *, void *);
extern void func_80171F9C(void *, void *, void *, void *);
extern s32 func_801720B4(void *, void *, void *, s32);
extern void func_80173D64(void *, void *, void *, void *);
extern void func_8017526C(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170E70[];
extern u8 D_80175A54[];
extern u8 D_80175A5C[];
extern u8 D_80175A8C[];
extern u8 D_80175A94[];
extern u8 D_80175A9C[];


typedef struct S_80170E70_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x66];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170E70_0;   /* arg0 in func_80170E70 */

typedef struct S_80170E70_1 {
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
} S_80170E70_1;   /* arg3 in func_80170E70 */

typedef struct S_80170E70_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80170E70_2;   /* arg2 in func_80170E70 */


typedef struct S_80170E70_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E70_4;   /* owner in func_80170E70 */

typedef struct S_80170E70_5 {
    u8 pad_00[0x10];
    s16 * unk_10;
} S_80170E70_5;   /* stack_base in func_80170E70 */

void func_80170E70(void *in0, void *in1, void *in2, void *in3)
{
    u8 *effect_tbl;
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    void *arg0 = in0;
    void *arg1 = in1;
    void *arg2 = in2;
    register void *arg3 ASM_REG("$18") = in3;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    s32 state;
    u32 origin_page;
#ifdef __mips__
    register u8 *stack_base ASM_REG("$29");   /* MATCH pin: retail callee-saved set / frame layout depends on it */
#endif
    s16 sp18;
    s16 path_result;
    s32 flags;
    s32 kind;
    s8 tile;
    s32 late_a0;
    s32 late_a1;
    s32 current_state;
    u16 field46;
    void *fifth;
    void *owner;

    if (D_80083462 & 0x1000) {
        ((S_80170E70_0 *)arg0)->unk_9A = 14;
        func_801713D4(arg0);
        func_801713B0();
    }

    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if (((S_80170E70_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80170E70_2 *)arg2)->unk_2C == D_80175A9C) {
            return;
        }
        {
            u8 *et = D_80175A94;
            (*(void * *)((u8 *)arg2 + (0x2C))) = et;
            func_80047784(
                arg2,
                et[((D_80083228 + ((S_80170E70_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
        }
        return;
    }

    if (((S_80170E70_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80170E70_2 *)arg2)->unk_2C == D_80175A9C) {
            ((S_80170E70_0 *)arg0)->unk_9A = 13;
            ((S_80170E70_0 *)arg0)->unk_9B = 1;
            ((S_80170E70_0 *)arg0)->unk_8C = 0;
            ((S_80170E70_1 *)arg3)->unk_1C &= ~0x40000;
            func_801713B0();
        }
        if (func_800AA924(arg0, arg1, arg2, D_80175A94) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80170E70_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_801713B0();
        }

        current_state = ((S_80170E70_0 *)arg0)->unk_9A;
        ASM_KEEP(current_state);   /* MATCH pin: retail delay-slot fill depends on it */
        state = 14;
        if (current_state != state) {
            u8 *effect = D_80175A54;

            if (((S_80170E70_2 *)arg2)->unk_2C != effect) {
                (*(void * *)((u8 *)arg2 + (0x2C))) = effect;
                func_80047784(
                    arg2,
                    effect[((D_80083228 + ((S_80170E70_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_80170E70_0 *)arg0)->unk_9A = state;
        }

        ((S_80170E70_0 *)arg0)->unk_98 &= 0xFFF3;
        if (((S_80170E70_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175A5C) != 0) {
                return;
            }
        }

        if (((S_80170E70_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173D64(arg0, arg1, arg2, arg3);
            func_801713B0();
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            if ((s16)func_800AAB10(arg0, arg1, arg2, arg3) != 0) {
                func_8017526C(arg0, arg1, arg2, arg3);
            }
        }
    }

    tile = func_8009FB34(((S_80170E70_2 *)arg2)->unk_24.at00.v, ((S_80170E70_2 *)arg2)->unk_24.at01.v);
    ((S_80170E70_2 *)arg2)->unk_26 = tile;

    if (((S_80170E70_1 *)arg3)->unk_6D > 0) {
        if (((S_80170E70_1 *)arg3)->unk_1C & 0x20) {
            goto jt_c12;
        }
        if (((S_80170E70_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }

        field46 = ((S_80170E70_1 *)arg3)->unk_46;
        if ((field46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_801720B4(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            field46 = ((S_80170E70_1 *)arg3)->unk_46 | 0x4000;
            ((S_80170E70_1 *)arg3)->unk_46 = field46;
            if ((field46 & 0x8000) == 0) {
                goto jt_default;
            }
        }

        kind = (((S_80170E70_1 *)arg3)->unk_46 & 0x3FFF) - 1;
        if ((u32)kind >= 12U) {
            goto jt_default;
        }
        (void)jt_keep;
        goto *D_80170808[kind];

jt_c8:
jt_c9:
        if ((s16)func_80171DD8(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_80171F9C(arg0, arg1, arg2, arg3);
        func_801713B0();

jt_c5:
jt_c6:
jt_c7:
        path_result = func_800A0818(
            ((S_80170E70_2 *)arg2)->unk_24.at00.v, ((S_80170E70_2 *)arg2)->unk_24.at01.v,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        owner = D_800814A8;
        ((S_80170E70_1 *)arg3)->unk_2A = path_result;
        if (((S_80170E70_4 *)owner)->unk_9A == 0x11) {
            fifth = D_80170E70;
            goto jt_call;
        }

jt_c12:
        func_800A9A0C(arg3);
        func_801713B0();

jt_c1:
jt_c2:
jt_c3:
        fifth = D_80170E70;

jt_call:
        func_800AAF00(arg0, arg1, arg2, D_80175A8C, fifth);
        func_801713B0();

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_8017162C(arg0, arg1, arg2, arg3);
        func_801713B0();
    }

    flags = ((S_80170E70_1 *)arg3)->unk_1C;
    if ((flags & 0x2000) == 0) {
        if ((tile < 0) ||
            ((((DungeonRecord *)D_800E2970)[tile].flags & 2) == 0)) {
            if ((flags & 0x430) == 0) {
                origin_page = 0x80080000;
                ASM_KEEP(origin_page);   /* MATCH pin: load-bearing for the whole function shape */
                arg0 = (void *)(origin_page + 0x2E80);
                if ((s16)func_8009FD7C(
                        ((S_80170E70_2 *)arg2)->unk_24.at00.v, ((S_80170E70_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E70_0 *)arg0)->unk_24, ((S_80170E70_0 *)arg0)->unk_25) != 0) {
#ifdef __mips__
                    late_a0 = ((S_80170E70_2 *)arg2)->unk_24.at00.v;
                    late_a1 = ((S_80170E70_2 *)arg2)->unk_24.at01.v;
                    ((S_80170E70_5 *)stack_base)->unk_10 = &sp18;
                    ((S_80170E70_1 *)arg3)->unk_2A = func_800A0818(
                        late_a0, late_a1,
                        ((S_80170E70_0 *)arg0)->unk_24, ((S_80170E70_0 *)arg0)->unk_25);
#else
                    ((S_80170E70_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_80170E70_2 *)arg2)->unk_24.at00.v, ((S_80170E70_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E70_0 *)arg0)->unk_24, ((S_80170E70_0 *)arg0)->unk_25, &sp18);
#endif
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170E70_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    effect_tbl = D_80175A54;
    if (((S_80170E70_2 *)arg2)->unk_2C == effect_tbl) {
        return;
    }
    ASM_KEEP(arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    {
        u8 *et = effect_tbl;
        (*(void * *)((u8 *)arg2 + (0x2C))) = et;
        func_80047784(
            arg2,
            et[((D_80083228 + ((S_80170E70_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
    }
}
