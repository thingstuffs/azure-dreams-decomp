#include "common.h"
#include "engine/node/registration.h"
#include "shared/object_index_slots.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "shared/object_links.h"
#include "shared/object_node.h"
#include "shared/town_object.h"
#include "town/menu/position_callbacks_api.h"
#include "shared/position_views.h"
#include "sdk/libgte.h"
#include "town/menu.h"


typedef struct {
    s32 unused;
    void *record;
} D_80082660_entry;


typedef struct S_func_800AA760_0 {
    u8 pad_00[0x60];
    u8 unk_60;
    u8 pad_61[0x37];
    s8 *unk_98;
} S_func_800AA760_0;


/* Updates the linked position, or clears the object flag and sets cleanup bits. */
void follow_linked_position_or_retire(S_func_800AA760_0 *object, ObjectPosition *out_position)
{
    s32 x_offset;
    s32 y_offset;
    s8 *object_flag;
    u8 link_id;
    u8 link_index;
    ObjectNodeHeader *linked_record;
    TownObjectRecord *linked_entity;
    ObjectPosition *linked_position;

    link_id = object->unk_60;
    link_index = link_id & 0xFF;
    if (classify_object_against_bounds(object, out_position) != 0) {
        object_flag = object->unk_98;
        if (object_flag != 0) {
            *object_flag = 0;
        }
        unlink_node_if_registered(object);
        NODE_HEADER(object)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }

    if (link_index != 0) {
        linked_record = object_index_slots[link_index].object;
        linked_entity = NODE_BODY(linked_record);
        if (linked_record != 0) {
            linked_position = linked_record->position;
            x_offset = rsin(linked_entity->heading);
            out_position->x.w.i =
                linked_position->x.w.i + (x_offset / 256);

            y_offset = rcos(linked_entity->heading);
            out_position->y.w.i =
                linked_position->y.w.i + (y_offset / 256);
            out_position->z.w.i = linked_position->z.w.i - 0x20;
        }
    }
}
