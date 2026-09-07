#include "common.h"


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
extern void func_80171554(void) __attribute__((noreturn));
extern void func_80171574(void);
extern void func_80171784(void *, void *, void *, void *);
extern s32 func_80171ECC(void *, void *, void *, void *);
extern void func_80172090(void *, void *, void *, void *);
extern s32 func_801721B4(void *, void *, void *, void *);
extern void func_80173468(void *, void *, void *, void *);
extern void func_80173AE8(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80171014[];
extern u8 D_8017420C[];
extern u8 D_8017421C[];
extern u8 D_8017424C[];
extern u8 D_80174254[];
extern u8 D_8017425C[];


typedef struct S_80171014_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x2];
    s16 unk_9E;
    u8 pad_A0[0x2];
    union { s16 s; u16 u; } unk_A2;   /* accessed as both */
} S_80171014_0;   /* arg0 in func_80171014 */

typedef struct S_80171014_1 {
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
} S_80171014_1;   /* arg3 in func_80171014 */

typedef struct S_80171014_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80171014_2;   /* arg2 in func_80171014 */

typedef struct S_80171014_3 {
    u8 pad_00[0x58];
    void * unk_58;
} S_80171014_3;   /* D_800814A8 in func_80171014 */

typedef struct S_80171014_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80171014_4;   /* origin in func_80171014 */

typedef struct S_80171014_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80171014_5;   /* player in func_80171014 */

void func_80171014(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    s32 scratch;
    s8 result;
    u16 state;

    if (D_80083462 & 0x1000) {
        ((S_80171014_0 *)arg0)->unk_9A = 0xE;
        func_80171574();
        func_80171554();
        return;
    }
    if (((S_80171014_1 *)arg3)->unk_25 == 0) {
        void *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80171014_2 *)arg2)->unk_2C == D_8017425C) {
            return;
        }
        table = D_80174254;
        (*(void * *)((u8 *)arg2 + (0x2C))) = table;
        func_80047784(arg2,
            ((u8 *)table)[((D_80083228 + ((S_80171014_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        func_80171554();
        return;
    }

    if (((S_80171014_1 *)arg3)->unk_1C & 0x200) {
        if (((S_80171014_2 *)arg2)->unk_2C == D_8017425C) {
            ((S_80171014_0 *)arg0)->unk_9A = 0xD;
            ((S_80171014_0 *)arg0)->unk_9B = 1;
            ((S_80171014_0 *)arg0)->unk_8C = 0;
            ((S_80171014_1 *)arg3)->unk_1C &= 0xFFFBFFFF;
            func_80171554();
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80174254) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_80171014_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            func_80171554();
            return;
        }

        ASM_KEEP(arg0);   /* MATCH pin: retail delay-slot fill depends on it */
        {
            u8 current_state = ((S_80171014_0 *)arg0)->unk_9A;
            u32 actor_state = 0xE;
            void *current;
            void *table;

#ifndef __mips__
#endif
            if (current_state != actor_state) {
                ((S_80171014_0 *)arg0)->unk_9A = actor_state;
            }
            current = ((S_80171014_2 *)arg2)->unk_2C;
            table = D_8017420C;
            if (current != table) {
                (*(void * *)((u8 *)arg2 + (0x2C))) = table;
                func_80047784(arg2,
                    ((u8 *)table)[((D_80083228 + ((S_80171014_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                    0);
                ((S_80171014_2 *)arg2)->unk_05 = 1;
                ((S_80171014_0 *)arg0)->unk_A2.s = 0;
                ((S_80171014_0 *)arg0)->unk_9E = 0;
            }
        }

        ((S_80171014_1 *)arg3)->unk_1C |= 0x40000;
        ((S_80171014_0 *)arg0)->unk_98 &= 0xFFF7;

        if (((S_80171014_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_8017421C) != 0) {
                return;
            }
        }

        if (((S_80171014_1 *)arg3)->unk_1C & 0x80000) {
            s16 delta;

            func_800AA888(arg0, arg1, arg2, arg3);
            delta = ((S_80171014_0 *)arg0)->unk_92.u - ((S_80171014_0 *)arg0)->unk_A2.u;
            ((S_80171014_0 *)arg0)->unk_A2.s = 0;
            ((S_80171014_0 *)arg0)->unk_9E = 0;
            ((S_80171014_0 *)arg0)->unk_92.s = delta;
            func_80173468(arg0, arg1, arg2, arg3);
            func_80171554();
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            if ((func_800AAB10(arg0, arg1, arg2, arg3) << 16) != 0) {
                func_80173AE8(arg0, arg1, arg2, arg3);
                func_80171554();
                return;
            }
        }
    }

    result = func_8009FB34(((S_80171014_2 *)arg2)->unk_24.at00.v, ((S_80171014_2 *)arg2)->unk_24.at01.v);
    ((S_80171014_2 *)arg2)->unk_26 = result;

    if (((S_80171014_1 *)arg3)->unk_6D > 0) {
        if (((S_80171014_1 *)arg3)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_80171014_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((S_80171014_1 *)arg3)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((S_80171014_3 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801721B4(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((S_80171014_1 *)arg3)->unk_46 | 0x4000;
            ((S_80171014_1 *)arg3)->unk_46 = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        state = ((S_80171014_1 *)arg3)->unk_46 & 0x3FFF;
        if ((u32)(state - 1) >= 12) {
            goto generic;
        }
        (void)jt_keep;
        goto *D_80170808[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80171ECC(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172090(arg0, arg1, arg2, arg3);
        func_80171554();
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

        coordinate = func_800A0818(
            ((S_80171014_2 *)arg2)->unk_24.at00.v, ((S_80171014_2 *)arg2)->unk_24.at01.v,
            ((S_80171014_4 *)origin)->unk_24, ((S_80171014_4 *)origin)->unk_25,
            &scratch);
        player = D_800814A8;
#ifndef __mips__
#endif
        ((S_80171014_1 *)arg3)->unk_2A = coordinate;
        if (((S_80171014_5 *)player)->unk_9A == 0x11) {
            goto case_123;
        }
        }

jt_c12:
case_12:
        func_800A9A0C(arg3);
        func_80171554();
        return;

jt_c1:
jt_c2:
jt_c3:
case_123:
        func_800AAF00(arg0, arg1, arg2, D_8017424C, D_80171014);
        func_80171554();
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_80171784(arg0, arg1, arg2, arg3);
        func_80171554();
        return;
    }

    if (!(((S_80171014_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((S_80171014_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80171014_2 *)arg2)->unk_24.at00.v, ((S_80171014_2 *)arg2)->unk_24.at01.v,
                        ((S_80171014_4 *)origin)->unk_24, ((S_80171014_4 *)origin)->unk_25) << 16) != 0) {
                    ((S_80171014_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_80171014_2 *)arg2)->unk_24.at00.v, ((S_80171014_2 *)arg2)->unk_24.at01.v,
                        ((S_80171014_4 *)origin)->unk_24, ((S_80171014_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }
}
