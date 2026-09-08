#include "common.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_D_800E3D7C.h"


s32 func_80042900(void *, s32);
void func_80042B68(void *, s32);
void func_80047784(void *, s32, s32);
s32 func_8009A180(void *, void *);
s16 func_8009FD40(void *, void *);
s32 func_800A2C34(void *);
s32 func_800A6D30(void);
void func_800A9A04(void *);
void func_800A9A0C(void *);
void func_800AA258(void *, s32, void *, void *);
s32 func_800AA6B4(void *, s32, void *, void *);
void func_800AA888(void *, s32, void *, void *);
void func_8016DA34(void) __attribute__((noreturn));
void func_8016DAA4(void *, s32, void *, void *);

extern u16 D_80013714;
extern u8 *D_800814A8;
extern u8 D_80082E80[];
extern s16 D_80083228;
extern u8 D_80083460[];
extern u16 D_80083462;
extern u8 D_8016B778[];
extern u8 D_801746A4[];
extern u8 D_801746AC[];
extern u8 D_801746C4[];


typedef struct S_8016D6F0_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x18];
    u8 unk_B4;
} S_8016D6F0_0;   /* arg0 in func_8016D6F0 */


typedef struct S_8016D6F0_2 {
    u8 pad_00[0x14A8];
    u8 * unk_14A8;
    u8 pad_14AC[0x1D7C];
    s16 unk_3228;
    u8 pad_322A[0x238];
    u16 unk_3462;
} S_8016D6F0_2;   /* base8008 in func_8016D6F0 */


typedef struct S_8016D6F0_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016D6F0_4;   /* counter_base in func_8016D6F0 */

typedef struct S_8016D6F0_5 {
    u8 pad_00[0x3714];
    u16 unk_3714;
} S_8016D6F0_5;   /* base8001 in func_8016D6F0 */

typedef struct S_8016D6F0_6 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8016D6F0_6;   /* clear_base in func_8016D6F0 */

typedef struct S_8016D6F0_7 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8016D6F0_7;   /* room_base in func_8016D6F0 */

typedef struct S_8016D6F0_8 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016D6F0_8;   /* update_base in func_8016D6F0 */

typedef struct S_8016D6F0_9 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8016D6F0_9;   /* ((S_8016D6F0_2 *)base8008)->unk_14A8 in func_8016D6F0 */

void func_8016D6F0(S_8016D6F0_0 *arg0, s32 arg1, Rec_D_80082E80 *arg2, void *arg3)
{
    S_8016D6F0_7 *room_base;
    register u8 *table ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    u8 *counter_base;
    u8 *base8008;
    u8 *base8001;
    u8 *clear_page;   /* MATCH pin: load-bearing for the whole function shape */
    u8 *clear_base;
    void *call_obj;   /* MATCH pin: retail basic-block layout depends on it */
    register u8 *update_base ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 state;
    s32 bits;
    s32 mask;
    s8 room;

    state = arg0->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }
       /* MATCH pin: retail delay-slot fill depends on it */
    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    base8008 = (u8 *)0x80080000;
    table = D_801746A4;
    ASM_KEEP(base8008);   /* MATCH pin: retail schedule: same instructions, different order without it */
    arg2->unk_2C.as_pu8 = table;
    func_80047784(
        arg2,
        table[((((S_8016D6F0_2 *)base8008)->unk_3228 +
                ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    counter_base = D_80083460;
    ((S_8016D6F0_4 *)counter_base)->unk_0A--;
    func_8016DA34();
    return;

state_one:
    if ((func_80042900(arg3, 1) << 0x10) == 0) {
        goto post_actions;
    }
    base8008 = (u8 *)0x80080000;
    ASM_KEEP(base8008);   /* MATCH pin: retail schedule: same instructions, different order without it */
    if (((S_8016D6F0_2 *)base8008)->unk_3462 & 0x1000) {
        goto done;
    }
    if (arg0->unk_B4 == 0) {
        base8001 = (u8 *)0x80010000;
        if (!(((S_8016D6F0_5 *)base8001)->unk_3714 & 8)) {
            if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
                if (func_800AA6B4(arg0, arg1, arg2, D_801746C4) != 0) {
                    return;
                }
            }
            goto action_body;
        }
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_64.as_s16 != 0) {
        clear_page = (u8 *)0x80080000;
        ASM_KEEP(clear_page);   /* MATCH pin: load-bearing for the whole function shape */
        clear_base = clear_page + 0x3460;
        if (((S_8016D6F0_6 *)clear_base)->unk_10 ==
            (u32)((u8 *)arg3 - 0x20)) {
            ((S_8016D6F0_6 *)clear_base)->unk_10 &= 0x7FFFFFFF;
        }
    }

action_body:
    if ((func_800A2C34(arg3) << 0x10) != 0) {
        goto done;
    }
    bits = ((Rec_D_800E3D7C *)arg3)->unk_1C.as_s32;
    mask = bits & 0x100;
    call_obj = arg0;
    if (mask) {
        func_800AA258(call_obj, arg1, arg2, arg3);
        return;
    }
    if (bits & 0x80000) {
        func_800AA888(call_obj, arg1, arg2, arg3);
        func_8016DAA4(arg0, arg1, arg2, arg3);
        return;
    }
    if (((Rec_D_800E3D7C *)arg3)->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(arg3) << 0x10) != 0) {
        base8008 = (u8 *)0x80080000;
        ASM_KEEP(base8008);   /* MATCH pin: retail schedule: same instructions, different order without it */
        if ((func_8009A180(
                 arg3,
                 ((S_8016D6F0_9 *)(((S_8016D6F0_2 *)base8008)->unk_14A8))->unk_58 + 0x20)
             << 0x10) != 0) {
            goto done;
        }
    }
    func_800A9A0C(arg3);
    func_800A9A04(arg3);
    if ((func_80042900(arg3, 1) << 0x10) != 0) {
        room_base = D_80082E80;
        room = arg2->unk_26.as_s8;
        if ((room != room_base->unk_26) || (room < 0)) {
            if (func_8009FD40(room_base, arg2) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(arg3, 1);
        }
    }

second_check:
    if ((func_80042900(arg3, 1) << 0x10) != 0) {
        goto done;
    }

post_actions:
    table = D_801746AC;
    base8008 = (u8 *)0x80080000;
    ASM_KEEP(base8008);   /* MATCH pin: retail schedule: same instructions, different order without it */
    arg2->unk_2C.as_pu8 = table;
    func_80047784(
        arg2,
        table[((((S_8016D6F0_2 *)base8008)->unk_3228 +
                ((Rec_D_800E3D7C *)arg3)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    if (arg2->unk_14.at00_u16.v & 0x8000) {
        goto set_callback;
    }
    update_base = D_80083460;
    ((S_8016D6F0_8 *)update_base)->unk_0A++;
    arg0->unk_9B++;
    return;

state_two:
    if (!(arg2->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    update_base = D_80083460;
    ((S_8016D6F0_8 *)update_base)->unk_0A--;

set_callback:
    arg0->unk_8C = D_8016B778;

done:
    return;
}
