#include "common.h"
#include "records/Rec_D_800814A8.h"


typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern void func_80047784(void *, s32, s32);
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
extern void func_80171FC8(void);
extern void func_801721D8(void *, void *, void *, void *);
extern s32 func_80172920(void *, void *, void *, void *);
extern void func_80172AAC(void *, void *, void *, void *);
extern s32 func_80172B8C(void *, void *, void *, void *);
extern void func_801743F0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern s32 D_801719DC;
extern u8 D_80174634[];
extern u8 D_80174644[];
extern u8 D_80174674[];
extern u8 D_8017467C[];
extern u8 D_80174684[];


typedef struct S_801719DC_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; struct { u8 pad[0x2]; u16 v; } at02u; } unk_A4;   /* overlapping accesses */
    s32 unk_A8;
    s32 unk_AC;
    s32 unk_B0;
    u8 pad_B4[0x4];
    s16 unk_B8;
} S_801719DC_0;   /* arg0 in func_801719DC */

typedef struct S_801719DC_1 {
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
} S_801719DC_1;   /* arg3 in func_801719DC */

typedef struct S_801719DC_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801719DC_2;   /* arg2 in func_801719DC */


typedef struct S_801719DC_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801719DC_4;   /* origin in func_801719DC */

typedef struct S_801719DC_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801719DC_5;   /* player in func_801719DC */

