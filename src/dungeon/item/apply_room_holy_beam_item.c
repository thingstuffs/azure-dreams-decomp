#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


typedef struct {
    u8 pad[0xC];
    u16 flags;
    u8 pad_E[6];
} DungeonRecord;

extern u8 D_800E12D6[];
extern u8 D_800E1303[];

extern void begin_mode_selected_item_action(s8 *object, s32 unused_1, s32 unused_2, s32 mode);
extern s32 process_record_and_update_linked_state(s32, s32);
extern void clear_slot_and_update_linked_state(s32);
extern s32 get_unused_text_buffer(void);
extern s32 expand_text_control_codes(u8 *src, u8 *dst);
extern void func_80099290(s8 *byte_ptr);
extern void display_formatted_context_message(void *);
extern void display_text_with_fullwidth_adjustment(s8 *text);
extern void apply_item_effect_at_entity_position(void *, s32);
extern void display_actor_item_status_message(void *, s32, s16);
extern s32 apply_actor_food_preference(void *, s32, s32);
extern void create_view_color_flash(s32, s16);
extern s32 create_timed_region_flag_expiry(s32 unused0, s32 unused1, s32 unused2, s16 payloadValueA, s16 payloadValueC);


typedef struct S_800BF7FC_0_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_800BF7FC_0_pre;   /* the 0x14 bytes before arg0 in apply_room_holy_beam_item, addressed as arg0[-1] */


typedef struct S_800BF7FC_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800BF7FC_1;   /* obj in apply_room_holy_beam_item */

/* Handles an item action for a target and updates dungeon record flags. */
s32 apply_room_holy_beam_item(void *target, u8 *item, s16 action, s32 action_param)
{
    DungeonRecord *record;
    u8 *record_obj;
    s32 random_value;
    s32 event_value;
    s8 record_index;

    if (action == 13) {
        return process_record_and_update_linked_state((s32)item, action_param);
    }

    if (target == ((u8 *)D_800E3D7C)) {
        ((EntityRec *)target)->unk_110 = (s32)item;
        begin_mode_selected_item_action(target, ((u8 *)(&D_80083780)), ((u8 *)(&D_80082E80)), target);
        return 0;
    }

    if ((u32)target <= 0x9FFFFFFF) {
        display_actor_item_status_message(target, (s32)item, action);
        if (apply_actor_food_preference(target,
                          entity_action_selectors[(*(u8 *)((u8 *)&((EntityRec *)target)->unk_10 + 3))] & 3,
                          (s32)item) == 0) {
            apply_item_effect_at_entity_position(target, (s32)item);
            return 1;
        }
    } else {
        record_obj = ((S_800BF7FC_0_pre *)target)[-1].unk_00;
        record_index = ((S_800BF7FC_1 *)record_obj)->unk_26;
        if (record_index >= 0 && !(D_800E2970[record_index].flags & 2)) {
            if (create_timed_region_flag_expiry(((S_800BF7FC_1 *)record_obj)->unk_24,
                              ((S_800BF7FC_1 *)record_obj)->unk_25,
                              ((EntityRec *)target)->unk_88,
                              item[0], record_index) == 0) {
                return 0;
            }

            record = &D_800E2970[((S_800BF7FC_1 *)record_obj)->unk_26];
            record->flags |= 2;
            create_view_color_flash(0x20C0C0, 1);
            random_value = get_unused_text_buffer();
            event_value = random_value;
            random_value = expand_text_control_codes(D_800E12D6, random_value);
            func_80099290(random_value);
            display_text_with_fullwidth_adjustment(event_value);
        } else {
            display_formatted_context_message(D_800E1303);
        }
    }

    g_dungeon_status.activity_counts.parts.pending_action_count--;
    clear_slot_and_update_linked_state((s32)item);
    return 1;
}
