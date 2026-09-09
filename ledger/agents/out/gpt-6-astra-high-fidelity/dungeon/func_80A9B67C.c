#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 rand(void);
extern s32 func_8009A180(void *, void *);
extern s8 func_8009FB34(s32, s32);
extern s32 func_8009FD7C(s32, s32, s32, s32);
extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern s32 func_800A1C58(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern s32 func_800AA924(void *, void *, void *, void *);
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_801715B4(void);
extern void func_801717F8(void *, void *, void *, void *);
extern s32 func_80171FA4(void *, void *, void *, void *);
extern void func_80172168(void *, void *, void *, void *);
extern s32 func_80172280(void *, void *, void *, s32);
extern void func_80173F20(void *, void *, void *, void *);
extern void func_80174470(void *, void *, void *, void *);

extern s32 D_80045340;
extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80083498[];
extern u8 D_800D79B0[];
extern u8 D_800DEA68[];
extern DungeonRecord D_800E2970[];
extern void *D_80170808[];
extern u8 D_80170E7C;
extern u8 D_80174C34[];
extern u8 D_80174C3C[];
extern u8 D_80174C44[];
extern u8 D_80174C84[];
extern u8 D_80174C8C[];




typedef struct S_80170E7C_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
    u8 pad_30[0x8B];
    u8 unk_BB;
} S_80170E7C_2;   /* arg2 in func_80170E7C */


typedef struct S_80170E7C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170E7C_4;   /* origin in func_80170E7C */

typedef struct S_80170E7C_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E7C_5;   /* player in func_80170E7C */


