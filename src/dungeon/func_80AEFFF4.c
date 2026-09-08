#include "common.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


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
extern s32 func_800AAB10(void *, void *, void *, void *);
extern void func_800AAF00(void *, void *, void *, void *, void *);
extern void func_80171D7C(void);
extern void func_80171FE8(void *, void *, void *, void *);
extern s32 func_801727B8(void *, void *, void *, void *);
extern void func_8017297C(void *, void *, void *, void *);
extern s32 func_80172A94(void *, void *, void *, s32);
extern void func_80174258(void *, void *, void *, void *);
extern void func_80174798(void *, void *, void *, void *);
extern void func_801751C0(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80170808[];
extern u8 D_801717F4;
extern u8 D_80175988[];
extern u8 D_80175998[];
extern u8 D_801759D0[];
extern u8 D_801759E0[];
extern u8 D_801759E8[];




typedef struct S_801717F4_2 {
    u8 pad_00[0x24];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801717F4_2;   /* arg2 in func_801717F4 */


typedef struct S_801717F4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801717F4_4;   /* origin in func_801717F4 */

typedef struct S_801717F4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801717F4_5;   /* player in func_801717F4 */

void func_801717F4(void *arg0, void *arg1, void *arg2, void *arg3)
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
    s32 scratch;
    s32 result;
    u16 state;
    u32 initial_flags = D_80083462;

    p0 = arg0;
    p1 = arg1;
    p2 = arg2;
    p3 = arg3;
#define arg0 p0
#define arg1 p1
#define arg2 p2
#define arg3 p3

    if (initial_flags & 0x1000) {
        ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xE;
        func_80171D7C();
        return;
    }

    ASM_KEEP(p1);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(p2);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(p3);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */

    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        u8 *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_801717F4_2 *)arg2)->unk_2C == D_801759E8) {
            return;
        }
        table = D_801759E0;
        (*(void * *)((u8 *)arg2 + (0x2C))) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((S_801717F4_2 *)arg2)->unk_2C == D_801759E8) {
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = 0xD;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_9B.as_u8 = 1;
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_801759E0) != 0) {
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

            ASM_KEEP(current_state);   /* MATCH pin: retail delay-slot fill depends on it */
            actor_state = 0xE;
            if (current_state != actor_state) {
                u8 *table = D_80175988;

                if (((S_801717F4_2 *)arg2)->unk_2C != table) {
                    (*(void * *)((u8 *)arg2 + (0x2C))) = table;
                    func_80047784(arg2,
                        table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                }
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_9E.as_s16 = 0;
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_A0.at00_s16.v = 0x14;
                ((Rec_func_800A9E70_arg0 *)arg0)->unk_9A.as_u8 = actor_state;
            }
        }

        ((Rec_func_800A9E70_arg0 *)arg0)->unk_98 &= 0xFFF3;

        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175998) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80174258(arg0, arg1, arg2, arg3);
            (*(void * *)((u8 *)arg2 + (0x2C))) = D_80175988;
            func_80047784(arg2,
                D_80175988[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                0);
            ((Rec_func_800A9E70_arg0 *)arg0)->unk_90.at00_s32.v = 0;
            return;
        }

        if ((s16)func_800A1C58(arg3) != 0) {
            if ((s16)func_800AAB10(arg0, arg1, arg2, arg3) != 0) {
                func_801751C0(arg0, arg1, arg2, arg3);
            }
        }
    }

    result = func_8009FB34(((S_801717F4_2 *)arg2)->unk_24.at00.v, ((S_801717F4_2 *)arg2)->unk_24.at01.v);
    ((S_801717F4_2 *)arg2)->unk_26 = result;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            goto special_cleanup;
        }
        if (((S_801717F4_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto ordinary_cleanup;
        }
        if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((s16)func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) != 0) {
                    return;
                }
            }
            if ((s16)func_80172A94(arg0, arg1, arg2, 0) == 0) {
                return;
            }
            state = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = state;
            if (!(state & 0x8000)) {
                goto ordinary_cleanup;
            }
        }

        state = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF;
        if ((u32)(state - 1) >= 12) {
            goto ordinary_cleanup;
        }
        (void)jt_keep;
        goto *D_80170808[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((s16)func_801727B8(arg0, arg1, arg2, arg3) != 0) {
            return;
        }
        func_8017297C(arg0, arg1, arg2, arg3);
        ASM_KEEP(p0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        return;

jt_c10:
        func_80174798(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 direction;

            direction = func_800A0818(
                ((S_801717F4_2 *)arg2)->unk_24.at00.v, ((S_801717F4_2 *)arg2)->unk_24.at01.v,
                ((S_801717F4_4 *)origin)->unk_24, ((S_801717F4_4 *)origin)->unk_25,
                &scratch);
            player = D_800814A8;
#ifndef __mips__
#endif
            ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = direction;
            if (((S_801717F4_5 *)player)->unk_9A == 0x11) {
                goto aaf_cleanup;
            }
            goto special_cleanup;
        }

jt_c12:
special_cleanup:
        func_800A9A0C(arg3);
        return;

jt_c1:
jt_c2:
jt_c3:
aaf_cleanup:
        func_800AAF00(arg0, arg1, arg2, D_801759D0, &D_801717F4);
        return;

jt_c4:
jt_c11:
ordinary_cleanup:
        func_80171FE8(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x2000)) {
        s32 index = (s8)result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((s16)func_8009FD7C(
                        ((S_801717F4_2 *)arg2)->unk_24.at00.v, ((S_801717F4_2 *)arg2)->unk_24.at01.v,
                        ((S_801717F4_4 *)origin)->unk_24, ((S_801717F4_4 *)origin)->unk_25) != 0) {
                    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
                        ((S_801717F4_2 *)arg2)->unk_24.at00.v, ((S_801717F4_2 *)arg2)->unk_24.at01.v,
                        ((S_801717F4_4 *)origin)->unk_24, ((S_801717F4_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }
}
