#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_80095A10_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_80095A10_0;   /* arg0 in update_familiar_summoning */

typedef struct S_80095A10_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80095A10_1;   /* arg2 in update_familiar_summoning */

typedef struct S_80095A10_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
} S_80095A10_2;   /* arg3 in update_familiar_summoning */

typedef struct S_80095A10_3 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_80095A10_3;

typedef struct S_80095A10_4 {
    u8 unk_00;
} S_80095A10_4;   /* &D_800E3E40 in update_familiar_summoning */

typedef struct S_80095A10_5_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_80095A10_5_pre;   /* 0x18-byte header immediately before the payload. */

typedef struct S_80095A10_5 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0x5];
    u8 unk_25;
} S_80095A10_5;

typedef struct S_80095A10_6 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_80095A10_6;

typedef struct S_80095A10_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80095A10_7;

   /* arg1 in update_familiar_summoning */

typedef struct S_80095A10_9 {
    u8 pad_00[0x2];
    u16 unk_02;
} S_80095A10_9;

typedef struct S_80095A10_10 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80095A10_10;   /* ((S_80095A10_2 *)arg3)->unk_60 in update_familiar_summoning */


s32 Control_CD();
void func_800424E0();
void func_80042560();
s32 func_80042640(void *, s32);
void clear_slots_of_type();
void runtime_map_type_16_entry_code();
s32 queue_cd_resource();
void runtime_no_op_callback();
void set_sprite_animation_frame();
void create_familiar_deployment_effect_with_owner_state();
void create_familiar_deployment_overlay();
void resolve_familiar_deployment_request();
void process_unflagged_linked_entries();
void process_unflagged_linked_entries_alt();
void *(*load_monster_resource_data())(s32, s8, s8, s16);
s32 find_or_retain_sprite_resource_slot();
s32 play_sound_if_enabled();
extern s32 loaded_entity_sprite_resource;
extern u8 player_wait_frames[];
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern void *familiar_record_slots[];
extern s8 entity_resource_read_complete;

