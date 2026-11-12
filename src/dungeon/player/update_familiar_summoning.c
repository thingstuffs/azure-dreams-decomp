#include "shared/actor_status_ids.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "dungeon/item/monster_resource_slots_g00325.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "shared/tile_object.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/player/state.h"
#include "engine/graphics.h"
#include "dungeon/player.h"
#include "dungeon/level.h"
#include "slus.h"
#include "dungeon/item.h"
#include "engine/entity.h"
#include "engine/texture.h"
#include "dungeon/system.h"
#include "dungeon/data.h"
#include "dungeon/actor/entity_resource_read_complete.h"

   /* arg3 in update_familiar_summoning */

typedef struct S_80095A10_3 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_80095A10_3;


   /* ((S_80095A10_2 *)arg3)->unk_60 in update_familiar_summoning */

void runtime_map_type_16_entry_code();
s32 queue_cd_resource(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern s32 loaded_entity_sprite_resource;
extern u8 player_wait_frames[];
extern void *familiar_record_slots[];

/* Advances the resource loading, object creation, and animation sequence. */
void update_familiar_summoning(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *animation, ActorRecord *context) {

    u8 *animation_table;
    void *load_resource;
    void *spawn_resource;
    u32 object_flags;
    u16 ticks_left;
    u16 animation_flags;
    S_80095A10_3 *resource_info;
    u32 state;
    u32 previous_state;
    ActorRecord *object;
    SpriteFrameState *object_scale;
    ObjectPosition *object_position;

    state = actor->action_phase;
    resource_info = ((S_80095A10_3 *)reference_tile_object.selected_item);
    switch (state) {
    case 0:
        if (!(animation->flags & 0xE000)) {
            return;
        }
        animation->frameTable = familiar_save_restore_frames;
        set_sprite_animation_frame(animation, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + context->facing + 0x100)
            >> 9) & 7) + familiar_save_restore_frames), 0, 1);
        animation->flags = (u16) (animation->flags | 0x200);
        create_familiar_deployment_effect_with_owner_state(actor, position, animation);
        create_familiar_deployment_overlay(actor, position, animation);
        previous_state = actor->action_phase;
        actor->action_phase = (u8) (previous_state + 1);
        return;
    case 1:
        load_resource = find_or_retain_sprite_resource_slot(resource_info->unk_00, 2);
        if (load_resource == 0) {
            previous_state = actor->action_phase;
        actor->action_phase = (u8) (previous_state + 1);
        return;
        }
        loaded_entity_sprite_resource = queue_cd_resource(resource_info->unk_00);
        load_monster_code_module(resource_info->unk_00, load_resource, 0);
        entity_resource_read_complete = 0;
        Control_CD(0xFF, set_byte_one, &entity_resource_read_complete);
        previous_state = actor->action_phase;
        actor->action_phase = (u8) (previous_state + 1);
        return;
    case 2:
        if (entity_resource_read_complete == 0) {
            return;
        }
        runtime_no_op_callback(state);
        previous_state = actor->action_phase;
        actor->action_phase = (u8) (previous_state + 1);
        return;
    case 3:
        spawn_resource = find_or_retain_sprite_resource_slot(resource_info->unk_00, 2);
        if (spawn_resource == 0) {
            return;
        }
        runtime_map_type_16_entry_code(((u8 *)reference_tile_object.selected_item));
        object = load_monster_code_module(resource_info->unk_00, spawn_resource, 1)(6,
            context->target_tile_x, context->target_tile_y,
            (s16) (context->ground_height - 0x20));
        if (object != 0) {
            context->target = object;
            familiar_record_slots[resource_info->unk_03 & 0x1F] = object;
            object_scale = NODE_HEADER(object)->sprite;
            object_scale->scale_y = 0x800;
            object_scale->scale_x = 0x800;
            object_position = NODE_HEADER(object)->position;
            object_position->x.unsigned_parts.integer = (u16) position->x.w.i;
            object_position->y.unsigned_parts.integer = (u16) position->y.w.i;
            object_position->z.w.i = (s16) (position->z.w.i - 0x10);
            func_80042640(object, object->species);
            apply_actor_template_and_class(object, object->species, resource_info);
            object_flags = object->flags1C;
            object_flags |= 0x02000000;
            object_flags |= 0x20000;
            object->flags1C = object_flags;
            replay_actor_status_slots(object);
            play_sound_if_enabled(0x704);
            clear_slots_of_type(object, STATUS_BLIND);
            clear_slots_of_type(object, STATUS_SLEEP);
            if (object->mp_value.parts.whole == 0) {
                object->mp_value.parts.whole = 1U;
            }
        }
        previous_state = actor->action_phase;
        {
            animation_flags = 0x10U;
            actor->action_timer = animation_flags;
            actor->action_phase = (u8) (previous_state + 1);
            return;
        }
    case 4:
        ticks_left = actor->action_timer - 1;
        actor->action_timer = ticks_left;
        if ((ticks_left << 0x10) > 0) {
            return;
        }
        animation->frameTable = familiar_save_frames;
        set_sprite_animation_frame(animation, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + context->facing + 0x100)
            >> 9) & 7) + familiar_save_frames), 0, 1);
        previous_state = actor->action_phase;
        actor->action_phase = (u8) (previous_state + 1);
        return;
    case 5:
        animation_flags = animation->flags;
        if (!(animation_flags & 0x6000)) {
            return;
        }
        animation_table = player_wait_frames;
        animation->flags = (u16) (animation_flags & 0xFDFF);
set_animation:
        animation->frameTable = animation_table;
        set_sprite_animation_frame(animation, *((((s32) (g_game_work.view.camera_rotation.parts.viewAngle + context->facing + 0x100)
            >> 9) & 7) + animation_table), 0, 1);
advance_state:
        previous_state = actor->action_phase;
store_next_state:
        actor->action_phase = (u8) (previous_state + 1);
        return;
    case 6:
        if (((ActorRecord *)(context->target))->flags14 & 0x100000) {
            return;
        }
        resolve_familiar_deployment_request(actor, position, animation, resource_info);
        actor->unk_8C.run = handle_player_input;
        process_unflagged_linked_entries_alt(context->next_actor_header);
        process_unflagged_linked_entries(context->next_actor_header);
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x812);
        return;
    }
}
