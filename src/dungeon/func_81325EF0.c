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
extern u8 D_80080000[];


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

/* Advance the actor's action state, directional animation, and completion callback. */
void func_8016D6F0(S_8016D6F0_0 *actor, s32 actor_id, Rec_D_80082E80 *sprite, void *entity)
{
    S_8016D6F0_7 *reference_pos;
    register u8 *direction_table ASM_REG("$5");
    u8 *counter_base;
    u8 *flags_page;
    u8 *reference_base;
    void *action_actor;
    register u8 *counter_update ASM_REG("$2");
    s32 state;
    s32 entity_flags;
    s32 action_flag;
    s8 room_id;

    state = actor->unk_9B;
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        return;
    }

    if (state == 2) {
        goto state_two;
    }
    return;

state_zero:
    if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    direction_table = D_801746A4;
    sprite->unk_2C.as_pu8 = direction_table;
    func_80047784(
        sprite,
        direction_table[((((S_8016D6F0_2 *)D_80080000)->unk_3228 +
                ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    counter_base = D_80083460;
    ((S_8016D6F0_4 *)counter_base)->unk_0A--;
    goto advance_state;

state_one:
    if ((func_80042900(entity, 1) << 0x10) == 0) {
        goto post_actions;
    }
    if (((S_8016D6F0_2 *)D_80080000)->unk_3462 & 0x1000) {
        goto done;
    }
    if (actor->unk_B4 == 0) {
        flags_page = (u8 *)0x80010000;
        if (!(((S_8016D6F0_5 *)flags_page)->unk_3714 & 8)) {
            if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
                if (func_800AA6B4(actor, actor_id, sprite, D_801746C4) != 0) {
                    return;
                }
            }
            goto action_body;
        }
    }
    if (((Rec_D_800E3D7C *)entity)->unk_64.as_s16 != 0) {
        reference_base = (u8 *)&D_80083460;
        if (((S_8016D6F0_6 *)reference_base)->unk_10 ==
            (u32)((u8 *)entity - 0x20)) {
            ((S_8016D6F0_6 *)reference_base)->unk_10 &= 0x7FFFFFFF;
        }
    }

action_body:
    if ((func_800A2C34(entity) << 0x10) != 0) {
        goto done;
    }
    entity_flags = ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32;
    action_flag = entity_flags & 0x100;
    action_actor = actor;
    if (action_flag) {
        func_800AA258(action_actor, actor_id, sprite, entity);
        return;
    }
    if (entity_flags & 0x80000) {
        func_800AA888(action_actor, actor_id, sprite, entity);
        func_8016DAA4(actor, actor_id, sprite, entity);
        return;
    }
    if (((Rec_D_800E3D7C *)entity)->unk_6D.as_s8 == 0) {
        goto done;
    }
    if ((func_800A2C34(entity) << 0x10) != 0) {
        if ((func_8009A180(
                 entity,
                 ((S_8016D6F0_9 *)(((S_8016D6F0_2 *)D_80080000)->unk_14A8))->unk_58 + 0x20)
             << 0x10) != 0) {
            goto done;
        }
    }
    func_800A9A0C(entity);
    func_800A9A04(entity);
    if ((func_80042900(entity, 1) << 0x10) != 0) {
        reference_pos = D_80082E80;
        room_id = sprite->unk_26.as_s8;
        if ((room_id != reference_pos->unk_26) || (room_id < 0)) {
            if (func_8009FD40(reference_pos, sprite) >= 2) {
                goto second_check;
            }
        }
        if ((func_800A6D30() & 7) == 0) {
            func_80042B68(entity, 1);
        }
    }

second_check:
    if ((func_80042900(entity, 1) << 0x10) != 0) {
        goto done;
    }

post_actions:
    direction_table = D_801746AC;
    sprite->unk_2C.as_pu8 = direction_table;
    func_80047784(
        sprite,
        direction_table[((((S_8016D6F0_2 *)D_80080000)->unk_3228 +
                ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7],
        0);
    if (sprite->unk_14.at00_u16.v & 0x8000) {
        goto set_callback;
    }
    counter_update = D_80083460;
    ((S_8016D6F0_8 *)counter_update)->unk_0A++;
advance_state:
    actor->unk_9B++;
    return;

state_two:
    if (!(sprite->unk_14.at00_u16.v & 0xE000)) {
        goto done;
    }
    counter_update = D_80083460;
    ((S_8016D6F0_8 *)counter_update)->unk_0A--;

set_callback:
    actor->unk_8C = D_8016B778;

done:
    return;
}