/* Advances the resource loading, object creation, and animation sequence. */
void update_familiar_summoning(u8 *actor, MovingPosition *position, void *animation, u8 *context) {

    u8 *animation_table;
    s32 load_resource;
    s32 spawn_resource;
    u32 object_flags;
    u16 ticks_left;
    u16 animation_flags;
    u8 *resource_info;
    u32 state;
    u32 previous_state;
    void *object;
    void *object_scale;
    void *object_position;

    state = ((S_80095A10_0 *)actor)->unk_9B;
    resource_info = ((u8 *)reference_tile_object.selected_item);
    switch (state) {
    case 0:
        if (!(((S_80095A10_1 *)animation)->unk_14 & 0xE000)) {
            return;
        }
        (*(s32 **)((u8 *)animation + 0x2C)) = D_800DD138;
        set_sprite_animation_frame(animation, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80095A10_2 *)context)->unk_2A + 0x100)
            >> 9) & 7) + D_800DD138), 0, 1);
        ((S_80095A10_1 *)animation)->unk_14 = (u16) (((S_80095A10_1 *)animation)->unk_14 | 0x200);
        create_familiar_deployment_effect_with_owner_state(actor, position, animation);
        create_familiar_deployment_overlay(actor, position, animation);
        previous_state = ((S_80095A10_0 *)actor)->unk_9B;
        ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
        return;
    case 1:
        load_resource = find_or_retain_sprite_resource_slot(((S_80095A10_3 *)resource_info)->unk_00, 2);
        if (load_resource == 0) {
            previous_state = ((S_80095A10_0 *)actor)->unk_9B;
        ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
        return;
        }
        loaded_entity_sprite_resource = queue_cd_resource(((S_80095A10_3 *)resource_info)->unk_00);
        load_monster_resource_data(((S_80095A10_3 *)resource_info)->unk_00, load_resource, 0);
        (*(s8 *)&entity_resource_read_complete) = 0;
        Control_CD(0xFF, set_byte_one, &entity_resource_read_complete);
        previous_state = ((S_80095A10_0 *)actor)->unk_9B;
        ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
        return;
    case 2:
        if (((S_80095A10_4 *)(&entity_resource_read_complete))->unk_00 == 0) {
            return;
        }
        runtime_no_op_callback(state);
        previous_state = ((S_80095A10_0 *)actor)->unk_9B;
        ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
        return;
    case 3:
        spawn_resource = find_or_retain_sprite_resource_slot(((S_80095A10_3 *)resource_info)->unk_00, 2);
        if (spawn_resource == 0) {
            return;
        }
        runtime_map_type_16_entry_code(((u8 *)reference_tile_object.selected_item));
        object = load_monster_resource_data(((S_80095A10_3 *)resource_info)->unk_00, spawn_resource, 1)(6,
            ((S_80095A10_2 *)context)->unk_72, ((S_80095A10_2 *)context)->unk_73,
            (s16) (((S_80095A10_2 *)context)->unk_88 - 0x20));
        if (object != 0) {
            ((S_80095A10_2 *)context)->unk_60 = object;
            familiar_record_slots[((S_80095A10_3 *)resource_info)->unk_03 & 0x1F] = object;
            object_scale = ((S_80095A10_5_pre *)object)[-1].unk_04;
            ((S_80095A10_6 *)object_scale)->unk_1E = 0x800;
            ((S_80095A10_6 *)object_scale)->unk_1C = 0x800;
            object_position = ((S_80095A10_5_pre *)object)[-1].unk_00;
            ((S_80095A10_7 *)object_position)->unk_02 = (u16) position->unk_02;
            ((S_80095A10_7 *)object_position)->unk_06 = (u16) position->unk_06;
            ((S_80095A10_7 *)object_position)->unk_0A = (s16) (position->unk_0A - 0x10);
            func_80042640(object, ((S_80095A10_5 *)object)->unk_13);
            func_800424E0(object, ((S_80095A10_5 *)object)->unk_13, resource_info);
            object_flags = ((S_80095A10_5 *)object)->unk_1C;
            object_flags |= 0x02000000;
            object_flags |= 0x20000;
            ((S_80095A10_5 *)object)->unk_1C = object_flags;
            func_80042560(object);
            play_sound_if_enabled(0x704);
            clear_slots_of_type(object, 3);
            clear_slots_of_type(object, 1);
            if (((S_80095A10_5 *)object)->unk_25 == 0) {
                ((S_80095A10_5 *)object)->unk_25 = 1U;
            }
        }
        previous_state = ((S_80095A10_0 *)actor)->unk_9B;
        {
            animation_flags = 0x10U;
            ((S_80095A10_0 *)actor)->unk_96 = animation_flags;
            ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
            return;
        }
    case 4:
        ticks_left = ((S_80095A10_0 *)actor)->unk_96 - 1;
        ((S_80095A10_0 *)actor)->unk_96 = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            return;
        }
        (*(s32 **)((u8 *)animation + 0x2C)) = D_800DD140;
        set_sprite_animation_frame(animation, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80095A10_2 *)context)->unk_2A + 0x100)
            >> 9) & 7) + D_800DD140), 0, 1);
        previous_state = ((S_80095A10_0 *)actor)->unk_9B;
        ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
        return;
    case 5:
        animation_flags = ((S_80095A10_1 *)animation)->unk_14;
        if (!(animation_flags & 0x6000)) {
            return;
        }
        animation_table = player_wait_frames;
        ((S_80095A10_1 *)animation)->unk_14 = (u16) (animation_flags & 0xFDFF);
set_animation:
        (*(s32 **)((u8 *)animation + 0x2C)) = animation_table;
        set_sprite_animation_frame(animation, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + ((S_80095A10_2 *)context)->unk_2A + 0x100)
            >> 9) & 7) + animation_table), 0, 1);
advance_state:
        previous_state = ((S_80095A10_0 *)actor)->unk_9B;
store_next_state:
        ((S_80095A10_0 *)actor)->unk_9B = (u8) (previous_state + 1);
        return;
    case 6:
        if (((S_80095A10_10 *)(((S_80095A10_2 *)context)->unk_60))->unk_14 & 0x100000) {
            return;
        }
        resolve_familiar_deployment_request(actor, position, animation, resource_info);
        ((S_80095A10_0 *)actor)->unk_8C = handle_player_input;
        process_unflagged_linked_entries_alt(((S_80095A10_2 *)context)->unk_5C);
        process_unflagged_linked_entries(((S_80095A10_2 *)context)->unk_5C);
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x812);
        return;
    }
}
