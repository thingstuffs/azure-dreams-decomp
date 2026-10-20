#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
extern void apply_entity_effects(void *);
extern void clear_slots_of_type(void *, s8);
extern void begin_deferred_item_action(void *, u8 *, u8 *, void *);
extern void clear_slot_and_update_linked_state(s32);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern s32 append_entity_display_text(void *record, u8 *out);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void apply_item_effect_at_entity_position(void *, s32);
extern void display_item_status_message(void *, s32, s16);
extern s32 apply_actor_food_preference(void *, s32, s32);
extern void create_timed_paired_particle_emitter(s32, s32, void *);
extern M2C_UNK D_800E0EB4;
extern M2C_UNK D_800E0EC9;
/* Kill one actor: the player takes the game-over path, others drop their message, clear their slots and decrement the live count. */
s32 use_item_to_reset_actor_statuses(void *actor, s32 cause, s16 amount)
{
    s32 handle;
    s32 msg_value;
    register s32 *msg;
    register s32 msg_arg;
    DungeonGlobalStatus *counters;
    s32 slot;
    if (actor == (((u8 *)D_800E3D7C))) {
        *((s32 *) (((s8 *) actor) + 0x110)) = cause;
        begin_deferred_item_action(actor, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), actor);
        return 0;
    }
    if (((u32) actor) <= 0x9FFFFFFFU) {
        display_item_status_message(actor, cause, amount);
        if (apply_actor_food_preference(actor, (D_800DDE84[*((u8 *) (((s8 *) actor) + 0x13))] >> 6) & 3, 0) == 0) {
            apply_item_effect_at_entity_position(actor, cause);
            return 1;
        }
    }
    create_timed_paired_particle_emitter(*((s32 *) (((s8 *) actor) + (-0x18))), 0x20C0C0, actor);

    if ((*((s32 *) (((s8 *) actor) + 0x14))) & 0x4000) {
        handle = get_unused_text_buffer();
        msg = &D_800E0EB4;
        msg_arg = handle;
        handle = expand_text_control_codes(msg, msg_value = msg_arg);
        func_80099290(expand_text_control_codes(&D_800E0EC9, append_entity_display_text(actor, handle)));
        display_text_with_fullwidth_adjustment(msg_value);
    }
    if ((*((s32 *) (((s8 *) actor) + 0x1C))) & 0x04000000) {
        *((s8 *) (((s8 *) actor) + 0x28)) = (s8) ((((u8) (*((u8 *) (((s8 *) actor) + 0x29)))) >> 1) + 1);
    }
    slot = 1;
    *((u8 *) (((s8 *) actor) + 0x26)) = (u8) (*((u8 *) (((s8 *) actor) + 0x68)));
    *((u8 *) (((s8 *) actor) + 0x27)) = (u8) (*((u8 *) (((s8 *) actor) + 0x69)));
    do {
        clear_slots_of_type(actor, slot);
        slot += 1;
    }
    while (slot < 0x21);
    *((s32 *) (((s8 *) actor) + 0x1C)) = (s32) ((*((s32 *) (((s8 *) actor) + 0x1C))) & 0xFBFFE10F);
    apply_entity_effects(actor);
    clear_slot_and_update_linked_state(cause);
    counters = &g_dungeon_status;
    *((u16 *) (((s8 *) counters) + 0xA)) = (u16) ((*((u16 *) (((s8 *) counters) + 0xA))) - 1);
    return 1;
}
