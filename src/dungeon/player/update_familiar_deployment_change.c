#include "dungeon/item/message.h"
#include "shared/dungeon_actor_callbacks.h"
#include "shared/object_links.h"
#include "shared/sprite_frame_state.h"
#include "dungeon/actor/callback.h"
#include "common.h"
#include "dungeon/item/monster_resource_slots_g00325.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/player/state.h"
#include "dungeon/player.h"
#include "dungeon/player/object.h"
#include "engine/entity.h"
#include "engine/texture.h"
#include "dungeon/data.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void runtime_map_type_16_entry_code();                      /* extern */
s32 begin_sprite_resource_load_with_completion_flag(); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */                   /* extern */
void set_sprite_animation_frame(SpriteFrameState *obj, s16 frame_group, s16 frame_index, s32 slot_index); /* extern */
void unlink_entity_node(struct EntityLinkNode *node);                      /* extern */
#include "dungeon/player/object/action_state.h"
#include "dungeon/item.h"
#include "dungeon/level.h"
#include "slus.h"
#include "dungeon/system.h"

struct Entity;
struct EntityLinkNode;
extern s32 loaded_entity_sprite_resource;
extern s32 sprite_resource_completion_flag;
extern void *selected_item_record_alias[];
extern struct S_8009345C_4 familiar_deployment_slots;
extern u8 D_800E05E1[15];
extern u8 D_800E05F0[16];
extern u8 D_800E06FA[26];
extern u8 D_800E0714[18];
extern s32 familiar_turn_counters_alias[];
extern void *familiar_record_slots[];
extern s8 entity_resource_read_complete;

typedef union ScratchS1 {
    void *text;
    void **base;
} ScratchS1;

typedef struct S_8009345C_0 {
    u8 pad_00[0x8C];
    ActorCallback action_callback; /* 0x8C */
    u8 pad_90[0x6];
    u16 wait_ticks; /* 0x96 */
    u8 pad_98[0x3];
    u8 phase; /* 0x9B */
} S_8009345C_0;   /* actor in update_familiar_deployment_change */

   /* entity in update_familiar_deployment_change */



typedef struct S_8009345C_4 {
    union { u16 u; s16 s; } slot; /* 0x00 */   /* accessed as both */
} S_8009345C_4;   /* &D_800DD262 in update_familiar_deployment_change */

   /* 0x2-byte header immediately before the payload. */

typedef struct S_8009345C_7 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_8009345C_7;   /* *scratch_s1.base in update_familiar_deployment_change */

typedef struct S_8009345C_8 {
    u8 unk_00;
} S_8009345C_8;   /* &D_800E3E40 in update_familiar_deployment_change */

typedef struct S_8009345C_9 {
    u8 unk_00;
    u8 pad_01[0x2];
    u8 unk_03;
} S_8009345C_9;   /* D_80082EB0[0] in update_familiar_deployment_change */

typedef struct S_8009345C_10_pre {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x10];
} S_8009345C_10_pre;   /* 0x18-byte header immediately before the payload. */




   /* map in update_familiar_deployment_change */

typedef struct S_8009345C_14 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_8009345C_14;



