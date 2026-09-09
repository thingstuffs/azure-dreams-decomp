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
extern s16 func_800A0818(u8, u8, u8, u8, s16 *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);

extern void func_80171460(void *);
extern void func_801716A4(void *, void *, void *, void *);
extern s32 func_80171E38(void *, void *, void *, void *);
extern void func_80171FFC(void *, void *, void *, void *);
extern s32 func_80172114(void *, void *, void *, s32);
extern void func_801737B8(void *, void *, void *, void *);
extern void func_80173C40(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170EE4[];
extern u8 D_801765D8[];
extern u8 D_801765E0[];
extern u8 D_80176650[];
extern u8 D_80176660[];
extern u8 D_80176678[];


typedef struct S_80170EE4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80170EE4_0;   /* arg0 in func_80170EE4 */

typedef struct S_80170EE4_1 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x4];
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
} S_80170EE4_1;   /* arg3 in func_80170EE4 */

typedef struct S_80170EE4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80170EE4_2;   /* arg2 in func_80170EE4 */


typedef struct S_80170EE4_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170EE4_4;   /* actor in func_80170EE4 */

typedef struct S_80170EE4_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170EE4_5;   /* origin in func_80170EE4 */

void func_80170EE4(void *arg0_, void *arg1_, void *arg2_, void *arg3_)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    void *arg0 = arg0_;
    void *arg1 = arg1_;
    void *arg2 = arg2_;
    register void *arg3 ASM_REG("$18") = arg3_;   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u32 initial_flags = D_80083462;
    s16 sp18;
    s32 flags;
    s32 kind;
    s8 tile;
    s16 result;
    u16 field46;
    register void *state ASM_REG("$5"); /* MATCH: merge the selected table in a1 at the shared update. */
    u8 *table;
    void *origin;
    void *actor;

    if (initial_flags & 0x1000) {
        ((S_80170EE4_0 *)arg0)->unk_9A = 14;
        func_80171460(arg0);
        return;
    }

    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg3);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */

    if (((S_80170EE4_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80170EE4_2 *)arg2)->unk_2C == D_80176650) {
            return;
        }
        state = D_80176678;
        goto update_table;
    }

    if (((S_80170EE4_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80170EE4_2 *)arg2)->unk_2C == D_80176650) {
            ((S_80170EE4_0 *)arg0)->unk_9A = 13;
            ((S_80170EE4_0 *)arg0)->unk_9B = 1;
            ((S_80170EE4_0 *)arg0)->unk_8C = 0;
            ((S_80170EE4_1 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80176678) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80170EE4_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        {
            u8 current_state = 14;
            if (((S_80170EE4_0 *)arg0)->unk_9A != current_state) {
                if (((S_80170EE4_2 *)arg2)->unk_2C != D_801765D8) {
                    (*(u8 * *)((u8 *)arg2 + (0x2C))) = D_801765D8;
                    func_80047784(
                        arg2,
                        D_801765D8[((D_80083228 + ((S_80170EE4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80170EE4_0 *)arg0)->unk_9A = current_state;
            }
        }

        ((S_80170EE4_0 *)arg0)->unk_98 &= 0xFFF3;

        if (((S_80170EE4_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_801765E0) != 0) {
                return;
            }
        }

        if (((S_80170EE4_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_801737B8(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(((S_80170EE4_2 *)arg2)->unk_24.at00.v, ((S_80170EE4_2 *)arg2)->unk_24.at01.v);
    ((S_80170EE4_2 *)arg2)->unk_26 = tile;

    if (((S_80170EE4_1 *)arg3)->unk_6D > 0) {
        if (((S_80170EE4_1 *)arg3)->unk_1C & 0x20) {
            goto jt_c12;
        }
        if (((S_80170EE4_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }
        field46 = ((S_80170EE4_1 *)arg3)->unk_46;
        if ((field46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172114(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            field46 = ((S_80170EE4_1 *)arg3)->unk_46 | 0x4000;
            ((S_80170EE4_1 *)arg3)->unk_46 = field46;
            if ((field46 & 0x8000) == 0) {
                goto jt_default;
            }
        }

        kind = (((S_80170EE4_1 *)arg3)->unk_46 & 0x3FFF) - 1;
        if ((u32)kind >= 12U) {
            goto jt_default;
        }
        (void)jt_keep;
        goto *D_80170808[kind];

jt_c9:
        if ((s16)func_80171E38(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        goto call_80171FFC;

jt_c8:
        if (!(((S_80170EE4_1 *)arg3)->unk_14 & 0x20000000)) {
            func_80173C40(arg0, arg1, arg2, arg3);
            return;
        }
call_80171FFC:
        func_80171FFC(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        result = func_800A0818(
            ((S_80170EE4_2 *)arg2)->unk_24.at00.v, ((S_80170EE4_2 *)arg2)->unk_24.at01.v,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        actor = D_800814A8;
        ((S_80170EE4_1 *)arg3)->unk_2A = result;
        if (((S_80170EE4_4 *)actor)->unk_9A == 0x11) {
            goto jt_call;
        }

jt_c12:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
jt_call:
        func_800AAF00(arg0, arg1, arg2, D_80176660, D_80170EE4);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_801716A4(arg0, arg1, arg2, arg3);
        return;
    }

    flags = ((S_80170EE4_1 *)arg3)->unk_1C;
    if (!(flags & 0x2000)) {
        if ((tile < 0) ||
            !(((DungeonRecord *)D_800E2970)[tile].flags & 2)) {
            if (!(flags & 0x430)) {
                origin = D_80082E80;
                if ((s16)func_8009FD7C(
                        ((S_80170EE4_2 *)arg2)->unk_24.at00.v, ((S_80170EE4_2 *)arg2)->unk_24.at01.v,
                        ((S_80170EE4_5 *)origin)->unk_24, ((S_80170EE4_5 *)origin)->unk_25) != 0) {
                    ((S_80170EE4_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_80170EE4_2 *)arg2)->unk_24.at00.v, ((S_80170EE4_2 *)arg2)->unk_24.at01.v,
                        ((S_80170EE4_5 *)origin)->unk_24, ((S_80170EE4_5 *)origin)->unk_25, &sp18);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170EE4_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    table = D_801765D8;
    if (((S_80170EE4_2 *)arg2)->unk_2C == table) {
        return;
    }
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    state = table;
update_table:
    table = state;
    (*(u8 * *)((u8 *)arg2 + (0x2C))) = table;
    func_80047784(
        arg2,
        *(u8 *)((((D_80083228 + ((S_80170EE4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) + (u32)table),
        0);
}
