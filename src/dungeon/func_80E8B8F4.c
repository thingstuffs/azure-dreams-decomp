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
extern void func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171684(void);
extern void func_801718DC(void *, void *, void *, void *);
extern s32 func_80172088(void *, void *, void *, void *);
extern void func_8017224C(void *, void *, void *, void *);
extern s32 func_80172364(void *, void *, void *, s32);
extern void func_80174060(void *, void *, void *, void *);
extern void func_80174234(void *, void *, void *, void *);
extern void func_80174B14(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_800DCF5B;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_80174F00[];
extern u8 D_80174F08[];
extern u8 D_80174F38;
extern u8 D_80174F40;
extern u8 D_80174F48;


typedef struct S_801710F4_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x8];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
} S_801710F4_0;   /* arg0 in func_801710F4 */

typedef struct S_801710F4_1 {
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
} S_801710F4_1;   /* arg3 in func_801710F4 */

typedef struct S_801710F4_2 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801710F4_2;   /* arg2 in func_801710F4 */

typedef struct S_801710F4_3 {
    u8 pad_00[0x58];
    void * unk_58;
} S_801710F4_3;   /* D_800814A8 in func_801710F4 */

typedef struct S_801710F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801710F4_4;   /* origin in func_801710F4 */

typedef struct S_801710F4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801710F4_5;   /* player in func_801710F4 */

void func_801710F4(void *arg0, void *arg1, void *arg2, void *arg3)
{
    static void *const jt_keep[] = {
        &&jt_c1, &&jt_c2, &&jt_c3, &&jt_c4,
        &&jt_c5, &&jt_c6, &&jt_c7, &&jt_c8,
        &&jt_c9, &&jt_c10, &&jt_c11, &&jt_c12,
    };
    void *p0;
    void *p1;
    void *p2;
    register void *p3 ASM_REG("$18");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    u8 *table;
    s32 scratch;
    s8 result;
    u16 state;
    u16 initial_flags = D_80083462;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (initial_flags & 0x1000) {
        ((S_801710F4_0 *)arg0)->unk_9A = 0xE;
        func_80171684();
        return;
    }

    ASM_KEEP(p1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(p2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(p3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if (((S_801710F4_1 *)arg3)->unk_25 == 0) {
        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_801710F4_2 *)arg2)->unk_2C != &D_80174F48) {
            u8 *new_table = &D_80174F40;

            (*(void * *)((u8 *)arg2 + 0x2C)) = new_table;
            func_80047784(arg2,
                *(u8 *)((u32)(((D_80083228 + ((S_801710F4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) +
                    (u32)new_table),
                0);
        }
        return;
    }

    if (((S_801710F4_1 *)arg3)->unk_1C & 0x200) {
        if (((S_801710F4_2 *)arg2)->unk_2C == &D_80174F48) {
            ((S_801710F4_0 *)arg0)->unk_9A = 0xD;
            ((S_801710F4_0 *)arg0)->unk_9B = 1;
            ((S_801710F4_0 *)arg0)->unk_8C = 0;
            ((S_801710F4_1 *)arg3)->unk_1C &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, &D_80174F40) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((S_801710F4_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        ASM_KEEP(arg0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        if (((S_801710F4_0 *)arg0)->unk_9A != 0xE) {
            u8 actor_state = 0xE;

            table = D_80174F00;
            if (((S_801710F4_2 *)arg2)->unk_2C != table) {
                (*(void * *)((u8 *)arg2 + 0x2C)) = table;
                func_80047784(arg2,
                    table[((D_80083228 + ((S_801710F4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                    0);
            }
            ((S_801710F4_0 *)arg0)->unk_9A = actor_state;
        }

        ((S_801710F4_0 *)arg0)->unk_98 &= 0xFFF3;
        if (((S_801710F4_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80174F08) != 0) {
                return;
            }
        }

        if (((S_801710F4_1 *)arg3)->unk_1C & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80174060(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_801710F4_2 *)arg2)->unk_24.at00.v, ((S_801710F4_2 *)arg2)->unk_24.at01.v);
    ((S_801710F4_2 *)arg2)->unk_26 = result;

    if (((S_801710F4_1 *)arg3)->unk_6D > 0) {
        if (((S_801710F4_1 *)arg3)->unk_1C & 0x20) {
            goto special_cleanup;
        }
        if (((S_801710F4_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((S_801710F4_1 *)arg3)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((S_801710F4_3 *)D_800814A8)->unk_58 + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172364(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((S_801710F4_1 *)arg3)->unk_46 | 0x4000;
            ((S_801710F4_1 *)arg3)->unk_46 = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        state = ((S_801710F4_1 *)arg3)->unk_46 & 0x3FFF;
        if ((u32)(state - 1) >= 12) {
            goto generic;
        }
        (void)jt_keep;
        goto *D_80170808[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80172088(arg0, arg1, arg2, arg3) << 16) == 0) {
            func_8017224C(arg0, arg1, arg2, arg3);
        }
        return;

jt_c4:
        func_80174B14(arg0, arg1, arg2, arg3);
        return;

jt_c10:
jt_c11:
        if (D_800DCF5B != 0) {
            goto generic;
        }
        func_80174234(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_801710F4_2 *)arg2)->unk_24.at00.v, ((S_801710F4_2 *)arg2)->unk_24.at01.v,
                ((S_801710F4_4 *)origin)->unk_24, ((S_801710F4_4 *)origin)->unk_25,
                &scratch);
            player = D_800814A8;
#ifndef __mips__
#endif
            ((S_801710F4_1 *)arg3)->unk_2A = coordinate;
            if (((S_801710F4_5 *)player)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
        }

jt_c12:
special_cleanup:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, &D_80174F38, func_801710F4);
        return;

generic:
        func_801718DC(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((S_801710F4_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((S_801710F4_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_801710F4_2 *)arg2)->unk_24.at00.v, ((S_801710F4_2 *)arg2)->unk_24.at01.v,
                        ((S_801710F4_4 *)origin)->unk_24, ((S_801710F4_4 *)origin)->unk_25) << 16) != 0) {
                    ((S_801710F4_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_801710F4_2 *)arg2)->unk_24.at00.v, ((S_801710F4_2 *)arg2)->unk_24.at01.v,
                        ((S_801710F4_4 *)origin)->unk_24, ((S_801710F4_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }

    if (D_80083462 & 0x2000) {
        return;
    }
    if (((S_801710F4_2 *)arg2)->unk_14 & 0x40) {
        return;
    }
    table = D_80174F00;
    if (((S_801710F4_2 *)arg2)->unk_2C == table) {
        return;
    }

    (*(void * *)((u8 *)arg2 + 0x2C)) = table;
    func_80047784(arg2,
        *(u8 *)((u32)(((D_80083228 + ((S_801710F4_1 *)arg3)->unk_2A + 0x100) >> 9) & 7) +
            (u32)table),
        0);
}
