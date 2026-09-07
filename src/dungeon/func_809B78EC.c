#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801590EC_0 {
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
    u8 pad_A4[0xE];
    s16 unk_B2;
} S_801590EC_0;   /* arg0 in func_801590EC */


typedef struct S_801590EC_2 {
    u8 pad_00[0x5];
    u8 unk_05;
    u8 pad_06[0xE];
    u16 unk_14;
    u8 pad_16[0xE];
    union { struct { u8 v; } at00; struct { u16 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; } unk_24;   /* overlapping accesses */
    u8 unk_26;
    u8 pad_27[0x5];
    void * unk_2C;
} S_801590EC_2;   /* arg2 in func_801590EC */


typedef struct S_801590EC_4 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801590EC_4;   /* origin in func_801590EC */

typedef struct S_801590EC_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_801590EC_5;   /* player in func_801590EC */



typedef struct {
    u8 pad0[0xC];
    u16 flags;
    u8 padE[6];
} DungeonRecord;

extern s32 func_80042900(void *, s32);
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
extern void func_8015969C(void *, void *, void *, void *);
extern void func_80159854(void *, void *, void *, void *);
extern s32 func_80159F9C(void *, void *, void *, void *);
extern void func_8015A234(void *, void *, void *, void *);
extern void func_8015A358(void *, void *, void *, void *);
extern s32 func_8015A66C(void *, void *, void *, s32);
extern void func_8015C574(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s8 D_80082EA4;
extern s16 D_80083228;
extern u16 D_80083462;
extern s8 D_800E2970[];
extern u8 D_8015DE40[];
extern u8 D_8015DE48[];
extern u8 D_8015DE98[];
extern u8 D_8015DEA0[];
extern u8 D_8015DEB0[];
extern u8 D_8015DEB8[];

void func_801590EC(void *arg0, void *arg1, void *arg2, void *arg3)
{
    s32 scratch;
    s8 result;
    u16 state;

    if (D_80083462 & 0x1000) {
        ((S_801590EC_0 *)arg0)->unk_9A = 0xE;
        func_8015969C(arg0, arg1, arg2, arg3);
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
        u8 *table;

        func_800AA79C(arg0, arg1, arg2, arg3);
        if (((S_801590EC_2 *)arg2)->unk_2C == D_8015DEA0) {
            return;
        }
        table = D_8015DEB0;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        return;
    }

    if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x200) {
        if (((S_801590EC_2 *)arg2)->unk_2C == D_8015DEA0) {
            ((S_801590EC_0 *)arg0)->unk_9A = 0xD;
            ((S_801590EC_0 *)arg0)->unk_9B = 1;
            ((S_801590EC_0 *)arg0)->unk_8C = 0;
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 &= ~0x40000;
            return;
        }
        if (func_800AA924(arg0, arg1, arg2, D_8015DEB0) != 0) {
            return;
        }
    }

    if (!(D_80083462 & 0x2000)) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            return;
        }

        {
            void *current;
            u8 *table;

            if (((S_801590EC_0 *)arg0)->unk_9A != 0xE) {
                ((S_801590EC_0 *)arg0)->unk_9A = 0xE;
                ((S_801590EC_0 *)arg0)->unk_B2 = 0;
            }

            current = ((S_801590EC_2 *)arg2)->unk_2C;
            if (current == D_8015DEB8) {
                if (((S_801590EC_2 *)arg2)->unk_14 & 0xE000) {
                    u8 *tableA = D_8015DE40;

                    (*(void * *)((u8 *)arg2 + 0x2C)) = tableA;
                    func_80047784(arg2,
                        tableA[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                    ((S_801590EC_2 *)arg2)->unk_05 = 1;
                    ((S_801590EC_0 *)arg0)->unk_A2.s = 0;
                    ((S_801590EC_0 *)arg0)->unk_9E = 0;
                }
            } else {
                table = D_8015DE40;
                if (current != table) {
                    (*(void * *)((u8 *)arg2 + 0x2C)) = table;
                    func_80047784(arg2,
                        table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
                        0);
                    ((S_801590EC_2 *)arg2)->unk_05 = 1;
                    ((S_801590EC_0 *)arg0)->unk_A2.s = 0;
                    ((S_801590EC_0 *)arg0)->unk_9E = 0;
                }
            }
        }

        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 |= 0x40000;
        ((S_801590EC_0 *)arg0)->unk_98 &= 0xFFF7;

        if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
            if (func_800AA6B4(arg0, arg1, arg2, D_8015DE48) != 0) {
                return;
            }
        }

        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x80000) {
            s16 delta;

            func_800AA888(arg0, arg1, arg2, arg3);
            delta = ((S_801590EC_0 *)arg0)->unk_92.u - ((S_801590EC_0 *)arg0)->unk_A2.u;
            ((S_801590EC_0 *)arg0)->unk_A2.s = 0;
            ((S_801590EC_0 *)arg0)->unk_9E = 0;
            ((S_801590EC_0 *)arg0)->unk_92.s = delta;
            func_8015C574(arg0, arg1, arg2, arg3);
            return;
        }

        if ((func_800A1C58(arg3) << 16) != 0) {
            func_800AAB10(arg0, arg1, arg2, arg3);
        }
    }

    result = func_8009FB34(((S_801590EC_2 *)arg2)->unk_24.at00.v, ((S_801590EC_2 *)arg2)->unk_24.at01.v);
    ((S_801590EC_2 *)arg2)->unk_26 = result;

    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 > 0) {
        if (((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x20) {
            goto case_12;
        }
        if (((S_801590EC_2 *)arg2)->unk_24.at00u.v == *(u16 *)&D_80082EA4) {
            goto generic;
        }
        if (!(((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x8000)) {
            if (D_80083462 & 0x2000) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }
            if ((func_8015A66C(arg0, arg1, arg2, 0) << 16) == 0) {
                return;
            }
            state = ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v | 0x4000;
            ((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v = state;
            if (!(state & 0x8000)) {
                goto generic;
            }
        }

        {
            static void *const sw_keep[] = {
                &&case_123, &&generic, &&sw_case89, &&sw_case567, &&case_12
            };
            extern void *const D_80158808[];
            u32 swi = (u32)((((Rec_D_800E3D7C *)arg3)->unk_44.at02_u16.v & 0x3FFF) - 1);

            if (swi >= 12) {
                goto generic;
            }
            (void)sw_keep;
            goto *D_80158808[swi];
        }
sw_case89:
            if ((func_80159F9C(arg0, arg1, arg2, arg3) << 16) != 0) {
                return;
            }
            func_8015A234(arg0, arg1, arg2, arg3);
            return;

sw_case567:
        {
            u8 *origin = D_80082E80;
            void *player;
            s16 coordinate;

            coordinate = func_800A0818(
                ((S_801590EC_2 *)arg2)->unk_24.at00.v, ((S_801590EC_2 *)arg2)->unk_24.at01.v,
                ((S_801590EC_4 *)origin)->unk_24, ((S_801590EC_4 *)origin)->unk_25,
                &scratch);
            player = D_800814A8;
            ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = coordinate;
            if (((S_801590EC_5 *)player)->unk_9A == 0x11) {
                goto case_123;
            }
        }
            /* fallthrough */

case_12:
            func_800A9A0C(arg3);
            return;

case_123:
            func_800AAF00(arg0, arg1, arg2, D_8015DE98, func_801590EC);
            return;

generic:
            func_80159854(arg0, arg1, arg2, arg3);
            return;
    }

    if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x2000)) {
        s32 index = result;

        if ((index < 0) ||
            !(((DungeonRecord *)D_800E2970)[index].flags & 2)) {
            if (!(((Rec_D_800E3D7C *)arg3)->unk_1C.as_u32 & 0x430)) {
                u8 *origin = D_80082E80;

                if ((func_8009FD7C(
                        ((S_801590EC_2 *)arg2)->unk_24.at00.v, ((S_801590EC_2 *)arg2)->unk_24.at01.v,
                        ((S_801590EC_4 *)origin)->unk_24, ((S_801590EC_4 *)origin)->unk_25) << 16) != 0) {
                    ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 = func_800A0818(
                        ((S_801590EC_2 *)arg2)->unk_24.at00.v, ((S_801590EC_2 *)arg2)->unk_24.at01.v,
                        ((S_801590EC_4 *)origin)->unk_24, ((S_801590EC_4 *)origin)->unk_25,
                        &scratch);
                    return;
                }
            }
        }
    } else if ((func_80042900(arg3, 4) << 16) == 0) {
        if (((Rec_D_800814A8 *)D_800814A8)->unk_9A == 0x17) {
            func_8015A358(arg0, arg1, arg2, arg3);
        }
    }
}
