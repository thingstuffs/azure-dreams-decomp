#include "shared/entity.h"
/* Jittered shaded particle creation and countdown-based removal. */
#include "shared/object_node.h"
#include "dungeon/effect/motion/decrement_effect_counter_by_twelve.h"
#include "shared/object_flags.h"


/*
 * Sets D_800259AC, subtracts twelve from the signed 16-bit counter at offset 0x32, and flags
 * removal at zero or below.
 */
void decrement_effect_counter_by_twelve(void *object)
{
    u8 *object_bytes = object;
    u16 counter;

    counter = *(u16 *)(object_bytes + 50);
    D_800259AC = 1;
    counter -= 12;
    *(u16 *)(object_bytes + 50) = counter;
    if ((counter << 16) <= 0) {
        *(u16 *)(object_bytes - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}

/* Creates a shaded particle at a jittered source offset and stores the supplied countdown and
   rendering values. */
void create_random_offset_effect_object(
    EntityRec *source, s16 field_14_value, void *payload, s16 field_32_value,
    s16 x_offset, s16 y_offset, s16 z_offset)
{
    s16 held_x_offset = x_offset;
    s16 held_y_offset = y_offset;
    s16 held_z_offset = z_offset;
    ObjectNodeHeader *object;
    Row_818F33BC_S_80024BBC_5 *state;

    object = allocate_list_node(0x211, source);
    if (object != NULL) {
        s32 x_jitter;
        s32 y_jitter;
        s32 z_jitter;
        s32 x_pos;
        s32 y_pos;
        s32 z_pos;
        ObjectPosition *x_dest;
        ObjectPosition *y_dest;
        ObjectPosition *z_dest;

        object->update_callback = decrement_effect_counter_by_twelve;

        x_jitter = rand() & 0x1F;
        x_pos = ((Row_818F33BC_S_80024BBC_6 *)((*(void * *)&source->z)))->unk_02;
        x_dest = object->position;
        x_pos += x_jitter;
        x_dest->x.w.i = (s16)x_pos + (s16)(held_x_offset - 0x10);
        y_jitter = rand() & 0x1F;
        y_pos = ((Row_818F33BC_S_80024BBC_6 *)((*(void * *)&source->z)))->unk_06;
        y_dest = object->position;
        y_pos += y_jitter;
        y_dest->y.w.i = (s16)y_pos + (s16)(held_y_offset - 0x10);

        state = (u8 *)object + 0x20;
        z_jitter = rand() & 0x1F;
        z_pos = ((Row_818F33BC_S_80024BBC_6 *)((*(void * *)&source->z)))->unk_0A;
        z_dest = object->position;
        z_pos += z_jitter;
        z_dest->z.w.i = (s16)z_pos + (s16)(held_z_offset - 0x10);
        state->unk_14 = field_14_value;
        state->unk_32 = field_32_value;
        register_node(object, draw_linked_shaded_tiles);
        state->unk_50 = -0x2000;
        state->unk_08 = payload;
    }
}

