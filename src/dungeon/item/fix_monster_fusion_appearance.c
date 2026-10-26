#include "shared/monster_ids.h"
#include "dungeon/item/message.h"

struct ObjectNodeHeader;
#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


#include "dungeon/player/item.h"
#include "dungeon/system.h"
void clear_slot_and_update_linked_state();
void *get_unused_text_buffer(void);
u8 * append_typed_formatted_value();
void adjust_source_value_and_finalize(void *context, const void *source);
s32 display_text_with_fullwidth_adjustment();
void place_actor_item(void *object_context, void *target);
s32 feed_actor_restore_mp();
void create_colored_effect_with_event(struct ObjectNodeHeader *source, s32 color, unsigned short event_id);

extern u8 D_8008935C[];
extern u8 D_800E0FF4[];
extern u8 D_800E100F[];


typedef struct S_800BE120_0 {
    u8 pad_00[0x13];
    u8 unk_13;
    u32 unk_14;
    u8 pad_18[0x30];
    union {
        struct { s32 v; } at00;
        struct { u8 v; } at00u;
        struct { u8 pad[0x1]; u8 v; } at01;
        struct { u8 pad[0x2]; u8 v; } at02;
        struct { u8 pad[0x3]; u8 v; } at03;
    } unk_48;   /* overlapping accesses */
    u8 pad_4C[0x8];
    u32 unk_54;
    u8 pad_58[0xB8];
    s32 unk_110;
} S_800BE120_0;   /* arg0 in fix_monster_fusion_appearance */

typedef struct S_800BE120_1 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
    u8 unk_03;
} S_800BE120_1;   /* arg1 in fix_monster_fusion_appearance */

/* Applies data to an entity and handles the resulting update or fallback. */
s32 fix_monster_fusion_appearance(void *entity, S_800BE120_1 *data, s16 mode) {
    s16 stored;
    void *call_entity;
    void *context_arg;
    s32 new_context;
    void *text_cursor;
    void *context;

    stored = 0;
    if (entity == dungeon_actor_ring_anchor) {
        ((S_800BE120_0 *)entity)->unk_110 = (s32)data;
        begin_deferred_item_action(entity, &view_reference_entity.x.v, &reference_tile_object.frame_entry, entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, data, mode);
        /*
         * BUG: Frog species 0x2E passes this restriction even when the saved species is Hikewne. Ovum can then
         * make that Hikewne survive fusion despite its normal absorption rule.
         * Found and documented by the Azure Dreams community
         * (adrando.com/guide/bugs.html).
         */
        if (((S_800BE120_0 *)entity)->unk_13 >= MONSTER_KEWNE) {
            if (!(((S_800BE120_0 *)entity)->unk_54 & 0x800000)) {
                if (((S_800BE120_0 *)entity)->unk_48.at01.v == 0) {
                    if (feed_actor_restore_mp(entity,
                            (entity_action_selectors[((S_800BE120_0 *)entity)->unk_13] >> 6) & 3,
                            0) == 0) {
                        place_actor_item(entity, data);
                        return 1;
                    }
                    ((S_800BE120_0 *)entity)->unk_48.at00.v = *(s32 *)data;
                    ((S_800BE120_0 *)entity)->unk_48.at00u.v = data->unk_00;
                    ((S_800BE120_0 *)entity)->unk_48.at01.v = data->unk_01;
                    ((S_800BE120_0 *)entity)->unk_48.at02.v = data->unk_02;
                    ((S_800BE120_0 *)entity)->unk_48.at03.v = data->unk_03;
                    ((S_800BE120_0 *)entity)->unk_54 |= 0x800000;
                    create_colored_effect_with_event((s8 *)entity - 0x20, 0x20A0A0, 0x702);
                    stored = 1;
                    if (((S_800BE120_0 *)entity)->unk_14 & 0x4000) {
                        adjust_source_value_and_finalize(entity, D_800E0FF4);
                    }
                }
            }
        }
    }

    new_context = stored;
    if (new_context == 0 &&
        ((((S_800BE120_0 *)entity)->unk_13 < MONSTER_KEWNE) ||
         (((S_800BE120_0 *)entity)->unk_54 & 0x800000) ||
         (((S_800BE120_0 *)entity)->unk_48.at01.v != 0))) {
        text_cursor = get_unused_text_buffer();
        call_entity = entity;
        context_arg = text_cursor;
        context = context_arg;
        text_cursor = append_entity_display_text(call_entity, context_arg);
        clear_byte_and_advance(expand_text_control_codes(D_8008935C, append_typed_formatted_value(data, expand_text_control_codes(D_800E100F, text_cursor))));
        display_text_with_fullwidth_adjustment(context);
        place_actor_item(entity, data);
        return 1;
    }
    clear_slot_and_update_linked_state(data);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    return 1;
}
