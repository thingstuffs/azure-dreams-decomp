#include "dungeon/effect/motion/decrement_effect_counter_by_twelve.h"


void decrement_effect_counter_by_twelve(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 50);
    D_800259AC = 1;
    counter -= 12;
    *(u16 *)(object_bytes + 50) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}

void create_random_offset_effect_object(
    EntityRec *source, s16 field_14_value, void *payload, s16 field_32_value,
    s16 x_offset, s16 y_offset, s16 z_offset)
{
    s16 held_x_offset = x_offset;
    s16 held_y_offset = y_offset;
    s16 held_z_offset = z_offset;
    void *object;
    Row_818F33BC_S_80024BBC_5 *state;

    object = allocate_list_node(0x211, source);
    if (object != NULL) {
        s32 x_jitter;
        s32 y_jitter;
        s32 z_jitter;
        s32 x_pos;
        s32 y_pos;
        s32 z_pos;
        Row_818F33BC_S_80024BBC_2 *x_dest;
        Row_818F33BC_S_80024BBC_3 *y_dest;
        Row_818F33BC_S_80024BBC_4 *z_dest;

        ((Row_818F33BC_S_80024BBC_0 *)object)->unk_10 = decrement_effect_counter_by_twelve;

        x_jitter = rand() & 0x1F;
        x_pos = ((Row_818F33BC_S_80024BBC_6 *)((*(void * *)&source->z)))->unk_02;
        x_dest = ((Row_818F33BC_S_80024BBC_0 *)object)->unk_08;
        x_pos += x_jitter;
        x_dest->unk_02 = (s16)x_pos + (s16)(held_x_offset - 0x10);
        y_jitter = rand() & 0x1F;
        y_pos = ((Row_818F33BC_S_80024BBC_6 *)((*(void * *)&source->z)))->unk_06;
        y_dest = ((Row_818F33BC_S_80024BBC_0 *)object)->unk_08;
        y_pos += y_jitter;
        y_dest->unk_06 = (s16)y_pos + (s16)(held_y_offset - 0x10);

        state = (u8 *)object + 0x20;
        z_jitter = rand() & 0x1F;
        z_pos = ((Row_818F33BC_S_80024BBC_6 *)((*(void * *)&source->z)))->unk_0A;
        z_dest = ((Row_818F33BC_S_80024BBC_0 *)object)->unk_08;
        z_pos += z_jitter;
        z_dest->unk_0A = (s16)z_pos + (s16)(held_z_offset - 0x10);
        state->unk_14 = field_14_value;
        state->unk_32 = field_32_value;
        register_node(object, draw_linked_shaded_tiles);
        state->unk_50 = -0x2000;
        state->unk_08 = payload;
    }
}

