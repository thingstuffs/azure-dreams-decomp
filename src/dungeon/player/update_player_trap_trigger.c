#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[0x9B];
    u8 state;
    u8 pad9C[0x100 - 0x9C];
    s16 h100;
} Actor;

extern u8 D_800E3648[];
extern u8 D_800E0B39[];
extern u8 D_80088B14[];
extern u8 D_800E0B4C[];

extern s32 try_claim_dungeon_action_slot(s32);
extern void restore_player_control_callback(Actor *, s32);
extern s32 get_unused_text_buffer();
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern s32 write_text_byte_and_advance(s8 value, s8 *dest);
extern s32 append_value_seven_suffix(u8 *dst);
extern s32 append_typed_formatted_value(void *, s32);
extern void copy_fullwidth_vowel_bytes(s32, s32);
extern s32 write_status_prefix_bytes(s32);
extern void func_80099290(s8 *byte_ptr);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void reveal_triggered_trap(Actor *, s32, s32, s32);
extern s16 call_slot_handler_and_update_status(s32 handler_id, void *object_ptr, s32 slot_id, s8 update_state);

/* Advance the actor's entry action and clear pending state when it finishes. */
void update_player_trap_trigger(Actor *actor, s32 context_a, s32 context_b, s32 target_arg) {
    u8 *entry;
    u8 *tab;
    int state = actor->state;
    s32 target = target_arg;
    if (state != 1) {
        if (state >= 2) {
            return;
        }
        if (state != 0) {
            return;
        }
        if (g_dungeon_status.flags & 0x1000) {
            return;
        }
        if ((s16) try_claim_dungeon_action_slot(target) != 0) {
            return;
        }
        tab = D_800E3648;
        entry = &tab[actor->h100 * 4];
        if (entry[0] == 0) {
            restore_player_control_callback(actor, target);
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.trap_counts.parts.pending_trap_count--;
            g_dungeon_status.flags &= 0xFFF7;
            return;
        }
        if (!(entry[3] & 0x40)) {

            s32 cursor;
            s32 buffer_start;
            s32 patch_pos;
            s32 entry_pos;
            cursor = get_unused_text_buffer();
            buffer_start = cursor;
            cursor = append_value_seven_suffix(expand_text_control_codes(D_800E0B39, write_text_byte_and_advance(8, cursor)));
            patch_pos = cursor - 2;
            cursor = expand_text_control_codes(D_80088B14, cursor);
            entry_pos = cursor;
            cursor = append_typed_formatted_value(&D_800E3648[actor->h100 * 4], entry_pos);
            copy_fullwidth_vowel_bytes(patch_pos, entry_pos);
            func_80099290(write_status_prefix_bytes(expand_text_control_codes(D_800E0B4C, write_text_byte_and_advance(10, cursor))));
            display_text_with_fullwidth_adjustment(buffer_start);
        }
        actor->state++;
        reveal_triggered_trap(actor, context_a, context_b, target);
    }
    if (D_800E3648[actor->h100 * 4] == 0) {
        restore_player_control_callback(actor, target);
        g_dungeon_status.active_actor = 0;
        g_dungeon_status.trap_counts.parts.pending_trap_count--;
        g_dungeon_status.flags &= 0xFFF7;
        return;
    } else {
        s16 result = (s16) call_slot_handler_and_update_status(D_800E3648[actor->h100 * 4], target, actor->h100, 0);
        if (result != 0) {
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.trap_counts.parts.pending_trap_count--;
            g_dungeon_status.flags &= 0xFFF7;
            if (result > 0) {
                restore_player_control_callback(actor, target);
            }
            actor->state++;
        }
    }
}
