#include "shared/entity_action_selectors.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"


void begin_deferred_item_action();
void clear_slot_and_update_linked_state();
s32 get_unused_text_buffer(void);
s32 expand_text_control_codes();
void *func_80099290();
s32 append_typed_formatted_value();
s32 append_entity_display_text();
void adjust_source_value_and_finalize();
s32 display_text_with_fullwidth_adjustment();
void apply_item_effect_at_entity_position();
void display_item_status_message();
s32 apply_actor_food_preference();
void create_colored_effect_with_event();

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
    u32 context_arg;
    s32 new_context;
    s32 context;

    stored = 0;
    if (entity == ((s32)D_800E3D7C)) {
        ((S_800BE120_0 *)entity)->unk_110 = (s32)data;
        begin_deferred_item_action(entity, &D_80083780.x.v, &D_80082E80.unk_000, entity);
        return 0;
    }

    if ((u32)entity <= 0x9FFFFFFFU) {
        display_item_status_message(entity, data, mode);
        if (((S_800BE120_0 *)entity)->unk_13 >= 2) {
            if (!(((S_800BE120_0 *)entity)->unk_54 & 0x800000)) {
                if (((S_800BE120_0 *)entity)->unk_48.at01.v == 0) {
                    if (apply_actor_food_preference(entity,
                            (entity_action_selectors[((S_800BE120_0 *)entity)->unk_13] >> 6) & 3,
                            0) == 0) {
                        apply_item_effect_at_entity_position(entity, data);
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
        ((((S_800BE120_0 *)entity)->unk_13 < 2) ||
         (((S_800BE120_0 *)entity)->unk_54 & 0x800000) ||
         (((S_800BE120_0 *)entity)->unk_48.at01.v != 0))) {
        new_context = get_unused_text_buffer();
        call_entity = entity;
        context_arg = new_context;
        context = context_arg;
        new_context = append_entity_display_text((s32)call_entity, context_arg);
        func_80099290(expand_text_control_codes(D_8008935C, append_typed_formatted_value(data, expand_text_control_codes(D_800E100F, new_context))));
        display_text_with_fullwidth_adjustment(context);
        apply_item_effect_at_entity_position(entity, data);
        return 1;
    }
    clear_slot_and_update_linked_state(data);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
    return 1;
}
