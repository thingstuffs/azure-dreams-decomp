#include "common.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"

typedef struct S_8016D0FC_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0xB];
    u8 unk_9B;
    u8 pad_9C[0x10];
    u8 unk_AC;
} S_8016D0FC_0;   /* arg0 in func_8016D0FC */

typedef struct S_8016D0FC_1 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_8016D0FC_1;   /* object in func_8016D0FC */

typedef struct S_8016D0FC_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8016D0FC_2;   /* counter_base in func_8016D0FC */

typedef struct S_8016D0FC_3 {
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
} S_8016D0FC_3;   /* actor in func_8016D0FC */




extern void func_80047784(void *, s32, s32);
extern s32 func_8009A180(void *, void *);
extern s32 func_800A2C34(void *);
extern void func_800A9A04(void *);
extern void func_800A9A0C(void *);
extern void func_800AA258(void *, s32, void *, void *);
extern s32 func_800AA6B4(void *, s32, void *, s32);
extern void func_800AA888(void *, s32, void *, void *);
extern void func_8016D4B8(void *, s32, void *, void *);

extern u8 D_8016A36C[];
extern u8 D_80173AC8[];
extern u8 D_80173AD0[];

/* Advance the actor state, updating directional tables and the shared counter. */
void func_8016D0FC(void *context, s32 callback_arg, void *object_arg, void *actor_arg)
{
    register void *object ASM_REG("$16") = object_arg;   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *actor = actor_arg;
    u8 *expected_table;
    u8 *current_table;
    s32 state;
    s32 kind;
    s32 actor_flags;
    s32 direction_index;

    state = ((S_8016D0FC_0 *)context)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_8016D0FC_1 *)object)->unk_14 & 0xE000)) {
            return;
        }
        current_table = ((u16)dungeonStatus.unk_0A);
        current_table--;
        dungeonStatus.unk_0A = current_table;
        kind = ((S_8016D0FC_0 *)context)->unk_AC;
        if (kind == 0xE || (kind < 0xF ? kind == 0xD : kind == 0xF)) {
            (*(u8 * *)((u8 *)object + 0x2C)) = D_80173AC8;
            direction_index = (gameWork.view.viewAngle + ((S_8016D0FC_3 *)actor)->unk_2A + 0x100) >> 9;
            func_80047784(object, D_80173AC8[direction_index & 7], 0);
        }
        ((S_8016D0FC_0 *)context)->unk_9B++;
        return;
    case 1:
        kind = ((S_8016D0FC_0 *)context)->unk_AC;
        if (kind == 0xE || (kind < 0xF ? kind == 0xD : kind == 0xF)) {
            current_table = ((S_8016D0FC_1 *)object)->unk_2C;
            expected_table = D_80173AC8;
            if (current_table != expected_table) {
                (*(u8 * *)((u8 *)object + 0x2C)) = expected_table;
                direction_index = (gameWork.view.viewAngle + ((S_8016D0FC_3 *)actor)->unk_2A + 0x100) >> 9;
                func_80047784(object, expected_table[direction_index & 7], 0);
            }
        }
        if (((S_8016D0FC_3 *)actor)->unk_25 != 0) {
            kind = ((S_8016D0FC_0 *)context)->unk_AC;
            if (kind == 0xE) {
                goto set_ad0;
            }
            if (kind < 0xF) {
                goto kind_lt_15;
            }
            goto kind_ge_15;
        }
        if (dungeonStatus.flags & 0x1000) {
            return;
        }
        if (((S_8016D0FC_3 *)actor)->unk_64 != 0) {
            if (func_800AA6B4(context, callback_arg, object, 0) != 0) {
                return;
            }
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            return;
        }
        actor_flags = ((S_8016D0FC_3 *)actor)->unk_1C;
        if (actor_flags & 0x100) {
            func_800AA258(context, callback_arg, object, actor);
            return;
        }
        if (actor_flags & 0x80000) {
            func_800AA888(context, callback_arg, object, actor);
            func_8016D4B8(context, callback_arg, object, actor);
            return;
        }
        if (((S_8016D0FC_3 *)actor)->unk_6D == 0) {
            return;
        }
        if ((func_800A2C34(actor) << 16) != 0) {
            if ((func_8009A180(actor, ((EntityRec *)((u8 *)D_800814A8))->unk_58 + 0x20) << 16) != 0) {
                return;
            }
        }
        func_800A9A0C(actor);
        func_800A9A04(actor);
        if (((S_8016D0FC_3 *)actor)->unk_25 == 0) {
            return;
        }
        kind = ((S_8016D0FC_0 *)context)->unk_AC;
        if (kind == 0xE) {
            goto set_ad0;
        }
        if (kind < 0xF) {
kind_lt_15:
            if (kind == 0xD) {
                goto set_ad0;
            }
            goto increment_counter;
        }
kind_ge_15:
        if (kind != 0xF) {
            goto increment_counter;
        }
set_ad0:
        (*(u8 * *)((u8 *)object + 0x2C)) = D_80173AD0;
        direction_index = (gameWork.view.viewAngle + ((S_8016D0FC_3 *)actor)->unk_2A + 0x100) >> 9;
        func_80047784(object, D_80173AD0[direction_index & 7], 0);
increment_counter:
        current_table = ((u16)dungeonStatus.unk_0A);
        current_table++;
        dungeonStatus.unk_0A = current_table;
        ((S_8016D0FC_0 *)context)->unk_9B++;
        return;
    case 2:
        if (((S_8016D0FC_1 *)object)->unk_14 & 0xE000) {
            current_table = ((u16)dungeonStatus.unk_0A);
            current_table--;
            dungeonStatus.unk_0A = current_table;
            ((S_8016D0FC_0 *)context)->unk_8C = D_8016A36C;
        }
        return;
    }
}
