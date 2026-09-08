#include "common.h"
#include "records/Rec_D_800E3D7C.h"
#include "records/Rec_D_800814A8.h"

typedef struct S_80173204_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
} S_80173204_0;   /* arg0 in func_80173204 */

typedef struct S_80173204_1 {
    u8 pad_00[0xC];
    union { u8 u8; s32 s32; } unk_0C;   /* accessed as both */
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_80173204_1;   /* arg2 in func_80173204 */


typedef struct S_80173204_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173204_3;   /* counter_base in func_80173204 */

typedef struct S_80173204_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80173204_4;   /* status in func_80173204 */


typedef struct S_80173204_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_80173204_6;   /* floor_base in func_80173204 */

typedef struct S_80173204_7 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_80173204_7;   /* counter in func_80173204 */



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
extern void func_80173A20(void *, s32, void *, void *);

extern void *D_800814A8;
extern s32 D_80082E80;
extern s16 D_80083228[];
extern u8 D_80083460[];
extern u8 D_80170E54;
extern u8 D_80173C9C[];
extern u8 D_80173CA4[];

void func_80173204(S_80173204_0 *arg0, s32 arg1, S_80173204_1 *arg2, Rec_D_800E3D7C *arg3)
{
    s32 state;
    s32 flags;
    s8 floor;
    register u8 *status ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s32 mode ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *counter_base;
    u8 *floor_base;
    u8 *status_page;
    register u8 *table ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    mode = arg1;
    ASM_KEEP_NV(mode);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (arg0->unk_9B < 2U) {
        if (arg2->unk_0C.u8 < 0x33U) {
            goto dispatch;
        }
        arg2->unk_0C.s32 += -0x30303;
    } else if (arg2->unk_0C.u8 < 0x80U) {
        arg2->unk_0C.s32 += 0x30303;
    }

dispatch:
    state = arg0->unk_9B;
    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        goto done;
    }
    if (state == 2) {
        goto state_2;
    }
    goto done;

state_0:
    arg3->unk_1C.as_s32 |= 0x10000000;
    if (!(arg2->unk_14 & 0xE000)) {
        goto done;
    }
    table = D_80173C9C;
    arg2->unk_2C = table;
    func_80047784(
        arg2,
        table[((D_80083228[0] + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    counter_base = D_80083460;
    ((S_80173204_3 *)counter_base)->unk_0A =
        ((S_80173204_3 *)counter_base)->unk_0A - 1;
    goto increment_state;

state_1:
    if ((func_80042900(arg3, 1) << 16) == 0) {
        table = D_80173CA4;
        arg2->unk_2C = table;
        func_80047784(
            arg2,
            table[((D_80083228[0] + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
            0);
        if (arg2->unk_14 & 0x8000) {
            arg3->unk_1C.as_s32 &= ~0x200;
            arg3->unk_1C.as_s32 &= 0xEFFFFFFF;
            arg2->unk_0C.s32 = 0x808080;
            arg0->unk_8C = &D_80170E54;
            goto done;
        }
        goto increment_counter;
    }

    status_page = (u8 *)0x80080000;
    ASM_KEEP_NV(status_page);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot fill; the source shape that makes it unnecessary has not been found */
    status = status_page + 0x3460;
    ASM_USE2(status_page, status);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    if (((S_80173204_4 *)status)->unk_02 & 0x1000) {
        goto done;
    }
    if (arg3->unk_64.as_s16 != 0) {
        if (func_800AA6B4(arg0, mode, arg2, 0) != 0) {
            goto done;
        }
    }
    if (arg3->unk_24.at01_u8.v == 0) {
        if (((S_80173204_4 *)status)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(arg0, mode, arg2, arg3);
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        goto done;
    }

    flags = arg3->unk_1C.as_s32;
    if (flags & 0x100) {
        func_800AA258(arg0, mode, arg2, arg3);
        goto done;
    }
    if (flags & 0x80000) {
        func_800AA888(arg0, mode, arg2, arg3);
        func_80173A20(arg0, mode, arg2, arg3);
        goto done;
    }
    if (arg3->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 16) != 0) {
        if ((func_8009A180(
                 arg3,
                 ((Rec_D_800814A8 *)D_800814A8)->unk_58.as_s32 + 0x20) << 16) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 16) != 0) {
        floor_base = (u8 *)&D_80082E80;
        floor = arg2->unk_26;
        if (!((floor == ((S_80173204_6 *)floor_base)->unk_26) && (floor >= 0))) {
            if (func_8009FD40(floor_base, arg2) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(arg3, 1);
        }
    }

second_check:
    if ((func_80042900(arg3, 1) << 16) != 0) {
        goto done;
    }
    table = D_80173CA4;
    arg2->unk_2C = table;
    func_80047784(
        arg2,
        table[((D_80083228[0] + arg3->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    if (arg2->unk_14 & 0x8000) {
        arg3->unk_1C.as_s32 &= ~0x200;
        arg3->unk_1C.as_s32 &= 0xEFFFFFFF;
        arg2->unk_0C.s32 = 0x808080;
        arg0->unk_8C = &D_80170E54;
        goto done;
    }
increment_counter:
    {
        register u8 *counter ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */

        counter = D_80083460;
        ((S_80173204_7 *)counter)->unk_0A++;
    }

increment_state:
    arg0->unk_9B++;
    goto done;

state_2:
    if (!(arg2->unk_14 & 0x8000)) {
        if (arg2->unk_0C.u8 < 0x80U) {
            goto done;
        }
    }
    {
        u8 *counter = D_80083460;
        ((S_80173204_7 *)counter)->unk_0A--;
    }
    arg3->unk_1C.as_s32 &= 0xEFFFFFFF;
    arg2->unk_0C.s32 = 0x808080;
    arg3->unk_1C.as_s32 &= ~0x200;
    arg0->unk_8C = &D_80170E54;

done:
    return;
}
