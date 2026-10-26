#include "shared/actor_property_flags.h"
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/def_table.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/dungeon_status.h"
#include "engine/cd.h"
#include "dungeon/system.h"
#include "dungeon/item/message.h"
extern int abs(int);

typedef struct S_800C0E88_1 {
    u8 pad_00[0x2];
    union { s8 s; u8 u; } unk_02;   /* accessed as both */
} S_800C0E88_1;   /* data in use_magic_ball */

typedef struct S_800C0E88_2_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800C0E88_2_pre;   /* the 0x14 bytes before object in use_magic_ball, addressed as object[-1] */

typedef struct S_800C0E88_2 {
    u8 pad_00[0x8];
    u8 unk_08;
    u8 unk_09;
    u8 pad_0A[0xA];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
} S_800C0E88_2;   /* object in use_magic_ball */

typedef struct S_800C0E88_3 {
    u8 pad_00[0x9];
    u8 unk_09;
    u8 unk_0A;
} S_800C0E88_3;   /* scan in use_magic_ball */

typedef struct S_800C0E88_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800C0E88_4;   /* tail_status in use_magic_ball */


extern void begin_mode_selected_item_action(void *object,void *unused_1,void *unused_2,void *mode);
extern s32 process_record_and_update_linked_state();
extern void clear_slot_and_update_linked_state();
extern void *get_unused_text_buffer(void);
extern u8 *expand_text_control_codes();
extern u8 * copy_selected_text_without_terminator();
extern void display_formatted_context_message(void *context);
extern void *scan_actor_along_heading();
extern void display_text_with_fullwidth_adjustment();
extern s32 find_slot_by_item_group(void *entry, s16 target);
struct DungeonItemEntry;
extern void place_actor_item(void *object_context, struct DungeonItemEntry *target);
extern void * create_actor_spell_effect();
extern s32 feed_actor_restore_mp();

extern u8 *item_category_tables[];
extern u16 magic_ball_delay[];
extern u8 D_800E1440[];
extern u8 D_800E144C[];
extern u8 D_800E1456[];
extern u8 D_800E146F[];

