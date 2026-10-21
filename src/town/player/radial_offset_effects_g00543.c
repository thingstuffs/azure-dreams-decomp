/* Create randomized radial offset effects (G00543). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009A1CC. */
#include "town/player/radial_offset_effects_g00543.h"

/* Creates an offset effect with randomized motion and initializes its appearance. */
void *create_randomized_offset_effect(S_8009792C_2 *source, u32 angle) {
    u32 direction;
    SpriteFrameState *appearance;
    S_8009792C_1 *motion;
    void *effect;
    s16 *effect_params;

    angle >>= 9;
    direction = angle & 7;
    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        effect_params = (s16 *)((s8 *)effect + 0x20);
        motion = ((S_8009792C_0 *)effect)->unk_08;
        appearance = ((S_8009792C_0 *)effect)->unk_0C;
        ((S_8009792C_0 *)effect)->unk_10 = (s32 *)&D_800ABB20;
        register_node(effect, project_sprite_chain);
        motion->unk_02 = source->unk_02 - dir_step_x[direction] * 0x10;
        motion->unk_06 = source->unk_06 - dir_step_y[direction] * 0x10;
        motion->unk_0A = source->unk_0A;
        motion->unk_0C = -(source->unk_0C * ((rand() & 1) + 2)) / 16;
        motion->unk_10 = -(source->unk_10 * ((rand() & 1) + 2)) / 16;
        motion->unk_14 = (~rand() & 1) << 0xF;
        select_record_entry_and_value(appearance, &D_800D1464, 0);
        appearance->color.c.b = 0xFF;
        appearance->color.c.g = 0xFF;
        appearance->color.c.r = 0xFF;
        appearance->scale_y = 0x1000;
        appearance->scale_x = 0x1000;
        appearance->tpage_abr = 0x60;
        appearance->flags |= 0xC;
        effect_params[1] = scale_random_to_unsigned_halfword_limit(7) + scale_random_to_unsigned_halfword_limit(7);
    }
    return effect;
}

/* Spawn objects at randomized positions around an origin with evenly spaced angles. */
void spawn_radial_objects(MovingPosition *origin, S_80097AD0_1 *spread, s32 count) {
    StackRecord record;
    s32 angle;
    s32 angle_step;
    s32 first_trig_value;
    s32 object_index;
    s32 angle_component;
    s32 y;
    u16 initial_y;
    ObjectPayloadView *object;

    if (count != 0) {
        angle_step = 0x1000 / count;
        angle = rand();
        initial_y = origin->unk_0A;
        record.field16 = -4;
        record.y = initial_y;
        for (object_index = 0; object_index < count; object_index++) {
            record.x = (origin->unk_02 +
                        scale_random_to_unsigned_halfword_limit(spread->unk_00.u16)) -
                       (spread->unk_00.s32 / 2);
            record.z = (origin->unk_06 +
                        scale_random_to_unsigned_halfword_limit(spread->unk_04.u16)) -
                       (spread->unk_04.s32 / 2);
            y = (origin->unk_0A -
                 scale_random_to_unsigned_halfword_limit(spread->unk_08.u16)) -
                (spread->unk_08.s32 / 2);
            record.y = y;
            record.fieldC = func_80064584(angle) << 5;
            first_trig_value = func_800644B8(angle);
            {
                void *record_ptr = &record;
                first_trig_value <<= 5;
                record.field10 = first_trig_value;
                object = create_randomized_offset_effect((S_8009792C_2 *)record_ptr, (u32)(s16)angle);
            }
            if (object != 0) {
                angle_component = func_800644B8(angle) << 5;
                if (angle_component < 0) {
                    angle_component = -angle_component;
                }
                ((S_80097AD0_3 *)(object->unk_08))->unk_14 = -angle_component;
            }
            angle += angle_step;
        }
    }
}
