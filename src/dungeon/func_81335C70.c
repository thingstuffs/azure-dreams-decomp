#include "common.h"
#include "m2c_compat.h"

typedef struct S_8016CC70_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016CC70_0;   /* obj in func_8016CC70 */

typedef struct S_8016CC70_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x10];
    s8 unk_26;
    u8 pad_27[0x5];
    u8 * unk_2C;
} S_8016CC70_1;   /* target in func_8016CC70 */

typedef struct S_8016CC70_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
    u8 pad_26[0x4];
    s16 unk_2A;
    u8 pad_2C[0x38];
    s16 unk_64;
    u8 pad_66[0x7];
    s8 unk_6D;
} S_8016CC70_2;   /* actor in func_8016CC70 */

typedef struct S_8016CC70_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016CC70_3;   /* counter_base in func_8016CC70 */

typedef struct S_8016CC70_4 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_8016CC70_4;   /* held_base in func_8016CC70 */

typedef struct S_8016CC70_5 {
    u8 pad_00[0x58];
    void * unk_58;
} S_8016CC70_5;   /* D_800814A8 in func_8016CC70 */

typedef struct S_8016CC70_6 {
    u8 pad_00[0x26];
    s8 unk_26;
} S_8016CC70_6;   /* room_base in func_8016CC70 */

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
s32 func_800AA6B4(void *, s32, void *, s32);
void func_800AA79C(void *, s32, void *, void *);
void func_800AA888(void *, s32, void *, void *);
void func_8016D4B8(void *, s32, void *, void *);
extern void *D_800814A8;
extern M2C_UNK D_80082E80;
extern s16 D_80083228;
extern M2C_UNK D_80083460;
extern M2C_UNK D_8016A36C;
extern u8 D_80173AC8[];
extern u8 D_80173AD0[];

void func_8016CC70(void *arg0, s32 arg1, void *arg2, void *arg3) {
    void *obj = arg0;
    s32 middle = arg1;
    void *target = arg2;
    register void *actor ASM_REG("$17") = arg3;   /* MATCH pin: load-bearing for the whole function shape */
    u8 *held_base;
    void *callback;
    void *room_base;
    register u8 *counter_base ASM_REG("$2");   /* MATCH pin: retail immediate-load split depends on it */
    s32 state;
    s32 kind;
    s32 bits;
    s8 room;

    state = ((S_8016CC70_0 *)obj)->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (!(((S_8016CC70_1 *)target)->unk_14 & 0xE000)) {
        goto done;
    }
    kind = ((S_8016CC70_0 *)obj)->unk_AC;
    if (kind == 0xE) {
        goto zero_setup;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto zero_setup;
        }
        goto decrement_counter;
    }
    if (kind != 0xF) {
        goto decrement_counter;
    }
zero_setup:
    (*(u8 **)((u8 *)target + 0x2C)) = D_80173AC8;
    func_80047784(target, D_80173AC8[((D_80083228 + ((S_8016CC70_2 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
decrement_counter:
    counter_base = (u8 *)&D_80083460;
    ((S_8016CC70_3 *)counter_base)->unk_0A--;
    goto counter_changed;

state_one:
    kind = ((S_8016CC70_0 *)obj)->unk_AC;
    if (kind == 0xE) {
        goto one_setup;
    }
    if (kind < 0xF) {
        if (kind == 0xD) {
            goto one_setup;
        }
        goto call_check;
    }
    if (kind != 0xF) {
        goto call_check;
    }
one_setup:
    if (((S_8016CC70_1 *)target)->unk_2C != D_80173AC8) {
        (*(u8 **)((u8 *)target + 0x2C)) = D_80173AC8;
        func_80047784(target, D_80173AC8[((D_80083228 + ((S_8016CC70_2 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);
    }
call_check:
    if ((func_80042900(actor, 1) << 0x10) != 0) {
        goto action_body;
    }
    kind = ((S_8016CC70_0 *)obj)->unk_AC;
    if (kind == 0xE) {
        goto update_tiles;
    }
    if (kind < 0xF) {
        goto low_kind;
    }
    goto high_kind;

action_body:
    counter_base = (u8 *)0x80080000;
    ASM_KEEP(counter_base);   /* MATCH pin: load-bearing for the whole function shape */
    held_base = counter_base + 0x3460;
    if (((S_8016CC70_4 *)held_base)->unk_02 & 0x1000) {
        goto done;
    }
    if (((S_8016CC70_2 *)actor)->unk_64 != 0) {
        if (func_800AA6B4(obj, middle, target, 0) != 0) {
            goto done;
        }
    }
    if (((S_8016CC70_2 *)actor)->unk_25 == 0) {
        if (((S_8016CC70_4 *)held_base)->unk_02 & 0x2008) {
            goto done;
        }
        func_800AA79C(obj, middle, target, actor);
        goto done;
    }
    if ((func_800A2C34(actor) << 0x10) != 0) {
        goto done;
    }
    bits = ((S_8016CC70_2 *)actor)->unk_1C;
    if (bits & 0x100) {
        func_800AA258(obj, middle, target, actor);
        goto done;
    }
    if (bits & 0x80000) {
        func_800AA888(obj, middle, target, actor);
        func_8016D4B8(obj, middle, target, actor);
        goto done;
    }
    if (((S_8016CC70_2 *)actor)->unk_6D == 0) {
        goto done;
    }
    if ((func_800A2C34(actor) << 0x10) != 0) {
        if ((func_8009A180(actor, (u8 *)((S_8016CC70_5 *)D_800814A8)->unk_58 + 0x20) << 0x10) != 0) {
            goto done;
        }
    }
    func_800A9A0C(actor);
    func_800A9A04(actor);
    if ((func_80042900(actor, 1) << 0x10) != 0) {
        room_base = &D_80082E80;
        room = ((S_8016CC70_1 *)target)->unk_26;
        if ((room != ((S_8016CC70_6 *)room_base)->unk_26) || (room < 0)) {
            if (func_8009FD40(room_base, target) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(actor, 1);
        }
    }
second_check:
    if ((func_80042900(actor, 1) << 0x10) != 0) {
        goto done;
    }

post_actions:
    kind = ((S_8016CC70_0 *)obj)->unk_AC;
    if (kind == 0xE) {
        goto update_tiles;
    }
    if (kind < 0xF) {
low_kind:
        if (kind == 0xD) {
            goto update_tiles;
        }
        goto after_tiles;
    }
high_kind:
    if (kind != 0xF) {
        goto after_tiles;
    }
update_tiles:
    (*(u8 **)((u8 *)target + 0x2C)) = D_80173AD0;
    func_80047784(target, D_80173AD0[((D_80083228 + ((S_8016CC70_2 *)actor)->unk_2A + 0x100) >> 9) & 7], 0);

after_tiles:
    if (((S_8016CC70_1 *)target)->unk_14 & 0x8000) {
        goto set_callback;
    }
    counter_base = (u8 *)&D_80083460;
    ((S_8016CC70_3 *)counter_base)->unk_0A++;
counter_changed:
    ((S_8016CC70_0 *)obj)->unk_9B++;
    goto done;

state_two:
    if (!(((S_8016CC70_1 *)target)->unk_14 & 0xE000)) {
        goto done;
    }
    counter_base = (u8 *)&D_80083460;
    ((S_8016CC70_3 *)counter_base)->unk_0A--;
set_callback:
    callback = &D_8016A36C;
    ((S_8016CC70_0 *)obj)->unk_8C = callback;

done:
    ASM_KEEP(obj);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
    ASM_KEEP(middle);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(target);   /* MATCH pin: retail register colouring depends on it */
    return;
}
