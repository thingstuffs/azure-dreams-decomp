#include "common.h"
#include "shared/dungeon_status.h"
#include "dungeon/level.h"

typedef struct {
    u8 pad0[0x9B];
    u8 state;
    u8 pad9C[0x100 - 0x9C];
    s16 h100;
} Actor;

extern u8 floor_objects[];
extern u8 D_800E0B39[];
extern u8 D_80088B14[];
extern u8 D_800E0B4C[];

extern s32 try_claim_dungeon_action_slot(s32);
extern void restore_player_control_callback(Actor *, s32);
extern void * get_unused_text_buffer(); /* Unprototyped: zero, one or three arguments; retail replaces all incoming arguments. */
extern u8 * expand_text_control_codes(u8 *src, u8 *dst);
extern void * write_text_byte_and_advance(s8 value, s8 *dest);
extern void * append_value_seven_suffix(u8 *dst);
extern u8 * append_typed_formatted_value(void *,u8 *);
extern void *copy_fullwidth_vowel_bytes(void *dst, void *character);
extern void * write_status_prefix_bytes(void *);
extern void clear_byte_and_advance(s8 *byte_ptr);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void reveal_triggered_trap(Actor *, s32, s32, s32);

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
        tab = floor_objects;
        entry = &tab[actor->h100 * 4];
        if (entry[0] == 0) {
            restore_player_control_callback(actor, target);
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.trap_counts.parts.pending_trap_count--;
            g_dungeon_status.flags &= 0xFFF7;
            return;
        }
        if (!(entry[3] & 0x40)) {

            void *cursor;
            void *buffer_start;
            s32 patch_pos;
            void *entry_pos;
            cursor = get_unused_text_buffer();
            buffer_start = cursor;
            cursor = append_value_seven_suffix(expand_text_control_codes(D_800E0B39, write_text_byte_and_advance(8, cursor)));
            patch_pos = cursor - 2;
            cursor = expand_text_control_codes(D_80088B14, cursor);
            entry_pos = cursor;
            cursor = append_typed_formatted_value(&floor_objects[actor->h100 * 4], entry_pos);
            copy_fullwidth_vowel_bytes(patch_pos, entry_pos);
            clear_byte_and_advance(write_status_prefix_bytes(expand_text_control_codes(D_800E0B4C, write_text_byte_and_advance(10, cursor))));
            display_text_with_fullwidth_adjustment(buffer_start);
        }
        actor->state++;
        reveal_triggered_trap(actor, context_a, context_b, target);
    }
    if (floor_objects[actor->h100 * 4] == 0) {
        restore_player_control_callback(actor, target);
        g_dungeon_status.active_actor = 0;
        g_dungeon_status.trap_counts.parts.pending_trap_count--;
        g_dungeon_status.flags &= 0xFFF7;
        return;
    } else {
        s16 result = (s16) call_slot_handler_and_update_status(floor_objects[actor->h100 * 4], target, actor->h100, 0);
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
