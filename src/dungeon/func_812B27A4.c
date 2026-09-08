#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80165FA4_0 {
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
    u8 pad_A4[0x12];
    s16 unk_B6;
} S_80165FA4_0;   /* arg0 in func_80165FA4 */


typedef struct S_80165FA4_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_80165FA4_2;   /* arg2 in func_80165FA4 */


typedef struct S_80165FA4_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_80165FA4_4;   /* origin in func_80165FA4 */

typedef struct S_80165FA4_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80165FA4_5;   /* player in func_80165FA4 */



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
extern void func_80166168(void) __attribute__((noreturn));
extern void func_80166510(void);
extern void func_801666C8(void *, void *, void *, void *);
extern s32 func_80166E10(void *, void *, void *, void *);
extern void func_801670A8(void *, void *, void *, void *);
extern s32 func_801671CC(void *, void *, void *, void *);
extern void func_80169078(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern void *D_80164818[];
extern u8 D_80165FA4[];
extern u8 D_80169C30[];
extern u8 D_80169C38[];
extern u8 D_80169C88[];
extern u8 D_80169C90[];
extern u8 D_80169CA0[];
extern u8 D_80169CA8[];

void func_80165FA4(void *arg0, void *arg1, void *arg2, void *arg3)
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
        ((S_80165FA4_0 *)arg0)->unk_9A = 0xE;
        func_80166510();
        return;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        void *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_80165FA4_2 *)arg2)->unk_2C == D_80169C90) {
            return;
        }
        table = D_80169CA0;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            ((u8 *)table)[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((S_80165FA4_2 *)arg2)->unk_2C == D_80169C90) {
            ((S_80165FA4_0 *)arg0)->unk_9A = 0xD;
            ((S_80165FA4_0 *)arg0)->unk_9B = 1;
            ((S_80165FA4_0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= 0xFFFBFFFF;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_80169CA0) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        {
            u8 current_state = ((S_80165FA4_0 *)arg0)->unk_9A;
            u32 actor_state = 0xE;
            void *current;
            void *table;

#ifndef __mips__
#endif
            if (current_state != actor_state) {
                ((S_80165FA4_0 *)arg0)->unk_9A = actor_state;
                ((S_80165FA4_0 *)arg0)->unk_B6 = 0;
            }
            current = ((S_80165FA4_2 *)arg2)->unk_2C;
            if (current == D_80169CA8) {
                if (((S_80165FA4_2 *)arg2)->unk_14 & 0xE000) {
#ifdef __mips__
                    register void *state_table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
                    state_table = D_80169C30;
                    ASM_TAILSLOT_PIN(state_table);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
#endif
                    func_80166168();
                }
            } else {
                table = D_80169C30;
                if (current != table) {
                    ASM_KEEP(current);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
                    (*(void * *)((u8 *)arg2 + 0x2C)) = table;
                    func_80047784(arg2,
                        ((u8 *)table)[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                    ((S_80165FA4_2 *)arg2)->unk_05 = 1;
                    ((S_80165FA4_0 *)arg0)->unk_A2.s = 0;
                    ((S_80165FA4_0 *)arg0)->unk_9E = 0;
                }
            }
        }

        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
        ((S_80165FA4_0 *)arg0)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80169C38) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            s16 delta;

            func_800AA888(arg0, arg1, arg2, arg3);
            delta = ((S_80165FA4_0 *)arg0)->unk_92.u - ((S_80165FA4_0 *)arg0)->unk_A2.u;
            ((S_80165FA4_0 *)arg0)->unk_A2.s = 0;
            ((S_80165FA4_0 *)arg0)->unk_9E = 0;
            ((S_80165FA4_0 *)arg0)->unk_92.s = delta;
            func_80169078(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_80165FA4_2 *)arg2)->unk_24.at00.v, ((S_80165FA4_2 *)arg2)->unk_24.at01.v);
    ((S_80165FA4_2 *)arg2)->unk_26 = result;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_80165FA4_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_801671CC(arg0, arg1, arg2, 0) << 16) == 0) {
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
        goto *D_80164818[(u32)(state - 1)];

jt_c8:
jt_c9:
        if ((func_80166E10(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_801670A8(arg0, arg1, arg2, arg3);
        return;

jt_c5:
jt_c6:
jt_c7:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

        coordinate = func_800A0818(
            ((S_80165FA4_2 *)arg2)->unk_24.at00.v, ((S_80165FA4_2 *)arg2)->unk_24.at01.v,
            ((S_80165FA4_4 *)origin)->unk_24, ((S_80165FA4_4 *)origin)->unk_25,
            &scratch);
        player = D_800814A8;
#ifndef __mips__
#endif
        ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = coordinate;
        if (((S_80165FA4_5 *)player)->unk_9A == 0x11) {
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
        func_800AAF00(arg0, arg1, arg2, D_80169C88, D_80165FA4);
        return;

jt_c4:
jt_c10:
jt_c11:
generic:
        func_801666C8(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_80165FA4_2 *)arg2)->unk_24.at00.v, ((S_80165FA4_2 *)arg2)->unk_24.at01.v,
                        ((S_80165FA4_4 *)origin)->unk_24, ((S_80165FA4_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
                        ((S_80165FA4_2 *)arg2)->unk_24.at00.v, ((S_80165FA4_2 *)arg2)->unk_24.at01.v,
                        ((S_80165FA4_4 *)origin)->unk_24, ((S_80165FA4_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }
}
