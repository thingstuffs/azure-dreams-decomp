#include "common.h"

typedef struct S_8008E504_0 {
    u8 pad_00[0x8C];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x6];
    u16 unk_A2;
    u8 pad_A4[0x80];
    void * unk_124;
} S_8008E504_0;   /* arg0 in func_8008E504 */

typedef struct S_8008E504_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8008E504_1;   /* arg1 in func_8008E504 */

typedef struct S_8008E504_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
    s16 unk_8A;
} S_8008E504_2;   /* arg3 in func_8008E504 */

typedef struct S_8008E504_3 {
    u8 pad_00[0x1C];
    volatile s32 unk_1C;
} S_8008E504_3;   /* temp_a0 in func_8008E504 */

typedef struct S_8008E504_4 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0x16];
    u8 * unk_2C;
} S_8008E504_4;   /* arg2 in func_8008E504 */



extern volatile s32 D_80081484;
extern s32 D_800E3540;
extern u8 D_8008ACDC[];
extern u8 D_8008EAC8[];
extern u8 D_800DD058[];
extern s16 D_80083228[5];

extern void func_800419EC(s32, s32);
extern void func_80048A44(void *, u8, s32, s32);
extern s32 func_80094EA4(void);

/* Advances an actor's timed animation state and selects its next behavior. */
void func_8008E504(S_8008E504_0 *actor, S_8008E504_1 *action, S_8008E504_4 *sprite, S_8008E504_2 *entity) {
    u16 state_or_ticks;
    u16 sprite_flags;
    s32 state;
    s32 saved_status;
    s32 entity_flags;
    s32 object_flags;
    S_8008E504_3 *linked_object;

    state = actor->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto state_two_check;
    }
    if (state == 0) {
        goto state_zero;
    }
    goto done;

state_two_check:
    state_or_ticks = 2;
    if (state == state_or_ticks) {
        goto state_two_body;
    }
    goto done;

state_zero:
    if (!(actor->unk_A2 & 0x10)) {
        goto done;
    }
    action->unk_14 = 0;
    if ((entity->unk_88 - entity->unk_8A) < 0x41) {
        goto state_zero_short;
    }
    func_800419EC(8, 0x10);
    if (entity->unk_1C & 0x100000) {
        linked_object = actor->unk_124;
        saved_status = D_80081484;
        object_flags = linked_object->unk_1C;
        D_80081484 = 0;
        linked_object->unk_1C = object_flags & 0xFFF7FFFF;
        entity_flags = entity->unk_1C;
        D_800E3540 = saved_status;
        entity->unk_1C = entity_flags & 0xFFEFFFFF;
    }
    state_or_ticks = 0xC;
    actor->unk_96 = state_or_ticks;
    goto increment_state;

state_zero_short:
    actor->unk_96 = 1U;

increment_state:
    actor->unk_9B = (u8)(actor->unk_9B + 1);

state_one:
    if (entity->unk_1C & 0x100000) {
        actor->unk_8C = D_8008EAC8;
        goto done;
    }
    sprite->unk_2C = D_800DD058;
    func_80048A44(sprite,
        D_800DD058[((D_80083228[0] + entity->unk_2A + 0x100) >> 9) & 7],
        0, 1);
    sprite->unk_14 = (u16)(sprite->unk_14 | 0x800);
    actor->unk_9B = (u8)(actor->unk_9B + 1);
    goto done;

state_two_body:
    state_or_ticks = actor->unk_96 - 1;
    actor->unk_96 = state_or_ticks;
    if ((state_or_ticks << 0x10) > 0) {
        goto done;
    }
    sprite_flags = sprite->unk_14;
    sprite->unk_14 = (u16)(sprite_flags & 0xF7FF);
    if ((sprite_flags & 0xE000) != 0 || ((func_80094EA4() << 0x10) != 0)) {
        goto assign_dispatch;
    }
    goto done;

assign_dispatch:
    actor->unk_8C = D_8008ACDC;

done:
    return;
}
