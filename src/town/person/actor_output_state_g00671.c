/* actor output state. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CAA34. */
#include "town/person/actor_output_state_g00671.h"
#include "town/person.h"

/* Set the object value to its base plus the source value minus 76. */
void set_object_z_from_lookup(Rec_func_800AB030_arg0 *source, ObjectPosition *object) {
    s32 value_offset;
    s32 base_value;

    base_value = query_lowered_transform_position(object);
    value_offset = advance_person_sine_offset(source);
    value_offset -= 0x4C;
    object->z.w.i = (s16) (base_value + value_offset);
}

/* Update the output, adding eight while the state's countdown is positive. */
void raise_object_while_counter_runs(Rec_func_800AB030_arg0 *state, ObjectPosition *output) {
    set_object_z_from_lookup(state, output);
    if ((s16)state->unk_6C > 0) {
        output->y.unsigned_parts.integer = (u16) (output->y.unsigned_parts.integer + 8);
        state->unk_6C = (s16) ((u16) state->unk_6C - 1);
    }
}
