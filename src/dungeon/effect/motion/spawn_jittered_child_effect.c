#include "shared/entity.h"
#include "dungeon/effect/motion/spawn_jittered_child_effect.h"
#include "dungeon/effect/motion.h"
#include "shared/object_node.h"


/* Creates a child effect at a random offset from its source and stores the supplied control values. */
void spawn_jittered_child_effect(
    void *source,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z)
{
    Row_818FECCC_S_818FECCC_1 *source_obj = source;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    ObjectNodeHeader *object_cursor;
    Row_818FECCC_S_818FECCC_0 *fields;
    s32 jitter_x;
    s32 jitter_y;
    s32 jitter_z;
    s16 bias_x;
    s16 bias_y;
    s16 bias_z;
    s16 position_x;
    s16 position_y;
    s16 position_z;
    void *init_data;
    ObjectPosition *dest_x;
    ObjectPosition *dest_y;
    ObjectPosition *dest_z;

    object_cursor = allocate_list_node(0x211, source_obj);
    if (object_cursor != NULL) {
        object_cursor->update_callback = D_80024400;
        jitter_x = rand() & 0x1F;
        position_x = ((Row_818FECCC_S_818FECCC_6 *)(source_obj->unk_08))->unk_02;
        dest_x = object_cursor->position;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = (s16)position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((Row_818FECCC_S_818FECCC_6 *)(source_obj->unk_08))->unk_06;
        dest_y = object_cursor->position;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = (s16)position_y;

        jitter_z = rand();
        init_data = &D_800241B0;
        jitter_z &= 0x1F;
        position_z = ((Row_818FECCC_S_818FECCC_6 *)(source_obj->unk_08))->unk_0A;
        fields = (Row_818FECCC_S_818FECCC_0 *)((u8 *)object_cursor + 0x20);
        dest_z = object_cursor->position;
        position_z += jitter_z;
        bias_z = offset_z + 0x10;
        position_z += bias_z;
        dest_z->z.w.i = (s16)position_z;
        fields->unk_14 = field_34;
        fields->unk_32 = saved_field_52;
        register_node(object_cursor, init_data);
        fields->unk_08.u = saved_field_28;
    }
}
