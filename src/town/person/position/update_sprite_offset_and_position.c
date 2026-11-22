#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "town/person/position.h"
#include "town/map/variant_data.h"

/* The linked child carries the frame flags and the adjusted coordinates. */
typedef struct SpriteOffsetChild {
    u8 pad_00[8];
    u32 frame_flags;
    u8 pad_0c[4];
    s16 x;
    s16 y;
} SpriteOffsetChild;

#define NULL 0

extern void install_object_handler_and_clear_slot_flag(); /* K&R: retail passes three arguments to this one-parameter function */


/* Update the sprite position using frame offsets, save the object position, and apply the update. */
void update_sprite_offset_and_position(TownObjectRecord *object, ObjectPosition *position, struct SpriteFrameState *sprite_arg)
{
    SpriteOffsetChild *frame_source;
    SpriteOffsetChild *coordinate_target;
    u32 flags;
    s32 x_offset;
    s32 y_offset;

    object_index_slots[object->slot].unk_00 = 0;
    frame_source = (SpriteOffsetChild *)object->unk_98;
    if (frame_source != NULL && ((flags = frame_source->frame_flags) & 0xC0000000) == 0xC0000000) {
        u32 table_select = (flags >> 23) & 1;
        u32 frame_index = (flags >> 24) & 0x3F;

        TownRectangle *rectangle;

        if (table_select == 0) {
            rectangle = &town_building_records[frame_index].position_entry;
        } else {
            rectangle = &town_map_variants[frame_index].position_entry;
        }
        x_offset = rectangle->origin_x + (u16)rectangle->x_offset;
        y_offset = rectangle->origin_y + (u16)rectangle->y_offset;
    } else {
        y_offset = x_offset = 0;
    }
    if (frame_source != NULL) {
        /* The routine reads the child link again for each coordinate store. */
        coordinate_target = (SpriteOffsetChild *)object->unk_98;
        coordinate_target->x = object->target_x - x_offset;
        coordinate_target = (SpriteOffsetChild *)object->unk_98;
        coordinate_target->y = object->target_y - y_offset;
    }
    object->unk_84 = object->target_x;
    object->unk_86 = object->target_y;
    install_object_handler_and_clear_slot_flag(object, position, sprite_arg);
}
