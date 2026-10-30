#include "common.h"
#include "engine/menu.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "engine/util.h"
#include "sdk/libc.h"
#include "slus.h"
#include "town/map.h"
#include "town/minigame.h"
#include "town/scene.h"
#include "town/minigame/position.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_800254A4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800254A4_0;   /* obj in initialize_tako_minigame */

typedef struct S_800254A4_1 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_800254A4_1;   /* root in initialize_tako_minigame */

typedef struct S_800254A4_3 {
    u8 pad_00[0x4C];
    void * unk_4C;
    u8 pad_50[0x6];
    s16 unk_56;
} S_800254A4_3;   /* part1 in initialize_tako_minigame */

typedef struct S_800254A4_5 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 pad_08[0x4];
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800254A4_5;   /* part2 in initialize_tako_minigame */

typedef struct S_800254A4_6 {
    u8 pad_00[0x4];
    void * unk_04;
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
    s16 unk_14;
    s16 unk_16;
    s16 unk_18;
    s16 unk_1A;
} S_800254A4_6;   /* part3 in initialize_tako_minigame */


extern u8 D_8002012C[];
extern u8 D_80020134[];
extern u8 D_8002013C[];
extern u8 D_80020140[];
extern u8 D_80020144[];
extern u8 D_80020148[];
extern u8 D_8002582C[];
extern u8 D_80025BC8[];
extern u8 D_80026B78[];
extern u8 D_80026BC4[];
extern u8 D_80026C54[];
extern u8 D_80026F50[];
extern s32 text_sprite_builder_address[4];

extern u8 tako_minigame_sprites[];

/* Creates a parent object, three children, paired display rows, and a final display element. */
s32 initialize_tako_minigame(void)
{
    u8 *parent_state = NULL;
    void * left_data[2] = { D_8002012C, D_80020134 };
    void * right_data[2] = { D_8002013C, D_80020140 };
    ObjectNodeHeader *object;
    S_800254A4_3 *child_state;
    S_800254A4_5 *left_state;
    S_800254A4_6 *right_state;
    SceneTileObject *final_state;
    SpriteFrameState *draw_state;
    ObjectPosition *packet;
    void *value_ptr;
    void *row_data;
    void *child_callback;
    void *callback;
    void *child_data;
    void **child_slot;
    u8 *initial_data = D_80020144;
    u8 *src_byte;
    u8 *first_dst_byte;
    u8 *second_dst_byte;
    u8 initial_byte;
    s32 index;
    s32 final_color;
    s32 final_extent;
    s16 row_y;

    tw_sd_sq_ld_call(0x24, 0x200);
    create_timed_sound(0x5A);
    func_8003E188(0x3C, (s32)parent_state);

    object = allocate_flagged_object_node(2);
    if (object != NULL) {
        parent_state = (u8 *)object + 0x20;
        object->update_callback = D_80025BC8;
        ((S_800254A4_1 *)parent_state)->unk_18 = rand() & 1;
    }

    index = 2;
    child_callback = D_8002582C;
    child_data = D_80020148;
    child_slot = (void **)(parent_state + 8);
create_child:
    object = allocate_flagged_object_node(0x136);
    *child_slot = object;
    if (object != NULL) {
        object->update_callback = child_callback;
        register_node(object, project_sprite_chain);
        child_state = (u8 *)object + 0x20;
        draw_state = object->sprite;
        packet = object->position;
        packet->x.v = 0x05600000;
        packet->y.v = (index << 0x16) + 0x03E00000;
        packet->z.v = 0x00800000;
        packet->velocity_z = 0xFFFC0000;
        ((S_800254A4_0 *)object)->unk_20 = parent_state;
        child_state->unk_56 = index;
        draw_state->scale_y = 0x1000;
        draw_state->scale_x = 0x1000;
        select_record_entry_and_value(draw_state, tako_minigame_sprites, 0);
        draw_state->color.word = 0x00808080;
        child_state->unk_4C = child_data;
        configure_the_set_mode_n_1((u8 *)object + 0x24, object->position, D_80026F50);
    }
    index--;
    child_slot--;
    if (index >= 0) {
        goto create_child;
    }

    index = 1;
    callback = D_80026B78;
    row_y = 0x2C;
next_left:
    object = allocate_list_node(1, &scene_object_list_anchor.next);
    left_state = (u8 *)object + 0x20;
    if (object != NULL) {
        object->update_callback = callback;
        register_node(object, text_sprite_builder_address);
        left_state->unk_14 = 0x20;
        left_state->unk_18 = 3;
        left_state->unk_1A = 0x7C80;
        left_state->unk_16 = row_y;
        left_state->unk_10 = 0x00808080;
        row_data = left_data[index];
        left_state->unk_0C = parent_state;
        left_state->unk_04 = row_data;
    }
    index--;
    row_y -= 0xC;
    if (index >= 0) {
        goto next_left;
    }

    index = 1;
    do {
        src_byte = initial_data + index;
        first_dst_byte = (u8 *)right_data[0] + index;
        second_dst_byte = (u8 *)right_data[1] + index;
        initial_byte = *src_byte;
        index--;
        do {
            *second_dst_byte = initial_byte;
            *first_dst_byte = initial_byte;
        } while (0);
    } while (index >= 0);

    index = 1;
    callback = D_80026BC4;
    row_y = 0x2C;
next_right:
    object = allocate_list_node(1, &scene_object_list_anchor.next);
    right_state = (u8 *)object + 0x20;
    if (object != NULL) {
        object->update_callback = callback;
        register_node(object, text_sprite_builder_address);
        right_state->unk_14 = 0x50;
        right_state->unk_18 = 3;
        right_state->unk_1A = 0x7C80;
        right_state->unk_16 = row_y;
        right_state->unk_10 = 0x00808080;
        right_state->unk_04 = right_data[index];
        if (index != 0) {
            if (index == 1) {
                goto link_second_value;
            }
            right_state->unk_0C = parent_state;
            goto next_right_row;
        } else {
            value_ptr = parent_state + 0x12;
            goto store_value_ptr;
        }
link_second_value:
        value_ptr = parent_state + 0x14;
store_value_ptr:
        right_state->unk_08 = value_ptr;
        right_state->unk_0C = parent_state;
    }
next_right_row:
    index--;
    row_y -= 0xC;
    if (index >= 0) {
        goto next_right;
    }

    object = allocate_list_node(1, &scene_object_list_anchor.next);
    if (object != NULL) {
        object->update_callback = D_80026C54;
        register_node(object, build_menu_line_tile_packets);
        final_color = 0x00404040;
        final_state = (u8 *)object + 0x20;
        final_extent = 0x1C;
        final_state->x = final_extent;
        final_state->y = final_extent;
        final_state->width = 0x48;
        final_state->height = final_extent;
        final_state->tpage_mode = 2;
        final_state->flags |= 1;
        final_state->color = final_color;
        final_state->linked = parent_state;
    }

    return 0;
}

/* MECHANISM: Sibling pointer arrays force the 0x48 frame; split first-loop callback liveness yields the
   retail s7/s6/s4 held-base roles. Volatile final stores retain the retail store-before-RMW emission
   order. */
