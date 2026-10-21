#include "modules/main_title_callbacks.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "engine/graphics.h"
#include "engine/node.h"
#include "frontend/settings.h"
#include "main/data.h"
#include "slus.h"

typedef struct S_80088BD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    union { s16 s16; void * p32; } unk_20;   /* accessed as both */
    u8 pad_24[0xA];
    s16 unk_2E;
} S_80088BD0_0;

typedef struct S_80088BD0_1 {
    u8 pad_00[0x1A];
    s16 unk_1A;
    s16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80088BD0_1;

typedef struct S_80088BD0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_80088BD0_2;

typedef struct S_80088BD0_4 {
    s32 unk_00;
} S_80088BD0_4;

typedef struct S_80088BD0_5 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80088BD0_5;

typedef struct S_80088BD0_6 {
    void * unk_00;
    u8 pad_04[0x6];
    s16 unk_0A;
    s16 unk_0C;
} S_80088BD0_6;

typedef struct S_80088BD0_7 {
    u8 pad_00[0x4];
    void * unk_04;
    s32 unk_08;
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    s16 unk_14;
    s16 unk_16;
} S_80088BD0_7;

typedef struct S_80088BD0_8 {
    u8 pad_00[0x10];
    void * unk_10;
} S_80088BD0_8;

typedef struct S_80088BD0_9 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s32 unk_10;
} S_80088BD0_9;
struct Dst;
struct Elem;
extern s8 animation_tick_scale;
void sync_object_with_sub_object();  /* extern */

typedef struct { s32 a, b, c; } Desc3;

/* Creates a controller and its linked sprites and effect objects. */
void create_settings_controller(void) {
    s32 sprite_ids[3];
    s32 child_index;
    s32 sprite_y;
    s32 start_delay;
    s32 unit_scale;
    s32 sprite_id;
    void *child_state;
    SpriteFrameState *sprite;
    void *object;
    S_80088BD0_7 *effect_state;
    void *parent_state;
    void *id_offset;
    void *child_slot;

    parent_state = NULL;
    *(Desc3 *)sprite_ids = *(Desc3 *)&D_80088760;
    animation_tick_scale = 1;
    object = allocate_flagged_object_node(0x11);
    if (object != NULL) {
        parent_state = object + 0x20;
        ((S_80088BD0_0 *)object)->unk_10 = (void *)update_settings_menu_animation;
        register_node(object, queue_settings_sprite_grid);
        ((S_80088BD0_1 *)parent_state)->unk_22 = 0x708;
        ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_06 = 0xF0;
        ((S_80088BD0_1 *)parent_state)->unk_1A = 0;
        ((S_80088BD0_1 *)parent_state)->unk_1C = 0x40;
    }
    child_index = 2;
    start_delay = 0x3C;
    sprite_y = 0xC8;
    unit_scale = 0x1000;
    child_slot = parent_state + 8;
    do {
        object = allocate_flagged_object_node(0x111);
        ((S_80088BD0_2 *)child_slot)->unk_04 = object;
        id_offset = (void *)(child_index << 2);
        if (object != NULL) {
            child_state = object + 0x20;
            sprite = ((S_80088BD0_0 *)object)->unk_0C;
            ((S_80088BD0_0 *)object)->unk_10 = (void *)update_settings_effect_object;
            register_node(object, &draw_linked_sprites);
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_02 = -0x40;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_06 = sprite_y;
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_0C = 0x150000;
            sprite->scale_y = unit_scale;
            sprite->scale_x = unit_scale;
            sprite_id = ((S_80088BD0_4 *)((s8 *)sprite_ids + (s32)id_offset))->unk_00;
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
            sprite->color.word = 0x808080;
            sprite->source = sprite_id;
            ((S_80088BD0_5 *)((s8 *)child_state - 0x20))->unk_20 = parent_state;
            ((S_80088BD0_6 *)child_state)->unk_0C = child_index;
            ((S_80088BD0_6 *)child_state)->unk_0A = start_delay;
        }
        start_delay -= 0x1E;
        sprite_y -= 0x10;
        child_index -= 1;
        child_slot -= 4;
    } while (child_index >= 0);
    object = allocate_flagged_object_node(1);
    if (object != NULL) {
        ((S_80088BD0_0 *)object)->unk_10 = (void *)sync_object_with_sub_object;
        register_node(object, &display_registration_tag);
        effect_state = object + 0x20;
        effect_state->unk_0C = 0x60;
        effect_state->unk_0E = -0x100;
        effect_state->unk_10 = 0x80;
        effect_state->unk_12 = 0x10;
        effect_state->unk_14 = 0;
        effect_state->unk_16 = 3;
        effect_state->unk_08 = 0x606060;
        ((S_80088BD0_0 *)object)->unk_20.s16 = 0;
        effect_state->unk_04 = parent_state;
    }
    child_index = 1;
    do {
        object = allocate_flagged_object_node(0x111);
        ((S_80088BD0_8 *)((s8 *)parent_state + (child_index << 2)))->unk_10 = object;
        if (object != NULL) {
            child_state = object + 0x20;
            sprite = ((S_80088BD0_0 *)object)->unk_0C;
            ((S_80088BD0_0 *)object)->unk_10 = (void *)update_settings_phase_motion;
            register_node(object, &draw_linked_sprites);
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_06 = 0xE9;
            if (child_index != 0) {
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_02 = -0x15;
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_0C = 0x160000;
                select_record_entry_and_value(sprite, &D_8008B270, 0);
            } else {
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_02 = 0x155;
                ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_0C = 0xFFEA0000;
                select_record_entry_and_value(sprite, &D_8008B230, 0);
            }
            ((S_80088BD0_9 *)(((S_80088BD0_0 *)object)->unk_08))->unk_10 = 0xFFF80000;
            sprite->scale_y = 0x1000;
            sprite->scale_x = 0x1000;
            sprite->color.word = 0x808080;
            ((S_80088BD0_6 *)child_state)->unk_00 = parent_state;
            ((S_80088BD0_6 *)child_state)->unk_0C = child_index;
        }
        child_index -= 1;
    } while (child_index >= 0);
    object = allocate_flagged_object_node(1);
    if (object != NULL) {
        ((S_80088BD0_0 *)object)->unk_10 = (void *)update_settings_effect;
        ((S_80088BD0_0 *)object)->unk_20.p32 = parent_state;
        ((S_80088BD0_0 *)object)->unk_2E = 0xE00;
    }
}