typedef struct S_80170E7C_7 {
    void * unk_00;
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[0x2];
    s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80170E7C_7;   /* sub in func_80170E7C */

typedef struct S_80170E7C_8 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80170E7C_8;   /* base in func_80170E7C */

typedef struct S_80170E7C_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170E7C_9;   /* ((S_80170E7C_2 *)arg2)->unk_08 in func_80170E7C */

void func_80170E7C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 scratch;
    s16 offset[3];
    s8 result;
    u16 state;
    u8 *table;
    register u8 *next_state ASM_REG("$5"); /* MATCH: both paths merge the table address in a1. */

    if (D_80083462 & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xE;
        func_801715B4();
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80170E7C_2 *)arg2)->unk_2C == D_80174C8C) {
            return;
        }
        next_state = D_80174C84;
        goto set_high_table;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((S_80170E7C_2 *)arg2)->unk_2C == D_80174C8C) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174C84) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        {
            u32 current_state = ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8;
            u32 actor_state;

               /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            actor_state = 0xE;
#ifndef __mips__
#endif
            if (current_state != actor_state) {
                table = D_80174C3C;
                if (((S_80170E7C_2 *)arg2)->unk_2C != table) {
                    (*(void * *)((u8 *)arg2 + (0x2C))) = table;
                    func_80047784(arg2,
                        table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = actor_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFF3;
        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174C44) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            u8 *high_table;

            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173F20(arg0, arg1, arg2, arg3);
            next_state = D_80174C34;
#ifndef __mips__
#endif
set_high_table:
            high_table = next_state;
            (*(void * *)((u8 *)arg2 + (0x2C))) = high_table;
            func_80047784(arg2,
                *(u8 *)((((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7) + (u32)high_table),
                0);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            if ((func_800AAB10(arg0, arg1, arg2, arg3) << 16) != 0) {
                func_80174470(arg0, arg1, arg2, arg3);
            }
        }
    }

    result = func_8009FB34(((S_80170E7C_2 *)arg2)->unk_24.at00.v, ((S_80170E7C_2 *)arg2)->unk_24.at01.v);
    ((S_80170E7C_2 *)arg2)->unk_26 = result;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_80170E7C_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172280(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        state = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(state - 1) >= 12) {
            goto generic;
        }
        (void)jt_keep;
        goto *D_80170808[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80171FA4(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172168(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_80170E7C_2 *)arg2)->unk_24.at00.v, ((S_80170E7C_2 *)arg2)->unk_24.at01.v,
                ((S_80170E7C_4 *)origin)->unk_24, ((S_80170E7C_4 *)origin)->unk_25,
                &scratch);
            player = D_800814A8;
#ifndef __mips__
#endif
            ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = coordinate;
            if (((S_80170E7C_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(arg0, arg1, arg2, D_80174C34, &D_80170E7C);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801717F8(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x2000)) {
        s32 index = result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80170E7C_2 *)arg2)->unk_24.at00.v, ((S_80170E7C_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E7C_4 *)origin)->unk_24, ((S_80170E7C_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
                        ((S_80170E7C_2 *)arg2)->unk_24.at00.v, ((S_80170E7C_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E7C_4 *)origin)->unk_24, ((S_80170E7C_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170E7C_2 *)arg2)->unk_14 & 0x40) {
        return;
    }

    table = D_80174C3C;
    if ((((S_80170E7C_2 *)arg2)->unk_2C != table) &&
        (((S_80170E7C_2 *)arg2)->unk_2C != D_80174C34)) {
        (*(void * *)((u8 *)arg2 + (0x2C))) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA = 1;
    } else if (((S_80170E7C_2 *)arg2)->unk_14 & 0x6000) {
        void *next_state;
        s16 timer = ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA - 1;

        ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA = timer;
        if (timer < 0) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA = (rand() & 0x1F) + 0x20;
        }
        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_AA < 2) {
            next_state = D_80174C3C;
        } else {
            next_state = D_80174C34;
        }
        ((S_80170E7C_2 *)arg2)->unk_2C = next_state;
        func_80047784(arg2,
            ((u8 *)*(u8 * volatile *)((u8 *)arg2 + 0x2C))[
                ((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
    }

    if (!func_8003DE58(((S_80170E7C_2 *)arg2)->unk_08, arg2, offset, 1)) {
        return;
    }
    if (((S_80170E7C_2 *)arg2)->unk_2C != D_80174C3C) {
        return;
    }

    {
        void *created;
        void *sub;
        void *color;
        u8 *base;

        created = func_8003FD64(0x112, D_80083498);
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_A0.at00_pv.v = created;
        arg2 = created;
        if (arg2 == 0) {
            return;
        }
        func_8004491C(arg2, &D_80045340);
        color = (void *)0x00808080;
        ((S_80170E7C_2 *)arg2)->unk_10 = D_800D79B0;
        ((S_80170E7C_9 *)(((S_80170E7C_2 *)arg2)->unk_08))->unk_02 =
            ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v + offset[0];
        ((S_80170E7C_9 *)(((S_80170E7C_2 *)arg2)->unk_08))->unk_06 =
            ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v + offset[1];
        ((S_80170E7C_9 *)(((S_80170E7C_2 *)arg2)->unk_08))->unk_0A =
            ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v + offset[2];
        sub = ((S_80170E7C_2 *)arg2)->unk_0C;
        base = D_800DEA68;
        ((S_80170E7C_2 *)arg2)->unk_BB = 0;
        ((S_80170E7C_7 *)sub)->unk_1E = 0xC00;
        ((S_80170E7C_7 *)sub)->unk_1C = 0xC00;
        ((S_80170E7C_7 *)sub)->unk_0C = color;
        ((S_80170E7C_7 *)sub)->unk_00 = base;
        ((S_80170E7C_7 *)sub)->unk_14 |= 0xC;
        {
            /* one-read temp BEFORE the byte clears: source order = retail
               emission order (ori,sh,lw,sb,sb,sw) and the two sb sit in the
               lw load-delay shadow with no scheduler motion needed */
            s32 anim = ((S_80170E7C_8 *)base)->unk_04;
            ((S_80170E7C_7 *)sub)->unk_04 = 0;
            ((S_80170E7C_7 *)sub)->unk_05 = 0;
            ((S_80170E7C_7 *)sub)->unk_08 = anim;
        }
    }
}

