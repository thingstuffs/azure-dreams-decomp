#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"



typedef struct S_80170E54_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    union { void * p; u8 * p2; } unk_2C;   /* accessed as both */
    u8 pad_30[0x8B];
    u8 unk_BB;
} S_80170E54_2;   /* arg2 in func_80170E54 */


typedef struct S_80170E54_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80170E54_4;   /* origin in func_80170E54 */

typedef struct S_80170E54_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170E54_5;   /* player in func_80170E54 */


typedef struct S_80170E54_7 {
    void * unk_00;
    volatile u8 unk_04;
    volatile u8 unk_05;
    u8 pad_06[0x2];
    volatile s32 unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    volatile u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80170E54_7;   /* sub in func_80170E54 */

typedef struct S_80170E54_8 {
    u8 pad_00[0x4];
    volatile s32 unk_04;
} S_80170E54_8;   /* base in func_80170E54 */

typedef struct S_80170E54_9 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80170E54_9;   /* ((S_80170E54_2 *)arg2)->unk_08 in func_80170E54 */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_8003DE58(void *, void *, void *, s32);
extern void *func_8003FD64(s32, void *);
extern void func_8004491C(void *, void *);
extern void func_80047784(void *, s32, s32);
extern s32 func_80069EF8(void);
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
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171060(void) __attribute__((noreturn));
extern void func_80171430(void);
extern void func_80171468(void) __attribute__((noreturn));
extern void func_8017154C(void) __attribute__((noreturn));
extern void func_80171570(void);
extern void func_801717B4(void *, void *, void *, void *);
extern s32 func_80171FC0(void *, void *, void *, void *);
extern void func_80172184(void *, void *, void *, void *);
extern s32 func_8017229C(void *, void *, void *, s32);
extern void func_80173EF4(void *, void *, void *, void *);

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
extern u8 D_80170E54;
extern u8 D_80174140[];
extern u8 D_80174148[];
extern u8 D_80174150[];
extern u8 D_80174188[];
extern u8 D_80174190[];

void func_80170E54(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
        &&normal_state, &&timer_table_reload,
    };
    s32 scratch;
    s16 offset[3];
    s8 result;
    u16 state;
    u8 *table;

    if (D_80083462 & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xE;
        func_80171570();
        func_8017154C();
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80170E54_2 *)arg2)->unk_2C.p == D_80174190) {
            return;
        }
        {
            register void *next_state ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

            next_state = D_80174188;
            ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        }
        func_80171060();
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((S_80170E54_2 *)arg2)->unk_2C.p == D_80174190) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xFFFBFFFF;
            func_8017154C();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174188) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_8017154C();
            return;
        }