/* Advances the object replacement sequence, including animation, messages, and cleanup. */
void update_familiar_deployment_change(void *actor, ObjectPosition *map, SpriteFrameState *entity, ActorRecord *context) {

    u8 *remove_text;
    u8 *create_text;
    void *remove_message;
    void *load_id;
    void *create_id;
    s32 object_flags;
    s32 cleanup_slot;
    u8 *create_message;
    u16 start_ticks;
    u16 end_ticks;
    u16 entity_flags;
    u16 slot_bits;
    s16 selected_slot;
    s32 object_slot;
    u8 state;
    u8 next_state;
    void *new_object;
    void *selected_object;
    void *old_object;
    ObjectStatusPrefix16 *removed_object;
    SpriteFrameState *object_scale;
    ObjectPosition *object_position;
    ScratchS1 message_or_list;

    state = ((S_8009345C_0 *)actor)->phase;
    switch (state) {
    case 0:
        if (!(entity->flags & 0x6000)) {
            return;
        }
        entity->frameTable = familiar_save_restore_frames;
        set_sprite_animation_frame(entity, familiar_save_restore_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + context->facing + 0x100)
            >> 9) & 7], 0, 1);
        create_familiar_deployment_effect_with_owner_state(actor, map, entity);
        create_familiar_deployment_overlay(actor, map, entity);
        entity_flags = entity->flags;
        familiar_removed_during_change = 0;
        entity->flags = (u16) (entity_flags | 0x200);
        ((S_8009345C_0 *)actor)->wait_ticks = 0x10U;
        selected_slot = context->unk_8A;
        slot_bits = context->unk_8A;
        selected_object = ((ActorRecord *)(((selected_slot * 4) + actor)))->unk_AC.address;
        familiar_deployment_slots.slot.u = slot_bits;
        context->target = selected_object;
        ((S_8009345C_0 *)actor)->phase++;
        return;
    case 1:
        start_ticks = ((S_8009345C_0 *)actor)->wait_ticks - 1;
        ((S_8009345C_0 *)actor)->wait_ticks = start_ticks;
        if ((start_ticks << 0x10) > 0) {
            return;
        }
        if (context->target != NULL) {
            store_recalled_familiar(actor, map, entity, context);
            ((S_8009345C_0 *)actor)->phase++;
            return;
        }
        next_state = ((S_8009345C_0 *)actor)->phase + 2;
        break;
    case 2:
        if (!(((ActorRecord *)(context->target))->flags1C & 0x800000)) {
            return;
        }
        message_or_list.text = get_unused_text_buffer();
        remove_message = write_text_byte_and_advance(8, message_or_list.text);
        if (familiar_deployment_slots.slot.s != 0) {
            remove_text = D_800E05F0;
        } else {
            remove_text = D_800E05E1;
        }
        clear_byte_and_advance(expand_text_control_codes(D_800E06FA, append_entity_display_text(context->target,
            expand_text_control_codes(remove_text, remove_message))));
        display_text_with_fullwidth_adjustment(message_or_list.text);
        old_object = context->target;
        familiar_removed_during_change = 1;
        mark_owned_linked_actor_actions(old_object);
        ((ActorRecord *)(((familiar_deployment_slots.slot.s * 4) + actor)))->unk_AC.value = 0;
        decrement_monster_entry_count(((ActorRecord *)(context->target))->species, 3);
        unlink_entity_node(context->target);
        removed_object = context->target;
        removed_object[-1].flags = (u16) (removed_object[-1].flags
            | 0x8000);
        (*&object_flag_block.flags) = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        if (selected_item_record_alias[0] == NULL) {
            ((S_8009345C_0 *)actor)->wait_ticks = 0U;
            next_state = ((S_8009345C_0 *)actor)->phase + 4;
            break;
        }
        ((S_8009345C_0 *)actor)->phase++;
        return;
    case 3:
        if ((has_pending_dungeon_activity(0) << 0x10) != 0) {
            return;
        }
        message_or_list.base = selected_item_record_alias;
        load_id = find_or_retain_sprite_resource_slot(((S_8009345C_7 *)(*message_or_list.base))->unk_00, 3);
        if (load_id != 0) {
            loaded_entity_sprite_resource = begin_sprite_resource_load_with_completion_flag(((S_8009345C_7 *)(*message_or_list.base))->unk_00, &sprite_resource_completion_flag);
            load_monster_code_module(((S_8009345C_7 *)(*message_or_list.base))->unk_00, load_id, 0);
            (*&entity_resource_read_complete) = 0;
            Control_CD(0xFF, set_byte_one, &entity_resource_read_complete);
        }
        ((S_8009345C_0 *)actor)->phase++;
        return;
    case 4:
        if (((S_8009345C_8 *)(&entity_resource_read_complete))->unk_00 == 0) {
            return;
        }
        if (loaded_entity_sprite_resource != 0) {
            register_and_upload_sprite_resource(((S_8009345C_9 *)(selected_item_record_alias[0]))->unk_00, loaded_entity_sprite_resource);
        }
        ((S_8009345C_0 *)actor)->phase++;
        return;
    case 5:
        message_or_list.base = selected_item_record_alias;
        create_id = find_or_retain_sprite_resource_slot(((S_8009345C_7 *)(*message_or_list.base))->unk_00, 3);
        if (create_id != 0) {
            runtime_map_type_16_entry_code(*message_or_list.base);
            new_object = load_monster_code_module(((S_8009345C_7 *)(*message_or_list.base))->unk_00, create_id, 1)(1,
                context->target_tile_x, context->target_tile_y,
                (s16) (context->ground_height - 0x20));
            if (new_object != NULL) {
                (*(void **)((u8 *)(((familiar_deployment_slots.slot.s * 4) + actor)) + (0xAC))) = new_object;
                familiar_record_slots[((S_8009345C_7 *)(*message_or_list.base))->unk_03 & 0x1F] = new_object;
                object_scale = ((S_8009345C_10_pre *)new_object)[-1].unk_04;
                object_scale->scale_y = 0x800;
                object_scale->scale_x = 0x800;
                object_position = ((S_8009345C_10_pre *)new_object)[-1].unk_00;
                object_position->x.unsigned_parts.integer = (u16) map->x.w.i;
                object_position->y.unsigned_parts.integer = (u16) map->y.w.i;
                object_position->z.w.i = (s16) (map->z.w.i - 0x10);
                func_80042640(new_object, ((ActorRecord *)new_object)->species);
                apply_actor_template_and_class(new_object, ((ActorRecord *)new_object)->species, *message_or_list.base);
                object_flags = ((ActorRecord *)new_object)->flags1C;
                object_slot = familiar_deployment_slots.slot.s;
                ((ActorRecord *)new_object)->flags1C = object_flags | 0x02000000;
                ((S_8009345C_14 *)(((object_slot * 4) + actor)))->unk_D0 = selected_item_record_alias[0];
                ((S_8009345C_9 *)(selected_item_record_alias[0]))->unk_03 = (u8) (((S_8009345C_9 *)(selected_item_record_alias[0]))->unk_03 | 0x20);
                message_or_list.text = get_unused_text_buffer();
                create_message = message_or_list.text;
                if (familiar_removed_during_change == 0) {
                    create_message = write_text_byte_and_advance(8, create_message);
                }
                if (familiar_deployment_slots.slot.s != 0) {
                    create_text = D_800E05F0;
                } else {
                    create_text = D_800E05E1;
                }
                clear_byte_and_advance(expand_text_control_codes(D_800E0714, append_entity_display_text(new_object, expand_text_control_codes(create_text,
                    create_message))));
                display_text_with_fullwidth_adjustment(message_or_list.text);
                cleanup_slot = familiar_deployment_slots.slot.s;
                familiar_turn_counters_alias[cleanup_slot] = 0;
                retain_spawn_resource(((S_8009345C_9 *)(selected_item_record_alias[0]))->unk_00, 3);
                replay_actor_status_slots(new_object);
                play_sound_if_enabled(0x704);
            }
        }
        next_state = ((S_8009345C_0 *)actor)->phase;
        start_ticks = 0x10U;
        ((S_8009345C_0 *)actor)->wait_ticks = start_ticks;
        next_state = next_state + 1;
        break;
    case 7:
        end_ticks = ((S_8009345C_0 *)actor)->wait_ticks - 1;
        ((S_8009345C_0 *)actor)->wait_ticks = end_ticks;
        if ((end_ticks << 0x10) > 0) {
            return;
        }
        entity->frameTable = familiar_save_frames;
        set_sprite_animation_frame(entity, familiar_save_frames[((s32) (g_game_work.view.camera_rotation.parts.viewAngle + context->facing + 0x100)
            >> 9) & 7], 0, 1);
        ((S_8009345C_0 *)actor)->phase++;
        return;
    case 8:
        if (!(entity->flags & 0x6000)) {
            return;
        }
        ((S_8009345C_0 *)actor)->action_callback = handle_player_input;
        process_unflagged_linked_entries_alt(context->next_actor_header);
        process_unflagged_linked_entries(context->next_actor_header);
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x812);
        entity->flags = (u16) (entity->flags & 0xFDFF);
    case 6:
        ((S_8009345C_0 *)actor)->phase++;
        return;
    case 9:
    default:
        return;
    }
    ((S_8009345C_0 *)actor)->phase = next_state;
}
