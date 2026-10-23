#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

void select_record_entry_and_value();
s32 register_node();
extern M2C_UNK D_80024224;
#include "shared/sprite_source.h"
extern SpriteSourceEntry D_800DE8E8[];

typedef struct S_800242A0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_800242A0_0;

   /* arg1 in allocate_effect_at_coordinates */

/* Allocate and initialize an object with the supplied value and coordinates. */
void *allocate_effect_at_coordinates(s32 object_value, MovingPosition *source_coords) {
    SpriteFrameState *sprite;
    S_800242A0_0 *object;
    MovingPosition *coords;

    object = allocate_flagged_object_node(0x212);
    if (object != NULL) {
        object->unk_10 = &D_80024224;
        sprite = object->unk_0C;
        object->unk_2C = object_value;
        sprite->color.c.b = 0x80;
        sprite->color.c.g = 0x80;
        sprite->color.c.r = 0x80;
        select_record_entry_and_value(sprite, &D_800DE8E8, 0);
        sprite->scale_y = 0x1000;
        sprite->scale_x = 0x1000;
        register_node(object, project_sprite_chain);
        coords = object->unk_08;
        coords->unk_02 = (u16)source_coords->unk_02;
        coords->unk_06 = (u16)source_coords->unk_06;
        coords->unk_0A = (u16)source_coords->unk_0A;
        return object;
    } else {
        return NULL;
    }
}
