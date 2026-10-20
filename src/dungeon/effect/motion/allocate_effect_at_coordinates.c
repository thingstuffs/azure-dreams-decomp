#include "shared/object_node.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

M2C_UNK func_8003DB94();
s32 register_node();
extern M2C_UNK D_80024224;
extern M2C_UNK D_800DE8E8;

typedef struct S_800242A0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0x18];
    s32 unk_2C;
} S_800242A0_0;

typedef struct S_800242A0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800242A0_1;



   /* arg1 in allocate_effect_at_coordinates */

/* Allocate and initialize an object with the supplied value and coordinates. */
void *allocate_effect_at_coordinates(s32 object_value, MovingPosition *source_coords) {
    S_800242A0_1 *sprite;
    S_800242A0_0 *object;
    MovingPosition *coords;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = &D_80024224;
        sprite = object->unk_0C;
        object->unk_2C = object_value;
        sprite->unk_0E = 0x80;
        sprite->unk_0D = 0x80;
        sprite->unk_0C = 0x80;
        func_8003DB94(sprite, &D_800DE8E8, 0);
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
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