/* Applies data to an object, updates its slots, and handles delayed consumption. */
s32 use_magic_ball(u8 *object, u8 *data, s16 action, void *context)
{
    u8 *slot_scan;
    u8 *object_record;
    DungeonGlobalStatus *status;
    ActorRecord *current_object;
    u8 *tail_status;
    ActorRecord *active_object;
    ObjectPosition *callback;
    u8 *message_table;
    void *message_start;
    s32 slot;
    s32 scan_slot;
    s32 slot_count;
    void *message_end;
    s16 delay_timer;
    u32 flags;


    if (action == 13) {
        return process_record_and_update_linked_state(data, context);
    }

    current_object = dungeon_actor_ring_anchor;
    if (object == current_object) {
        callback = &view_reference_entity;
        data[3] |= 0x20;
        active_object = dungeon_actor_ring_anchor;
        ((PlayerRecord *)active_object)->pending_item_action = data;
        begin_mode_selected_item_action(active_object, callback, ((u8 *)(&reference_tile_object)), active_object);
        return 0;
    }

    if ((u32)object <= 0x9FFFFFFF) {
        display_actor_item_status_message(object, data);

        if (((S_800C0E88_1 *)data)->unk_02.s >= 10 && data[0] < 16) {
            slot = ((data[0] - 1) * 3) + 1;
            if ((s16)find_slot_by_item_group(object, slot) >= 0) {
                clear_slot_and_update_linked_state(data);
                tail_status = (u8 *)0x80080000;
            } else {
                message_table = item_action_definitions;
                slot_scan = object;
scan_next:
                if (slot_scan[8] == 0) {
                    flags = ((S_800C0E88_2 *)object)->unk_14;
                    if (flags & ACTOR_ELEMENT_FIRE) {
                        scan_slot = ((data[0] - 1) * 3) + 1;
                        slot_scan[8] = scan_slot;
                    } else if (flags & ACTOR_ELEMENT_WATER) {
                        scan_slot = ((data[0] - 1) * 3) + 2;
                        slot_scan[8] = scan_slot;
                    } else if (flags & ACTOR_ELEMENT_WIND) {
                        scan_slot = ((data[0] - 1) * 3) + 3;
                        slot_scan[8] = scan_slot;
                    }

                    slot_count = ((S_800C0E88_1 *)data)->unk_02.s;
                    slot_count /= 10;
                    ((S_800C0E88_3 *)slot_scan)->unk_0A = slot_count;
                    ((S_800C0E88_3 *)slot_scan)->unk_09 = slot_count;

                    if (((S_800C0E88_2 *)object)->unk_14 & 0x4000) {
                        message_start = get_unused_text_buffer();
                        message_end = append_entity_display_text(object, message_start);
                        message_end = expand_text_control_codes(D_800E1440, message_end);
                        message_end = expand_text_control_codes(
                            *(void **)(message_table + (slot_scan[8] * 20)), message_end);
                        message_end = expand_text_control_codes(D_800E144C, message_end);
                        clear_byte_and_advance(message_end);
                        display_text_with_fullwidth_adjustment(message_start);
                    }
                } else {
                    slot_scan += 3;
                    if ((s32)slot_scan < (s32)object + 9) {
                        goto scan_next;
                    }
                }
                clear_slot_and_update_linked_state(data);
                tail_status = (u8 *)0x80080000;
            }
        } else {
            if (feed_actor_restore_mp(object,
                              entity_action_selectors[object[0x13]] & 3, 0) == 0) {
                place_actor_item(object, data);
                return 1;
            }
            clear_slot_and_update_linked_state(data);
            tail_status = (u8 *)0x80080000;
        }
        tail_status += 0x3460;
        ((S_800C0E88_4 *)tail_status)->unk_0A--;
    } else if (((S_800C0E88_1 *)data)->unk_02.s == 0) {
        display_formatted_context_message(D_800E1456);
        tail_status = ((u8 *)(&g_dungeon_status));
        data[3] &= 0xDF;
        ((S_800C0E88_4 *)tail_status)->unk_0A--;
    } else {
        current_object->action_state_flags &= 0xFF7F;
        ((S_800C0E88_2 *)object)->unk_09 = 0xFF;

        slot = (data[0] - 1) * 3;
        ((S_800C0E88_2 *)object)->unk_08 = slot + 1;
        flags = *(u16 *)(item_category_tables[0] + (data[0] * 20));
        if (flags & 2) {
            ((S_800C0E88_2 *)object)->unk_08 = slot + 2;
        } else if (flags & 4) {
            ((S_800C0E88_2 *)object)->unk_08 = slot + 3;
        }

        object_record = ((S_800C0E88_2_pre *)object)[-1].unk_00;
        object = (u8 *)((u32)object & 0xDFFFFFFF);
        ((S_800C0E88_2 *)object)->unk_60 = scan_actor_along_heading(
            object, object_record[0x24], object_record[0x25], ((S_800C0E88_2 *)object)->unk_2A, 16);

        ((S_800C0E88_2 *)object)->unk_72 = abs(((S_800C0E88_2 *)object)->unk_72);
        ((S_800C0E88_2 *)object)->unk_73 = abs(((S_800C0E88_2 *)object)->unk_73);

        if (data[3] & 0x20) {
            if (create_actor_spell_effect(object, object + 8, 0,
                              ((u8 *)dungeon_actor_ring_anchor) + 0x98) == 0) {
                return 0;
            }
            magic_ball_delay[0] = 16;
            data[3] &= 0xDF;
        }

        delay_timer = magic_ball_delay[0] - 1;
        magic_ball_delay[0] = delay_timer;
        if (delay_timer >= 0) {
            return 0;
        }

        magic_ball_delay[0] = 0;
        if (get_cd_command_queue_depth() != 0) {
            return 0;
        }

        status = &g_dungeon_status;
        status->active_actor = object;
        primary_actor_record->action_state_flags |= 0x80;
        ((S_800C0E88_1 *)data)->unk_02.u--;

        message_start = get_unused_text_buffer();
        message_end = copy_selected_text_without_terminator(data, message_start);
        message_end = expand_text_control_codes(D_800E146F, message_end);
        clear_byte_and_advance(message_end);
        display_text_with_fullwidth_adjustment(message_start);
        (*(u16 *)&status->activity_counts.parts.pending_action_count)--;
    }
    return 1;
}
