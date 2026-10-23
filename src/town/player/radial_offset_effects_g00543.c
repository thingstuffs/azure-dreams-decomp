/* Create randomized radial offset effects (G00543). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_8009A1CC. */
#include "town/player/radial_offset_effects_g00543.h"
#include "shared/entity.h"
#include "shared/object_node.h"

/* Creates an offset effect with randomized motion and initializes its appearance. */
void *create_randomized_offset_effect(S_8009792C_2 *source, u32 angle) {
    u32 direction;
    SpriteFrameState *appearance;
    ObjectPosition *motion;
    ObjectNodeHeader *effect;
    s16 *effect_params;

    angle >>= 9;
    direction = angle & 7;
    effect = allocate_flagged_object_node(0x212);
    if (effect != NULL) {
        effect_params = (s16 *)((s8 *)effect + 0x20);
        motion = effect->position;
        appearance = effect->sprite;
        effect->update_callback = (s32 *)&D_800ABB20;
        register_node(effect, project_sprite_chain);
        motion->x.w.i = source->unk_02 - dir_step_x[direction] * 0x10;
        motion->y.w.i = source->unk_06 - dir_step_y[direction] * 0x10;
        motion->z.w.i = source->unk_0A;
        motion->velocity_x = -(source->unk_0C * ((rand() & 1) + 2)) / 16;
        motion->velocity_y = -(source->unk_10 * ((rand() & 1) + 2)) / 16;
        motion->velocity_z = (~rand() & 1) << 0xF;
        select_record_entry_and_value(appearance, &radial_sprite_entries, 0);
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
        initial_y = origin->z;
        record.field16 = -4;
        record.y = initial_y;
        for (object_index = 0; object_index < count; object_index++) {
            record.x = (origin->x +
                        scale_random_to_unsigned_halfword_limit(spread->unk_00.u16)) -
                       (spread->unk_00.s32 / 2);
            record.z = (origin->y +
                        scale_random_to_unsigned_halfword_limit(spread->unk_04.u16)) -
                       (spread->unk_04.s32 / 2);
            y = (origin->z -
                 scale_random_to_unsigned_halfword_limit(spread->unk_08.u16)) -
                (spread->unk_08.s32 / 2);
            record.y = y;
            record.fieldC = rcos(angle) << 5;
            first_trig_value = rsin(angle);
            {
                void *record_ptr = &record;
                first_trig_value <<= 5;
                record.field10 = first_trig_value;
                object = create_randomized_offset_effect((S_8009792C_2 *)record_ptr, (u32)(s16)angle);
            }
            if (object != 0) {
                angle_component = rsin(angle) << 5;
                if (angle_component < 0) {
                    angle_component = -angle_component;
                }
                ((ObjectPosition *)object->unk_08)->velocity_z = -angle_component;
            }
            angle += angle_step;
        }
    }
}