void func_801719DC(void *in0, void *in1, void *in2, void *in3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 scratch;
    s8 result;
    u16 state;
    void *arg0 = in0;
    register void *arg1 ASM_REG("$16") = in1;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *arg2 = in2;
    void *arg3 = in3;

    if (D_80083462 & 0x1000) {
        ((S_801719DC_0 *)arg0)->unk_9A = 0xE;
        func_80171FC8();
        return;
    }
    ASM_KEEP(arg0);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg1);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    ASM_KEEP(arg2);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    if (((S_801719DC_1 *)arg3)->unk_25 == 0) {
        void *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_801719DC_2 *)arg2)->unk_2C == D_80174684) {
            return;
        }
        table = D_8017467C;
        (*(void * *)((u8 *)arg2 + (0x2C))) = table;
        func_80047784(arg2,
            ((u8 *)table)[((D_80083228 + ((S_801719DC_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_801719DC_1 *)arg3)->unk_1C & 0x200) {
        if (((S_801719DC_2 *)arg2)->unk_2C == D_80174684) {
            ((S_801719DC_0 *)arg0)->unk_9A = 0xD;
            ((S_801719DC_0 *)arg0)->unk_9B = 1;
            ((S_801719DC_0 *)arg0)->unk_8C = 0;
            ((S_801719DC_1 *)arg3)->unk_1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_8017467C) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_801719DC_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        {
            s32 current_state;
            u32 actor_state;
            void *current;
            void *table;
            s32 reset_value;

            current_state = ((S_801719DC_0 *)arg0)->unk_9A;
               /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
            actor_state = 0xE;
            if (current_state != actor_state) {
                current = ((S_801719DC_2 *)arg2)->unk_2C;
                table = D_80174634;
                if (current != table) {
                    (*(void * *)((u8 *)arg2 + (0x2C))) = table;
                    func_80047784(arg2,
                        ((u8 *)table)[((D_80083228 + ((S_801719DC_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                        1);
                    ((S_801719DC_2 *)arg2)->unk_05 = 1;
                    reset_value = ((S_801719DC_0 *)arg0)->unk_A4.at00.v;
                    ((S_801719DC_0 *)arg0)->unk_A4.at02.v = 0;
                    ((S_801719DC_0 *)arg0)->unk_B8 = 0;
                    ((S_801719DC_0 *)arg0)->unk_AC = 0;
                    ((S_801719DC_0 *)arg0)->unk_B0 = 0;
                    ((S_801719DC_0 *)arg0)->unk_A8 = reset_value;
                }
                ((S_801719DC_0 *)arg0)->unk_9A = actor_state;
            }
        }

        ((S_801719DC_0 *)arg0)->unk_98 &= 0xFFF3;
        ((S_801719DC_1 *)arg3)->unk_1C |= 0x40000;

        if (((S_801719DC_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174644) != 0) {
                return;
            }
        }

        if (((S_801719DC_1 *)arg3)->unk_1C & 0x80000) {
            u16 old_value;
            u16 delta;
            s32 value;

            func_800AA888(arg0, arg1, arg2, arg3);
            old_value = ((S_801719DC_0 *)arg0)->unk_92;
            delta = ((S_801719DC_0 *)arg0)->unk_A4.at02u.v;
            value = ((S_801719DC_0 *)arg0)->unk_A4.at00.v;
            ((S_801719DC_0 *)arg0)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)arg0)->unk_B8 = 0;
            ((S_801719DC_0 *)arg0)->unk_AC = 0;
            ((S_801719DC_0 *)arg0)->unk_B0 = 0;
            ((S_801719DC_0 *)arg0)->unk_92 = old_value - delta;
            ((S_801719DC_0 *)arg0)->unk_A8 = value;
            func_801743F0(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_801719DC_2 *)arg2)->unk_24.at00.v, ((S_801719DC_2 *)arg2)->unk_24.at01.v);
    ((S_801719DC_2 *)arg2)->unk_26 = result;

    if (((S_801719DC_1 *)arg3)->unk_6D > 0) {
        if (((S_801719DC_1 *)arg3)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_801719DC_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((S_801719DC_1 *)arg3)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172B8C(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((S_801719DC_1 *)arg3)->unk_46 | 0x4000;
            ((S_801719DC_1 *)arg3)->unk_46 = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        state = ((S_801719DC_1 *)arg3)->unk_46 & 0x3FFF;
        if ((u32)(state - 1) >= 12) {
            goto generic;
        }
        (void)jt_keep;
        goto *D_80170808[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80172920(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172AAC(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_801719DC_2 *)arg2)->unk_24.at00.v, ((S_801719DC_2 *)arg2)->unk_24.at01.v,
                ((S_801719DC_4 *)origin)->unk_24, ((S_801719DC_4 *)origin)->unk_25,
                &scratch);
            player = D_800814A8;
            ((S_801719DC_1 *)arg3)->unk_2A = coordinate;
            if (((S_801719DC_5 *)player)->unk_9A == 0x11) {
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
        func_800AAF00(arg0, arg1, arg2, D_80174674, &D_801719DC);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801721D8(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((S_801719DC_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((S_801719DC_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_801719DC_2 *)arg2)->unk_24.at00.v, ((S_801719DC_2 *)arg2)->unk_24.at01.v,
                        ((S_801719DC_4 *)origin)->unk_24, ((S_801719DC_4 *)origin)->unk_25) << 16) != 0) {
                    ((S_801719DC_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_801719DC_2 *)arg2)->unk_24.at00.v, ((S_801719DC_2 *)arg2)->unk_24.at01.v,
                        ((S_801719DC_4 *)origin)->unk_24, ((S_801719DC_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_801719DC_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    {
        void *table = D_80174634;
        s32 reset_value;

        if (((S_801719DC_2 *)arg2)->unk_2C != table) {
            (*(void * *)((u8 *)arg2 + (0x2C))) = table;
            func_80047784(arg2,
                ((u8 *)table)[((D_80083228 + ((S_801719DC_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                1);
            ((S_801719DC_2 *)arg2)->unk_05 = 1;
            reset_value = ((S_801719DC_0 *)arg0)->unk_A4.at00.v;
            ((S_801719DC_0 *)arg0)->unk_A4.at02.v = 0;
            ((S_801719DC_0 *)arg0)->unk_B8 = 0;
            ((S_801719DC_0 *)arg0)->unk_AC = 0;
            ((S_801719DC_0 *)arg0)->unk_B0 = 0;
            ((S_801719DC_0 *)arg0)->unk_A8 = reset_value;
        }
    }
}