normal_state:
        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 != 0xE) {
            table = D_80174148;
            if (((S_80170E54_2 *)arg2)->unk_2C.p != table) {
                (*(void * *)((u8 *)arg2 + 0x2C)) = table;
                func_80047784(arg2,
                    table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                    0);
            }
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xE;
        }

        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFF3;
        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174150) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            u8 *high_table;

            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173EF4(arg0, arg1, arg2, arg3);
            high_table = D_80174140;
            (*(void * *)((u8 *)arg2 + 0x2C)) = high_table;
            func_80047784(arg2,
                high_table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            func_8017154C();
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_80170E54_2 *)arg2)->unk_24.at00.v, ((S_80170E54_2 *)arg2)->unk_24.at01.v);
    ((S_80170E54_2 *)arg2)->unk_26 = result;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_80170E54_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8017229C(arg0, arg1, arg2, 0) << 16) == 0) {
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
        if ((func_80171FC0(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172184(arg0, arg1, arg2, arg3);
        func_8017154C();
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_80170E54_2 *)arg2)->unk_24.at00.v, ((S_80170E54_2 *)arg2)->unk_24.at01.v,
                ((S_80170E54_4 *)origin)->unk_24, ((S_80170E54_4 *)origin)->unk_25,
                &scratch);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = coordinate;
            if (((S_80170E54_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

jt_c12:
case_12:
        func_800A9A0C(arg3);
        func_8017154C();
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(arg0, arg1, arg2, D_80174140, &D_80170E54);
        func_8017154C();
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801717B4(arg0, arg1, arg2, arg3);
        func_8017154C();
        return;
    }

    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x2000)) {
        s32 index = result;

        if ((index < 0) || !(D_800E2970[index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80170E54_2 *)arg2)->unk_24.at00.v, ((S_80170E54_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E54_4 *)origin)->unk_24, ((S_80170E54_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
                        ((S_80170E54_2 *)arg2)->unk_24.at00.v, ((S_80170E54_2 *)arg2)->unk_24.at01.v,
                        ((S_80170E54_4 *)origin)->unk_24, ((S_80170E54_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_80170E54_2 *)arg2)->unk_14 & 0x40) {
        return;
    }

    table = D_80174148;
    if ((((S_80170E54_2 *)arg2)->unk_2C.p != table) &&
        (((S_80170E54_2 *)arg2)->unk_2C.p != D_80174140)) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA = 1;
        func_80171468();
        return;
    }

    if (((S_80170E54_2 *)arg2)->unk_14 & 0x6000) {
        s16 timer = ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA - 1;

        ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA = timer;
        if (timer < 0) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_AA = (func_80069EF8() & 0x1F) + 0x20;
        }
        if (((Rec_func_800A9E70_arg0 *)arg0)->unk_AA < 2) {
            {
                void *next_state;

                next_state = D_80174148;
                ASM_TAILSLOT_PIN(next_state);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
            }
            func_80171430();
        }
        ((S_80170E54_2 *)arg2)->unk_2C.p = D_80174140;
timer_table_reload:
        func_80047784(arg2,
            ((S_80170E54_2 *)arg2)->unk_2C.p2[
                ((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
    }

    if (!func_8003DE58(((S_80170E54_2 *)arg2)->unk_08, arg2, offset, 1)) {
        return;
    }
    if (((S_80170E54_2 *)arg2)->unk_2C.p != D_80174148) {
        return;
    }

    {
        void *created;
        void *sub;
        void *color;
        u8 *base;
        s32 base_word;

        created = func_8003FD64(0x112, D_80083498);
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_A0.at00_pv.v = created;
        arg2 = created;
        if (arg2 == 0) {
            return;
        }
        func_8004491C(arg2, &D_80045340);
        color = (void *)0x00808080;
        ((S_80170E54_2 *)arg2)->unk_10 = D_800D79B0;
        ((S_80170E54_9 *)(((S_80170E54_2 *)arg2)->unk_08))->unk_02 =
            ((Rec_D_800E3D7C *)arg1)->unk_00.at02_u16.v + offset[0];
        ((S_80170E54_9 *)(((S_80170E54_2 *)arg2)->unk_08))->unk_06 =
            ((Rec_D_800E3D7C *)arg1)->unk_04.at02_u16.v + offset[1];
        ((S_80170E54_9 *)(((S_80170E54_2 *)arg2)->unk_08))->unk_0A =
            ((Rec_D_800E3D7C *)arg1)->unk_08.at02_u16.v + offset[2];
        sub = ((S_80170E54_2 *)arg2)->unk_0C;
        base = D_800DEA68;
        ((S_80170E54_2 *)arg2)->unk_BB = 0;
        ((S_80170E54_7 *)sub)->unk_1E = 0xC00;
        ((S_80170E54_7 *)sub)->unk_1C = 0xC00;
        ((S_80170E54_7 *)sub)->unk_0C = color;
        ((S_80170E54_7 *)sub)->unk_00 = base;
        ((S_80170E54_7 *)sub)->unk_14 |= 0xC;
        base_word = ((S_80170E54_8 *)base)->unk_04;
        ((S_80170E54_7 *)sub)->unk_04 = 0;
        ((S_80170E54_7 *)sub)->unk_05 = 0;
        ((S_80170E54_7 *)sub)->unk_08 = base_word;
    }
}

extern void func_80171430(void) __attribute__((noreturn));
