#include "common.h"
#include "shared/object_index_slots.h"
#include "town/person/position.h"
#include "town/map/variant_data.h"

typedef struct S_800C4AEC_0 {
    u8 pad_00[0x60];
    s32 unk_60;
    u8 pad_64[0x20];
    u16 unk_84;
    u16 unk_86;
    u16 unk_88;
    u16 unk_8A;
    u8 pad_8C[0xC];
    void * unk_98;
} S_800C4AEC_0;

typedef struct S_800C4AEC_1 {
    u8 pad_00[0x8];
    u32 unk_08;
} S_800C4AEC_1;

typedef struct S_800C4AEC_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    s16 unk_12;
} S_800C4AEC_2;   /* store_ptr in update_sprite_offset_and_position */


#define NULL 0

extern void install_object_handler_and_clear_slot_flag(void *, s32, s32);


/* Update the sprite position using frame offsets, save the object position, and apply the update. */
void update_sprite_offset_and_position(void *object_arg, s32 update_arg, s32 setup_context)
{
    S_800C4AEC_0 *object = object_arg;
    S_800C4AEC_1 *sprite;
    u32 flags;
    s32 x_offset;
    s32 y_offset;

    *(((u8 *)object_index_slots) + object->unk_60 * 8) = 0;
    sprite = object->unk_98;
    if (sprite != NULL && ((flags = sprite->unk_08) & 0xC0000000) == 0xC0000000) {
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
    if (sprite != NULL) {
        ((S_800C4AEC_2 *)object->unk_98)->unk_10 = object->unk_88 - x_offset;
        ((S_800C4AEC_2 *)object->unk_98)->unk_12 = object->unk_8A - y_offset;
    }
    object->unk_84 = object->unk_88;
    object->unk_86 = object->unk_8A;
    install_object_handler_and_clear_slot_flag(object, update_arg, setup_context);
}
