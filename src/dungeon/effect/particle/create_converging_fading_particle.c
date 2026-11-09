/* row func_8132E2FC, true base 0x801652FC -- exemplar-seeded from landed
 * func_80BC1528 (MATCH @2.7.2-cdk-G0, gate_verified). Opcode-sequence
 * similarity 0.9843. Ordinary code: no symbol alias, no .text section
 * attribute, no literal word arrays, first word is the prologue.
 *
 * Adaptation measured off the retail stream:
 *   - one fewer parameter (exemplar's arg2 is gone; the value stored at
 *     obj+0x20 / tail+8 is arg1 here), so every later arg shifts one slot
 *   - `((S_801652FC_0 *)tail)->unk_14 = arg1` is absent
 *   - the six vector fields sit 0xC higher (0x36->0x42 ... 0x54->0x60)
 *   - the z bias is -40, not -100
 *   - the two overlay data symbols are this image's
 */
#include "common.h"
#include "engine/node/registration.h"
#include "dungeon/effect/particle.h"
#include "shared/object_node.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/data.h"
#include "dungeon/effect/particle/converging_fade.h"

extern void *allocate_list_node(s32, void *);

/* Creates an offset object and initializes its source position and motion parameters. */
void create_converging_fading_particle(
    void *source, s32 initial_value, s32 duration, s32 offset_x,
    s32 offset_y, s32 offset_z)
{
    ObjectNodeHeader *source_obj = source;
    s32 saved_offset_x = offset_x;
    s32 saved_offset_y = offset_y;
    s32 saved_offset_z = offset_z;
    ObjectNodeHeader *object;
    ConvergingFadeBody *state;
    s32 calculation;
    s32 quotient_x;
    s32 quotient_y;
    s32 quotient_z;
    s32 rounded_x;
    s32 rounded_z;

    object = allocate_list_node(0x211, source_obj);
    if (object != 0) {
        object->update_callback = update_converging_fading_particle;

        object->position->x.w.i =
            source_obj->position->x.unsigned_parts.integer + saved_offset_x;
        object->position->y.w.i =
            source_obj->position->y.unsigned_parts.integer + saved_offset_y;
        object->position->z.w.i =
            source_obj->position->z.unsigned_parts.integer + saved_offset_z - 40;

        state = NODE_BODY(object);
        state->target_x = source_obj->position->x.unsigned_parts.integer;
        state->target_y = source_obj->position->y.unsigned_parts.integer;
        state->target_z = source_obj->position->z.unsigned_parts.integer;

        quotient_x = -(saved_offset_x << 16) / ((s16)duration / 8);
        calculation = quotient_x / 2;
        state->velocity_x = calculation;
        calculation = -(saved_offset_y << 16);
        quotient_y = calculation / ((s16)duration / 8);
        calculation = quotient_y / 2;
        state->velocity_y = calculation;
        calculation = -(saved_offset_z << 16);
        quotient_z = calculation / ((s16)duration / 8);
        rounded_x = quotient_z / 2;
        state->velocity_z = rounded_x;

        rounded_x = quotient_x;
        if (rounded_x < 0) {
            rounded_x += 3;
        }
        state->acceleration_x = rounded_x >> 2;

        rounded_z = quotient_y;
        if (rounded_z < 0) {
            rounded_z += 3;
        }
        state->acceleration_y = rounded_z >> 2;

        rounded_z = quotient_z;
        state->acceleration_z = (rounded_z / 4);

        state->fade_level = duration;
        register_node(object, child_particle_draw_address);
        rounded_x = initial_value;
        state->base_color.word = rounded_x;
        state->draw_color = initial_value;
    }

}
