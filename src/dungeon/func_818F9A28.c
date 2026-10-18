#include "shared/dungeon_effect_views.h"
#include "modules/dungeon_ovl_1918800.h"
#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/entity.h"
#include "shared/object_node.h"

/* Retail 818F9A28 (create_random_jitter_child): spawn an effect object under the parent node, placed at the parent's
 * position plus a random jitter (0..31 per axis) and the given offsets (minus half the jitter range). */
void create_random_jitter_child(
    ObjectNodeHeader *parent,
    s16 field_34,
    s32 field_28,
    s16 field_52,
    s16 offset_x,
    s16 offset_y,
    s16 offset_z)
{
    ObjectNodeHeader *source_obj = parent;
    u32 saved_field_28 = field_28;
    s16 saved_field_52 = field_52;
    ObjectNodeHeader *spawned;
    PointRecord *fields;
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
    EntityRec *dest_x;
    EntityRec *dest_y;
    EntityRec *dest_z;

    /* the parent's next slot is the list head the new node links behind */
    spawned = func_8003FD64(0x211, (ObjectNodeHeader **)source_obj);
    if (spawned != 0) {
        spawned->unk_10 = (void *)raise_entity_to_ground;
        jitter_x = rand() & 0x1F;
        position_x = ((EntityRec *)source_obj->unk_08)->x.w.i;
        dest_x = spawned->unk_08;
        position_x += jitter_x;
        bias_x = offset_x - 0x10;
        position_x += bias_x;
        dest_x->x.w.i = position_x;

        jitter_y = rand() & 0x1F;
        position_y = ((EntityRec *)source_obj->unk_08)->y.w.i;
        dest_y = spawned->unk_08;
        position_y += jitter_y;
        bias_y = offset_y - 0x10;
        position_y += bias_y;
        dest_y->y.w.i = position_y;

        jitter_z = rand();
        init_data = draw_linked_brightness_points;
        jitter_z &= 0x1F;
        position_z = ((EntityRec *)source_obj->unk_08)->z.w.i;
        fields = (PointRecord *)(spawned + 1);
        dest_z = spawned->unk_08;
        position_z += jitter_z;
        bias_z = offset_z - 0x10;
        position_z += bias_z;
        dest_z->z.w.i = position_z;
        fields->unk_14 = field_34;
        fields->brightness = saved_field_52;
        func_8004491C(spawned, (s32)init_data);
        fields->color = saved_field_28;
    }
}

