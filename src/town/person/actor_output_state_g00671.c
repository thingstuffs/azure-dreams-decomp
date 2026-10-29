/* G00671: actor output state. */
/* Original-file evidence (G00671): inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800CAA34. */
#include "town/person/actor_output_state_g00671.h"
#include "town/person.h"

/* Set the object value to its base plus the source value minus 76. */
void set_object_value_base_plus(Rec_func_800AB030_arg0 *source, EntityRec *object) {
    s32 value_offset;
    s32 base_value;

    base_value = query_lowered_transform_position(object);
    value_offset = advance_person_lookup_value(source);
    value_offset -= 0x4C;
    object->z.w.i = (s16) (base_value + value_offset);
}

/* Update the output, adding eight while the state's countdown is positive. */
void update_output_adding_eight_state(Rec_func_800AB030_arg0 *state, S_800C81E4_1 *output) {
    set_object_value_base_plus(state, (EntityRec *)output);
    if ((s16)state->unk_6C > 0) {
        output->unk_06 = (u16) (output->unk_06 + 8);
        state->unk_6C = (s16) ((u16) state->unk_6C - 1);
    }
}
