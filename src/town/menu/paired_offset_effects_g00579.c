/* Accumulates an effect value and creates a pair of objects with offset positions. */
/* inferred-strong G00579: paired_offset_effects_g00579; joins CL:town/func_800A97E8; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A97E8. */
#include "town/menu/paired_offset_effects_g00579.h"

/* Increases the step by four, adds it to a capped value, and creates paired effects when it reaches 0x400. */
void accumulate_effect_step(void *updateState, s32 unused1, s32 unused2, void *accumulatorState) {
    u16 step;
    u16 accumulatedValue;

    step = *(u16 *) ((u8 *) updateState + 0x90) + 4;
    *(u16 *) ((u8 *) updateState + 0x90) = step;
    accumulatedValue = *(u16 *) ((u8 *) accumulatorState + 0x16) + step;
    *(u16 *) ((u8 *) accumulatorState + 0x16) = accumulatedValue;
    if (accumulatedValue >= 0x400) {
        accumulatedValue = 0x400;
        *(u16 *) ((u8 *) accumulatorState + 0x16) = accumulatedValue;
    }
    if (*(u16 *) ((u8 *) accumulatorState + 0x16) == 0x400) {
        create_paired_offset_effects((S_800A6F48_10 *)updateState, (S_800A6F48_0 *)updateState,
            (IntVector3 *)unused2, (S_800A6F48_11 *)accumulatorState);
    }
}

/* Creates two offset objects, adjusts their components, and initializes the owner and color. */
void create_paired_offset_effects(S_800A6F48_10 *owner, S_800A6F48_0 *spawn_state, IntVector3 *origin, S_800A6F48_11 *color) {
    s32 position[5];
    s32 *offset_data;
    s32 *second_offset_data;
    s32 y_component;
    s32 z_component;
    u32 offset_sum;
    S_800A6F48_4 *first_object;
    S_800A6F48_5 *first_y_data;
    S_800A6F48_6 *first_z_data;
    S_800A6F48_9 *second_y_data;

    spawn_state->unk_0C = &D_800D0DD8;
    offset_sum = ((S_800A6F48_1 *)(&D_800D0DD8))->unk_04 + ((S_800A6F48_1 *)(&D_800D0DD8))->unk_10;
    position[0] = origin->x + ((s32) (offset_sum + (offset_sum >> 0x1F)) >> 1);
    offset_data = spawn_state->unk_0C;
    position[1] = origin->y + ((S_800A6F48_3 *)offset_data)->unk_04 + ((S_800A6F48_3 *)offset_data)->unk_10;
    position[2] = origin->z;
    first_object = create_preset_sprite_object(position);
    ((S_800A6F48_14 *)(((ObjectPayloadView *)first_object)->unk_08))->unk_0C = 0x10000;
    first_y_data = first_object->unk_08;
    y_component = first_y_data->unk_10;
    first_y_data->unk_10 = (s32) (y_component / 4);
    first_z_data = first_object->unk_08;
    z_component = first_z_data->unk_14;
    first_z_data->unk_14 = (s32) (z_component / 4);
    first_object->unk_B0 = 0;
    spawn_person_radial_effects(position);
    second_offset_data = spawn_state->unk_0C;
    position[0] = origin->x - ((((S_800A6F48_7 *)second_offset_data)->unk_04
        + ((S_800A6F48_7 *)second_offset_data)->unk_10) / 3);
    first_object = create_preset_sprite_object(position);
    ((S_800A6F48_15 *)(((ObjectPayloadView *)first_object)->unk_08))->unk_0C = -0x8000;
    second_y_data = first_object->unk_08;
    second_y_data->unk_10 = (s32) (second_y_data->unk_10 / 3);
    first_object->unk_B0 = 0;
    spawn_person_radial_effects(position);
    owner->unk_50 = &D_800A70EC;
    owner->unk_6C = 0xA;
    color->unk_0E = 0x80;
    color->unk_0D = 0x80;
    color->unk_0C = 0x80;
}
