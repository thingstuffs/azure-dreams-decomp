#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"


extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, void *, void *, void *);
extern s32 func_800AA6B4(void *, void *, void *, void *);
extern void func_800AA79C(void *, void *, void *, void *);
extern void func_800AA888(void *, void *, void *, void *);
extern void func_801737DC(void *, void *, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80170E5C[];
extern u8 D_80174520[];
extern u8 D_80174538[];


typedef struct S_80173254_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173254_0;   /* arg0 in func_80173254 */



typedef struct S_80173254_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173254_3;   /* system_base in func_80173254 */


typedef struct S_80173254_5 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173254_5;   /* origin in func_80173254 */

void func_80173254(void *arg0, void *arg1, void *arg2, void *arg3)
{
    void *p1;
    void *p2;
    u8 state;

    p1 = arg1;
    p2 = arg2;
#define arg1 p1
#define arg2 p2

    state = ((S_80173254_0 *)arg0)->unk_9B;
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    return;

state_zero:
    if (((Rec_D_80082E80 *)arg2)->unk_14.at00_u16.v & 0xE000) {
        u8 *table;
        u8 *system_base;

        table = D_80174538;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        system_base = (u8 *)&D_80083460;
        ((S_80173254_3 *)system_base)->unk_0A--;
        ((S_80173254_0 *)arg0)->unk_9B++;
    }
    return;

state_one:
    {
        u8 *system_base;

        if ((func_80042900(arg3, 1) << 16) != 0) {
            s32 flags;

            system_base = (u8 *)&D_80083460;
            if (((S_80173254_3 *)system_base)->unk_02 & 0x1000) {
                return;
            }

            if ((((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) &&
                (func_800AA6B4(arg0, arg1, arg2, 0) != 0)) {
                return;
            }

            if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
                if (((S_80173254_3 *)system_base)->unk_02 & 0x2008) {
                    return;
                }
                func_800AA79C(arg0, arg1, arg2, arg3);
                return;
            }

            if ((func_800A2C34(arg3) << 16) != 0) {
                return;
            }

            flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
            if (flags & 0x100) {
                func_800AA258(arg0, arg1, arg2, arg3);
                return;
            }

            if (flags & 0x80000) {
                func_800AA888(arg0, arg1, arg2, arg3);
                func_801737DC(arg0, arg1, arg2, arg3);
                return;
            }

            if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
                return;
            }

            if ((func_800A2C34(arg3) << 16) != 0) {
                if ((func_8009A180(arg3,
                        (u8 *)((Rec_D_800814A8 *)D_800814A8)->unk_58.as_pv + 0x20) << 16) != 0) {
                    return;
                }
            }

            func_800A9A0C(arg3);
            func_800A9A04(arg3);

            if ((func_80042900(arg3, 1) << 16) != 0) {
                u8 *origin;
                s8 coordinate;

                origin = D_80082E80;
                coordinate = ((Rec_D_80082E80 *)arg2)->unk_26.as_s8;
                if ((((coordinate == ((S_80173254_5 *)origin)->unk_26) &&
                            (coordinate >= 0)) ||
                        (func_8009FD40(origin, arg2) < 2)) &&
                    ((func_800A6D30() & 7) == 0)) {
                    func_80042B68(arg3, 1);
                }
            }

            if ((func_80042900(arg3, 1) << 16) != 0) {
                return;
            }
        }
    }

    {
        u8 *table;

        table = D_80174520;
        (*(void * *)((u8 *)arg2 + 0x2C)) = table;
        func_80047784(arg2,
            table[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= ~0x200;
        ((S_80173254_0 *)arg0)->unk_8C = D_80170E5C;
    }
    ASM_KEEP(p2);   /* MATCH pin: load-bearing for the whole function shape */
}
