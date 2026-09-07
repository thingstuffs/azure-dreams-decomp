#include "common.h"
#include "records/Rec_func_800AA258_arg2.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_801736F4_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_801736F4_0;   /* arg0 in func_801736F4 */



typedef struct S_801736F4_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_801736F4_3;   /* counter in func_801736F4 */

typedef struct S_801736F4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_801736F4_4;   /* status in func_801736F4 */


typedef struct S_801736F4_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_801736F4_6;   /* room_base in func_801736F4 */



extern s32 func_80042900(void *, s32);
extern void func_80042B68(void *, s32);
extern void func_80047784(void *, u8, s32);
extern s32 func_8009A180(void *, s32);
extern s16 func_8009FD40(void *, void *);
extern s32 func_800A2C34(void *);
extern s32 func_800A6D30(void);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA79C(void *, s32, void *, void *);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_80173EF4(void *, s32, void *, void *);

extern void *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u8 D_80170E54;
extern u8 D_80174140[];
extern u8 D_80174188[];
extern u8 D_80174190[];

void func_801736F4(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    u8 *status;
    s32 flags;
    s32 state;

    state = ((S_801736F4_0 *)arg0)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto exit;
    }
    if (state == 2) {
        goto state_two;
    }
    goto exit;

state_zero:
    if (!(((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000)) {
        goto exit;
    }
    {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174190;
        func_80047784(
            arg2,
            D_80174190[((D_80083228
                         + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100)
                        >> 9) & 7],
            0);
    }
    {
        u8 *counter;
        counter = D_80083460;
        ((S_801736F4_3 *)counter)->unk_0A--;
    }
    ((S_801736F4_0 *)arg0)->unk_9B++;
    goto exit;

state_one:
    if (((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000) {
        void *current_table;
        current_table = ((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv;
        if (current_table == D_80174140) {
            ((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv = D_80174188;
        } else if (current_table == D_80174188) {
            ((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv = D_80174190;
        }
        func_80047784(
            arg2,
            ((u8 *)((Rec_func_800AA258_arg2 *)arg2)->unk_2C.as_pv)
                [((D_80083228
                   + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100)
                  >> 9) & 7],
            0);
    }

    if ((func_80042900(arg3, 1) << 16) == 0) {
        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174188;
        func_80047784(
            arg2,
            D_80174188[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100)
                        >> 9) & 7],
            0);
        if (((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0x8000) {
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= ~0x200;
            ((S_801736F4_0 *)arg0)->unk_8C = &D_80170E54;
            goto exit;
        }
        {
            u8 *counter = D_80083460;
            ((S_801736F4_3 *)counter)->unk_0A++;
        }
        ((S_801736F4_0 *)arg0)->unk_9B++;
        goto exit;
    } else {
    status = D_80083460;
    if (!(((S_801736F4_4 *)status)->unk_02 & 0x1000)
        && ((((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 == 0)
            || (func_800AA6B4(arg0, arg1, arg2, 0) == 0))) {

        if (((Rec_D_800E3D7C *)arg3)->unk_24.at01_u8.v == 0) {
            if (((S_801736F4_4 *)status)->unk_02 & 0x2008) {
                goto exit;
            }
            func_800AA79C(arg0, arg1, arg2, arg3);
            goto exit;
        }

        if ((func_800A2C34(arg3) << 16) != 0) {
            goto exit;
        }
        flags = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
        if (flags & 0x100) {
            func_800AA258(arg0, arg1, arg2, arg3);
            goto exit;
        }
        if (flags & 0x80000) {
            func_800AA888(arg0, arg1, arg2, arg3);
            func_80173EF4(arg0, arg1, arg2, arg3);
            goto exit;
        }
        if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
            goto exit;
        }
        if ((func_800A2C34(arg3) << 16) != 0) {
            if ((func_8009A180(
                     arg3,
                     ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32
                         + 0x20)
                 << 16)
                != 0) {
                goto exit;
            }
        }

        func_800A9A0C(arg3);
        func_800A9A04(arg3);
        if ((func_80042900(arg3, 1) << 16) != 0) {
            u8 *room_base;
            s32 room_value;
            room_base = D_80082E80;
            room_value = ((Rec_func_800AA258_arg2 *)arg2)->unk_26.as_s8;
            if (((room_value == ((S_801736F4_6 *)room_base)->unk_26)
                 && (room_value >= 0))
                || (func_8009FD40(room_base, arg2) < 2)) {
                if (!(func_800A6D30() & 7)) {
                    func_80042B68(arg3, 1);
                }
            }
        }
        if ((func_80042900(arg3, 1) << 16) != 0) {
            goto exit;
        }

        (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174188;
        func_80047784(
            arg2,
            D_80174188[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100)
                        >> 9) & 7],
            0);
        if (((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0x8000) {
            ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= ~0x200;
            ((S_801736F4_0 *)arg0)->unk_8C = &D_80170E54;
            goto exit;
        }
        {
            u8 *counter = D_80083460;
            ((S_801736F4_3 *)counter)->unk_0A++;
        }
        ((S_801736F4_0 *)arg0)->unk_9B++;
        goto exit;
    }
    }
    goto exit;

state_two:
    if (!(((Rec_func_800AA258_arg2 *)arg2)->unk_14 & 0xE000)) {
        goto exit;
    }
    {
        u8 *counter;
        counter = D_80083460;
        ((S_801736F4_3 *)counter)->unk_0A--;
    }
    ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32 &= ~0x200;
    (*(void * *)((u8 *)arg2 + 0x2C)) = D_80174188;
    func_80047784(
        arg2,
        D_80174188[((D_80083228 + ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100)
                    >> 9) & 7],
        0);
    ((S_801736F4_0 *)arg0)->unk_8C = &D_80170E54;
    goto exit;

exit:
    return;
}
