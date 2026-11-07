#include "dungeon/monster/u_boat_frames.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "dungeon/monster/u_boat.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "engine/entity.h"

typedef struct S_80170CEC_1 {
    u8 pad_00[0xC];
    void * unk_0C;
    u8 pad_10[0xE];
    u16 unk_1E;
} S_80170CEC_1;   /* entity_base in update_rotating_actor_aura */







extern u8 D_800E2408[];

/* Update the effect rotation, position, and fade, marking it finished when needed. */
void update_rotating_actor_aura(UBoatAuraEffectBody *effect, ObjectPosition *position, SpriteFrameState *visual) {
    ActorRecord *entity;
    void *entity_saved;
    ObjectPosition *source_position;
    S_80170CEC_1 *entity_base;
    SpriteFrameState *record;
    u16 old_angle;
    u16 new_angle;
    u16 record_angle;
    s16 state;
    u16 state_bits;
    void *kind;

    entity = effect->owner;
    source_position = effect->source.position;
    old_angle = visual->angle_z;
    entity_base = (S_80170CEC_1 *)((u8 *)entity - 0x20);
    record = entity_base->unk_0C;
    record_angle = (u16)record->depth_bias;
    new_angle = old_angle + 0x190;
    entity_saved = entity;
    visual->angle_z = new_angle;
    visual->depth_bias = record_angle;
    if (new_angle >= 0x1001) {
        visual->angle_z = old_angle - 0xE70;
    }

    state = effect->phase.s;
    state_bits = effect->phase.u;
    switch (state) {
    case 0:
    {
        u16 fade_step;
        s32 intensity;

        fade_step = effect->ticks.s + 1;
        intensity = ((s32)(s16)fade_step << 7) / effect->duration;
        effect->ticks.s = fade_step;
        visual->color.c.r = intensity;
        visual->color.c.g = intensity;
        visual->color.c.b = intensity;
        if (effect->ticks.u >= 5) {
            effect->phase.u++;
        }
    }
        break;
    case 1:
        if ((((ActorRecord *)entity_saved)->action_id == 0x19) ||
            (((ActorRecord *)entity_saved)->unk_B4.bytes[1] == 0)) {
            effect->phase.u = state_bits + 1;
            effect->duration = 0x14;
            effect->ticks.s = 0x14;
        }
        if (entity->action_id == 1) {
            effect->phase.s = 3;
            effect->duration = 0x14;
            effect->ticks.s = 0x14;
        }
        if ((((ActorRecord *)entity_saved)->flags14 & 0x100000) &&
            (dungeon_actor_ring_anchor->action_id != 0x28)) {
            effect->phase.s = 3;
            effect->duration = 0x14;
            effect->ticks.s = 0x14;
        }
        if (entity_base->unk_1E & 0x8000) {
            effect->phase.s = 3;
            effect->duration = 0x14;
            effect->ticks.s = 0x14;
        }
        kind = record->frameTable;
        if ((kind == uboat_ready_frames) || (kind == D_800E2408)) {
            effect->phase.s = 3;
            effect->duration = 0x14;
            effect->ticks.s = 0x14;
        }
        position->x.v = source_position->x.v;
        position->y.v = source_position->y.v;
        position->z.v = source_position->z.v;
        break;
    case 3:
        position->x.v = source_position->x.v;
        position->y.v = source_position->y.v;
        position->z.v = source_position->z.v;
        visual->scale_x = record->scale_x;
        visual->scale_y = record->scale_y;
    case 2:
    {
        u16 fade_step;
        s32 intensity;

        fade_step = effect->ticks.s - 1;
        intensity = ((s32)(s16)fade_step << 7) / effect->duration;
        effect->ticks.s = fade_step;
        visual->color.c.r = intensity;
        visual->color.c.g = intensity;
        visual->color.c.b = intensity;
        if (effect->ticks.u <= 0) {
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
