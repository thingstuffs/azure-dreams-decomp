#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/u_boat.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"

typedef struct S_80170CEC_0 {
    u8 pad_00[0x2C];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    u8 pad_2E[0x8];
    union { u16 s; s16 u; } unk_36;   /* accessed as both */
    s16 unk_38;
    u8 pad_3A[0x6];
    void * unk_40;
} S_80170CEC_0;   /* arg0 in update_rotating_actor_aura */

typedef struct S_80170CEC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80170CEC_1;   /* entity_base in update_rotating_actor_aura */



typedef struct S_80170CEC_4 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x82];
    u8 unk_9A;
    u8 pad_9B[0x1A];
    u8 unk_B5;
} S_80170CEC_4;   /* entity_saved in update_rotating_actor_aura */

typedef struct S_80170CEC_5 {
    u8 pad_00[0x9A];
    u8 unk_9A;
} S_80170CEC_5;   /* entity in update_rotating_actor_aura */


typedef struct S_80170CEC_7 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80170CEC_7;   /* copy_source in update_rotating_actor_aura */


extern s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);
extern u8 uboat_ready_frames[];
extern u8 D_800E2408[];

/* Update the effect rotation, position, and fade, marking it finished when needed. */
void update_rotating_actor_aura(void *effect, ObjectPosition *position, SpriteFrameState *visual) {
    void *entity;
    void *entity_saved;
    void *source_position;
    void *entity_base;
    SpriteFrameState *record;
    u16 old_angle;
    u16 new_angle;
    u16 record_angle;
    s16 state;
    u16 state_bits;
    void *kind;

    entity = ((S_80170CEC_0 *)effect)->unk_40;
    source_position = *(void **)((u8 *)effect + 0x44);
    old_angle = visual->angle_z;
    entity_base = (u8 *)entity - 0x20;
    record = ((S_80170CEC_1 *)entity_base)->unk_0C;
    record_angle = (u16)record->depth_bias;
    new_angle = old_angle + 0x190;
    entity_saved = entity;
    visual->angle_z = new_angle;
    visual->depth_bias = record_angle;
    if (new_angle >= 0x1001) {
        visual->angle_z = old_angle - 0xE70;
    }

    state = ((S_80170CEC_0 *)effect)->unk_2C.s;
    state_bits = ((S_80170CEC_0 *)effect)->unk_2C.u;
    switch (state) {
    case 0:
    {
        u16 fade_step;
        s32 intensity;

        fade_step = ((S_80170CEC_0 *)effect)->unk_36.s + 1;
        intensity = ((s32)(s16)fade_step << 7) / ((S_80170CEC_0 *)effect)->unk_38;
        ((S_80170CEC_0 *)effect)->unk_36.s = fade_step;
        visual->color.c.r = intensity;
        visual->color.c.g = intensity;
        visual->color.c.b = intensity;
        if (((S_80170CEC_0 *)effect)->unk_36.u >= 5) {
            ((S_80170CEC_0 *)effect)->unk_2C.u++;
        }
    }
        break;
    case 1:
        if ((((S_80170CEC_4 *)entity_saved)->unk_9A == 0x19) ||
            (((S_80170CEC_4 *)entity_saved)->unk_B5 == 0)) {
            ((S_80170CEC_0 *)effect)->unk_2C.u = state_bits + 1;
            ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
            ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
        }
        if (((S_80170CEC_5 *)entity)->unk_9A == 1) {
            ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
            ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
            ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
        }
        if ((((S_80170CEC_4 *)entity_saved)->unk_14 & 0x100000) &&
            (((u8 *)dungeon_actor_ring_anchor)[0x9A] != 0x28)) {
            ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
            ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
            ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
        }
        if (((S_80170CEC_1 *)entity_base)->unk_1E & 0x8000) {
            ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
            ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
            ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
        }
        kind = record->frameTable;
        if ((kind == uboat_ready_frames) || (kind == D_800E2408)) {
            ((S_80170CEC_0 *)effect)->unk_2C.s = 3;
            ((S_80170CEC_0 *)effect)->unk_38 = 0x14;
            ((S_80170CEC_0 *)effect)->unk_36.s = 0x14;
        }
        position->x.v = ((S_80170CEC_7 *)source_position)->unk_00;
        position->y.v = ((S_80170CEC_7 *)source_position)->unk_04;
        position->z.v = ((S_80170CEC_7 *)source_position)->unk_08;
        break;
    case 3:
        position->x.v = ((S_80170CEC_7 *)source_position)->unk_00;
        position->y.v = ((S_80170CEC_7 *)source_position)->unk_04;
        position->z.v = ((S_80170CEC_7 *)source_position)->unk_08;
        visual->scale_x = record->scale_x;
        visual->scale_y = record->scale_y;
    case 2:
    {
        u16 fade_step;
        s32 intensity;

        fade_step = ((S_80170CEC_0 *)effect)->unk_36.s - 1;
        intensity = ((s32)(s16)fade_step << 7) / ((S_80170CEC_0 *)effect)->unk_38;
        ((S_80170CEC_0 *)effect)->unk_36.s = fade_step;
        visual->color.c.r = intensity;
        visual->color.c.g = intensity;
        visual->color.c.b = intensity;
        if (((S_80170CEC_0 *)effect)->unk_36.u <= 0) {
            (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            return;
        }
    }
        break;
    }

    if ((get_entity_effect_value(entity_saved, STATUS_FROG) << 16) == 0) {
        return;
    }

    (*(u16 *)((u8 *)effect + -2)) |= NODE_REMOVE;
    object_flag_block.flags |= OBJECT_REMOVE_PENDING;
}
