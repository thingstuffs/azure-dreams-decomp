#include "common.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_8017140C_0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    union { u16 u; s16 s; } unk_92;   /* accessed as both */
    u8 pad_94[0x4];
    u16 unk_98;
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x1A];
    union { s16 s; u16 u; } unk_B6;   /* accessed as both */
    s16 unk_B8;
} S_8017140C_0;   /* arg0 in func_8017140C */

typedef struct S_8017140C_1 {
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
} S_8017140C_1;   /* arg3 in func_8017140C */

typedef struct S_8017140C_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0x1E];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_8017140C_2;   /* arg2 in func_8017140C */


typedef struct S_8017140C_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8017140C_4;   /* origin in func_8017140C */

typedef struct S_8017140C_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_8017140C_5;   /* player in func_8017140C */



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
extern void func_80171964(void *, void *);
extern void func_80171B1C(void *, void *, void *, void *);
extern s32 func_80172264(void *, void *, void *, void *);
extern void func_80172428(void *, void *, void *, void *);
extern s32 func_80172550(void *, void *, void *, s32);
extern void func_80173C34(void *, void *, void *, void *);
extern void func_80175068(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern u8 D_8017586C[];
extern u8 D_80175874[];
extern u8 D_80175884[];
extern u8 D_8017588C[];
extern u8 D_80175894[];

void func_8017140C(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s8 result;
    u16 state;

    if (D_80083462 & 0x1000) {
        ((S_8017140C_0 *)arg0)->unk_9A = 0xE;
        func_80171964(arg0, arg1);
        return;
    }

    if (((S_8017140C_1 *)arg3)->unk_25 == 0) {
        u8 *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_8017140C_2 *)arg2)->unk_2C == D_80175894) {
            return;
        }
        table = D_8017588C;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((S_8017140C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((S_8017140C_1 *)arg3)->unk_1C & 0x200) {
        if (((S_8017140C_2 *)arg2)->unk_2C == D_80175894) {
            ((S_8017140C_0 *)arg0)->unk_9A = 0xD;
            ((S_8017140C_0 *)arg0)->unk_9B = 1;
            ((S_8017140C_0 *)arg0)->unk_8C = 0;
            ((S_8017140C_1 *)arg3)->unk_1C &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_8017588C) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        void *current;
        u8 *table;

        if (((S_8017140C_1 *)arg3)->unk_1C & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        if (((S_8017140C_0 *)arg0)->unk_9A != 0xE) {
            ((S_8017140C_0 *)arg0)->unk_9A = 0xE;
        }

        current = ((S_8017140C_2 *)arg2)->unk_2C;
        table = D_8017586C;
        if (current != table) {
            (*(void * *)((u8 *)arg2 + 0x2C)) = table;
            func_80047784(arg2,
                table[((D_80083228 + ((S_8017140C_1 *)arg3)->unk_2A + 0x100) >> 9) & 7],
                0);
            ((S_8017140C_2 *)arg2)->unk_05 = 1;
            ((S_8017140C_0 *)arg0)->unk_B6.s = 0;
            ((S_8017140C_0 *)arg0)->unk_B8 = 0;
        }

        ((S_8017140C_1 *)arg3)->unk_1C |= 0x40000;
        ((S_8017140C_0 *)arg0)->unk_98 &= 0xFFF7;

        if (((S_8017140C_1 *)arg3)->unk_64 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_80175874) != 0) {
                return;
            }
        }

        if (((S_8017140C_1 *)arg3)->unk_1C & 0x80000) {
            s16 delta;

            func_800AA888(arg0, arg1, arg2, arg3);
            delta = ((S_8017140C_0 *)arg0)->unk_92.u - ((S_8017140C_0 *)arg0)->unk_B6.u;
            ((S_8017140C_0 *)arg0)->unk_B6.s = 0;
            ((S_8017140C_0 *)arg0)->unk_B8 = 0;
            ((S_8017140C_0 *)arg0)->unk_92.s = delta;
            func_80173C34(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            if ((func_800AAB10(arg0, arg1, arg2, arg3) << 16) != 0) {
                func_80175068(arg0, arg1, arg2, arg3);
            }
        }
    }

    result = func_8009FB34(((S_8017140C_2 *)arg2)->unk_24.at00.v, ((S_8017140C_2 *)arg2)->unk_24.at01.v);
    ((S_8017140C_2 *)arg2)->unk_26 = result;

    if (((S_8017140C_1 *)arg3)->unk_6D > 0) {
        if (((S_8017140C_1 *)arg3)->unk_1C & 0x20) {
            goto case_12;
        }
        if (((S_8017140C_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((S_8017140C_1 *)arg3)->unk_46 & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_80172550(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((S_8017140C_1 *)arg3)->unk_46 | 0x4000;
            ((S_8017140C_1 *)arg3)->unk_46 = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        {
            static void *const sw_keep[] = {
                &&case_123, &&generic, &&sw_case89, &&sw_case567, &&case_12
            };
            extern void *const D_80170808[];
            u32 swi = (u32)((((S_8017140C_1 *)arg3)->unk_46 & 0x3FFF) - 1);

            if (swi >= 12) {
                goto generic;
            }
            (void)sw_keep;
            goto *D_80170808[swi];
        }
sw_case89:
        if ((func_80172264(arg0, arg1, arg2, arg3) << 16) != 0) {
            return;
        }
        func_80172428(arg0, arg1, arg2, arg3);
        return;

sw_case567:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_8017140C_2 *)arg2)->unk_24.at00.v, ((S_8017140C_2 *)arg2)->unk_24.at01.v,
                ((S_8017140C_4 *)origin)->unk_24, ((S_8017140C_4 *)origin)->unk_25,
                &scratch);
            player = D_800814A8;
#ifndef __mips__
            
#endif
            ((S_8017140C_1 *)arg3)->unk_2A = coordinate;
            if (((S_8017140C_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }

case_12:
        func_800A9A0C(arg3);
        return;

case_123:
        func_800AAF00(arg0, arg1, arg2, D_80175884, func_8017140C);
        return;

generic:
        func_80171B1C(arg0, arg1, arg2, arg3);
        return;
    }

    if (!(((S_8017140C_1 *)arg3)->unk_1C & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((S_8017140C_1 *)arg3)->unk_1C & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_8017140C_2 *)arg2)->unk_24.at00.v, ((S_8017140C_2 *)arg2)->unk_24.at01.v,
                        ((S_8017140C_4 *)origin)->unk_24, ((S_8017140C_4 *)origin)->unk_25) << 16) != 0) {
                    ((S_8017140C_1 *)arg3)->unk_2A = func_800A0818(
                        ((S_8017140C_2 *)arg2)->unk_24.at00.v, ((S_8017140C_2 *)arg2)->unk_24.at01.v,
                        ((S_8017140C_4 *)origin)->unk_24, ((S_8017140C_4 *)origin)->unk_25,
                        &scratch);
                }
            }
        }
    }
}
