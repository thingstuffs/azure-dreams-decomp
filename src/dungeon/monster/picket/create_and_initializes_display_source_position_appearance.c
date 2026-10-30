#include "shared/object_node.h"
#include "dungeon/monster/picket.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "records/Rec_func_800AD058_arg2.h"
#include "shared/dungeon_projectile_views.h"
#include "engine/node.h"
#include "engine/menu.h"

/* Sparse views for fields not covered by the existing record types. */
typedef struct {
    u8 pad_00[0x48];
    u8 field_48;
    u8 field_49;
} AppearanceFieldView_80E8F548;

typedef struct {
    s32 value;
} __attribute__((packed)) unaligned_s32;

#ifndef NULL
#define NULL 0
#endif

extern void create_tracked_effect(void *, s32, s32, s32);

extern u8 item_effect_descriptor[9];

typedef struct S_80174D48_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x9C];
    s16 unk_A8;
    s16 unk_AA;
} S_80174D48_1;

typedef struct S_80174D48_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_80174D48_2;

typedef struct S_80174D48_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_80174D48_3;

/* Creates and initializes a display object from the source position and appearance. */
/* Creates a moving display for the held item, selecting its texture by item category and preserving its
 * item data. */
void create_and_initializes_display_source_position_appearance(void *source, Rec_func_800AD058_arg2 *record, void *appearance)
{
    s32 coord_z;
    s32 record_byte;
    s32 coord_value;
    void *init_object;
    void *active_object;
    s32 zero;
    s32 sprite_size;
    S_80174D48_3 *sprite;
    S_80174D48_1 *data_base;
    S_80174D48_1 *data_base_2;
    void *object_data;
    void *texture;
    ProjectileObject *object;
    S_80174D48_2 *transform;

    if (((((AppearanceFieldView_80E8F548 *)appearance)->field_49) != 0) &&
        (object = allocate_flagged_object_node(0x12), object != NULL)) {
        init_object = object;
        transform = object->position;
        data_base_2 = source;
        coord_value = data_base_2->unk_00;
        sprite = object->sprite;
        transform->unk_00 = coord_value;
        transform->unk_04 = data_base_2->unk_04;
        coord_z = data_base_2->unk_08;
        transform->unk_10 = 0;
        transform->unk_0C = 0;
        transform->unk_14 = 0xFFEE0000;
        transform->unk_08 = coord_z;
        register_node(init_object, project_sprite_chain);
        sprite->unk_0C = 0x808080;
        sprite_size = 0xC90;
        object_data = (u8 *)object + 0x20;
        sprite->unk_1E = sprite_size;
        sprite->unk_1C = sprite_size;
        data_base = object_data;
        if ((((AppearanceFieldView_80E8F548 *)appearance)->field_49) == 0x12) {
            texture = item_effect_descriptor;
            sprite->unk_08 = (s32)texture;
            record_byte = record->unk_24;
        } else {
            texture = (void *)lookup_item_category_mapped_value((((AppearanceFieldView_80E8F548 *)appearance)->field_49),
                          (((AppearanceFieldView_80E8F548 *)appearance)->field_48));
            sprite->unk_08 = (s32)texture;
            record_byte = record->unk_24;
        }
        active_object = object;
        data_base->unk_A8 = record_byte;
        record_byte = record->unk_25;
        data_base->unk_AA = record_byte;
        zero = 0;
        (*(unaligned_s32 *)((u8 *)object_data + 0x48)) = (*(unaligned_s32 *)((u8 *)appearance + 0x48));
        create_tracked_effect(active_object, zero, zero, zero);
        object->update_callback = update_a_timed_movement_animation_marks_completion;
    }
}
