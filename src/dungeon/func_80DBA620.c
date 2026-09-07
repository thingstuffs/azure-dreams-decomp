#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80171E20_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_80171E20_0;   /* arg0 in func_80171E20 */

typedef struct S_80171E20_1 {
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
} S_80171E20_1;   /* arg3 in func_80171E20 */

typedef struct S_80171E20_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80171E20_2;   /* arg2 in func_80171E20 */


typedef struct S_80171E20_4 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171E20_4;   /* actor in func_80171E20 */

typedef struct S_80171E20_5 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171E20_5;   /* origin in func_80171E20 */



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

extern void func_80172384(void);
extern void func_801725C8(void *, void *, void *, void *);
extern s32 func_80172D74(void *, void *, void *, void *);
extern void func_80172F38(void *, void *, void *, void *);
extern s32 func_80173050(void *, void *, void *, s32);
extern void func_80174890(void *, void *, void *, void *);
extern void func_80174A9C(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_801753BC[];
extern u8 D_801753C4[];
extern u8 D_801753F4[];
extern u8 D_801753FC[];
extern u8 D_80175404[];

void func_80171E20(void *arg0_, void *arg1_, void *arg2_, void *arg3_)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4, &&jt_c5, &&jt_c6,
        &&jt_c7, &&jt_c8, &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12
    };
    void *arg0 = arg0_;
    void *arg1 = arg1_;
    void *arg2 = arg2_;
    register void *arg3 ASM_REG("$18") = arg3_;   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u32 initial_flags = D_80083462;
    s16 sp18;
    s32 flags;
    s32 kind;
    s8 tile;
    s16 result;
    u16 field46;
    u8 *table;
    void *origin;
    void *actor;

    if (initial_flags & 0x1000) {
        ((S_80171E20_0 *)arg0)->unk_9A = 14;
        func_80172384();
        return;
    }

    ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(arg3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if (((S_80171E20_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80171E20_2 *)arg2)->unk_2C == D_80175404) {
            return;
        }
        {
            u8 *early_table = D_801753FC;
            (*(u8 * *)((u8 *)arg2 + 0x2C)) = early_table;
            func_80047784(
                arg2,
                early_table[((D_80083228 + ((S_80171E20_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
            return;
        }
    }

    if (((S_80171E20_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80171E20_2 *)arg2)->unk_2C == D_80175404) {
            ((S_80171E20_0 *)arg0)->unk_9A = 13;
            ((S_80171E20_0 *)arg0)->unk_9B = 1;
            ((S_80171E20_0 *)arg0)->unk_8C = 0;
            ((S_80171E20_1 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_801753FC) != 0) {
            return;
        }
    }

    if ((D_80083462 & 0x2000) == 0) {
        if (((S_80171E20_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        {
            u8 current_state = ((S_80171E20_0 *)arg0)->unk_9A;
            u32 actor_state = 14;

            if (current_state != actor_state) {
                table = D_801753BC;
                if (((S_80171E20_2 *)arg2)->unk_2C != table) {
                    (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
                    func_80047784(
                        arg2,
                        table[((D_80083228 + ((S_80171E20_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                        0);
                }
                ((S_80171E20_0 *)arg0)->unk_9A = actor_state;
            }
        }

        ((S_80171E20_0 *)arg0)->unk_98 &= 0xFFF3;

        if (((S_80171E20_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_801753C4) != 0) {
                return;
            }
        }

        if (((S_80171E20_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80174890(arg0, arg1, arg2, arg3);
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    tile = func_8009FB34(((S_80171E20_2 *)arg2)->unk_24.at00.v, ((S_80171E20_2 *)arg2)->unk_24.at01.v);
    ((S_80171E20_2 *)arg2)->unk_26 = tile;

    if (((S_80171E20_1 *)arg3)->unk_6D > 0) {
        if (((S_80171E20_1 *)arg3)->unk_1C & 0x20) {
            goto jt_c12;
        }
        if (((S_80171E20_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto jt_default;
        }
        field46 = ((S_80171E20_1 *)arg3)->unk_46;
        if ((field46 & 0x8000) == 0) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(
                        arg3, (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80173050(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            field46 = ((S_80171E20_1 *)arg3)->unk_46 | 0x4000;
            ((S_80171E20_1 *)arg3)->unk_46 = field46;
            if ((field46 & 0x8000) == 0) {
                goto jt_default;
            }
        }

        kind = (((S_80171E20_1 *)arg3)->unk_46 & 0x3FFF) - 1;
        if ((u32)kind >= 12U) {
            goto jt_default;
        }
        (void)jt_keep;
        goto *D_80170808[kind];

jt_c9:
        if ((s16)func_80172D74(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_80172F38(arg0, arg1, arg2, arg3);
        return;

jt_c8:
        func_80174A9C(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        result = func_800A0818(
            ((S_80171E20_2 *)arg2)->unk_24.at00.v, ((S_80171E20_2 *)arg2)->unk_24.at01.v,
            D_80082E80[0x24], D_80082E80[0x25], &sp18);
        actor = D_800814A8;
        ((S_80171E20_1 *)arg3)->unk_2A = result;
        if (((S_80171E20_4 *)actor)->unk_9A == 0x11) {
            goto jt_call;
        }

jt_c12:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
jt_call:
        func_800AAF00(arg0, arg1, arg2, D_801753F4, func_80171E20);
        return;

jt_c4:
jt_c10:
jt_c11:
jt_default:
        func_801725C8(arg0, arg1, arg2, arg3);
        return;
    }

    flags = ((S_80171E20_1 *)arg3)->unk_1C;
    if (!(flags & 0x2000)) {
        if ((tile < 0) ||
            !(((DungeonRecord *)D_800E2970)[tile].flags & 2)) {
            if (!(flags & 0x430)) {
                origin = D_80082E80;
                if ((s16)func_8009FD7C(
                        ((S_80171E20_2 *)arg2)->unk_24.at00.v, ((S_80171E20_2 *)arg2)->unk_24.at01.v,
                        ((S_80171E20_5 *)origin)->unk_24, ((S_80171E20_5 *)origin)->unk_25) != 0) {
                    ((S_80171E20_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_80171E20_2 *)arg2)->unk_24.at00.v, ((S_80171E20_2 *)arg2)->unk_24.at01.v,
                        ((S_80171E20_5 *)origin)->unk_24, ((S_80171E20_5 *)origin)->unk_25, &sp18);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80171E20_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    table = D_801753BC;
    if (((S_80171E20_2 *)arg2)->unk_2C == table) {
        return;
    }

assign_table:
    (*(u8 * *)((u8 *)arg2 + 0x2C)) = table;
    func_80047784(
        arg2,
        table[((D_80083228 + ((S_80171E20_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
        0);
}
