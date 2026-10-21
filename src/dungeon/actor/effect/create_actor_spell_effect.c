#include "common.h"
#include "shared/def_table.h"
#include "shared/sys_flags.h"
#include "shared/object_node.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

typedef struct S_800A94A0_0 {
    void * unk_00;
    void * unk_04;
    u8 pad_08[0x23];
    u8 unk_2B;
    u8 pad_2C[0x4C];
    void * unk_78;
    u8 pad_7C[0x24];
    s16 unk_A0;
} S_800A94A0_0;   /* arg0 in create_actor_spell_effect; pointer addresses record offset 0x18 */


typedef struct S_800A94A0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s32 unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
    void * unk_20;
} S_800A94A0_2;

typedef struct S_800A94A0_3 {
    u8 pad_00[0x4];
    void * unk_04;
    u8 unk_08;
    u8 unk_09;
} S_800A94A0_3;





typedef struct S_800A94A0_6 {
    s32 unk_00;
} S_800A94A0_6;   /* Pointer addresses record offset 0x14. */

typedef struct S_800A94A0_7 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_800A94A0_7;

typedef struct S_800A94A0_8 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_800A94A0_8;

typedef struct S_800A94A0_9 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_800A94A0_9;   /* *D_800E3D7C in create_actor_spell_effect */


extern u8 D_800E3CC8[];
extern u16 direction_x_offsets[];
extern u16 direction_y_offsets[];

void *allocate_list_node();
s32 func_80069EF8(void);
s32 get_unused_text_buffer();
s32 expand_text_control_codes();
void *func_80099290();
s32 append_entity_display_text();
s16 get_tile_chebyshev_distance();
s32 display_text_with_fullwidth_adjustment();
s16 resolve_alternate_spell_id();
s32 load_spell_effect_code();
s32 select_nearby_target_and_initialize_slot();
void setup_object_within_planar_range();
void process_nearby_object_midpoint();
void spend_actor_mp();
extern M2C_UNK D_80089080;
extern u8 D_800DD880[];
extern u8 D_800DD8B4[];
extern M2C_UNK D_800E1C58;
extern u8 current_spell_effect_variant;

/* Creates an effect for an actor, sets its position and scale, and builds its message. */
void *create_actor_spell_effect(void *actor, EntityRec *effect_record, s16 mode, void *context) {
    s32 message;
    s32 name_text;
    s32 effect_data;
    s32 text_context;
    s32 new_text_context;
    s32 direction_offset;
    s32 effect_mode;
    u16 effect_flags;
    s32 global_flags;
    u8 variant;
    s16 effect_id;
    MovingPosition *effect_position;
    S_800A94A0_7 *actor_state;
    void *effect;
    S_800A94A0_3 *effect_state;
    void *linked_object;
    MovingPosition *actor_position;
    TileObject *map_state;

    actor_state = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_04;
    effect = allocate_list_node(0x12, ((u8 *)(&scene_object_list_anchor)));
    if (effect != NULL) {
        effect_mode = ((s32) mode << 0x10) >> 0x10;
        {
            s32 mode_arg = effect_mode;
            u8 entry_variant;
            effect_id = (*(u8 *)&effect_record->x);
            entry_variant = (*(u8 *)((u8 *)&effect_record->x + 1));
            current_spell_effect_variant = entry_variant;
            effect_data = load_spell_effect_code((u8) effect_id, mode_arg, ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_2B);
        }
        if (effect_data == 0) {
            effect_flags = ((S_800A94A0_2 *)effect)->unk_1E | 0x8000;
            global_flags = object_flag_block.flags | 0x8000;
            ((S_800A94A0_2 *)effect)->unk_1E = effect_flags;
            object_flag_block.flags = global_flags;
            return NULL;
        }
        ((S_800A94A0_2 *)effect)->unk_10 = effect_data;
        effect_state = effect + 0x20;
        ((S_800A94A0_2 *)effect)->unk_20 = actor;
        effect_state->unk_04 = context;
        effect_state->unk_08 = effect_id;
        D_800E3CC8[0] = effect_id;
        variant = (*(u8 *)((u8 *)&effect_record->x + 1));
        effect_state->unk_09 = variant;
        D_800E3CC8[1] = variant;
        if (mode == 0) {
            actor_position = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_00;
            effect_position = ((S_800A94A0_2 *)effect)->unk_08;
            effect_position->unk_02 = (u16) actor_position->unk_02;
            effect_position->unk_06 = (u16) actor_position->unk_06;
            effect_position->unk_0A = (u16) actor_position->unk_0A;
            text_context = func_80069EF8();
            if (!((u16) *((s16 *)&system_update_flags) & 1)) {
                linked_object = ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_78;
                if (linked_object != NULL) {
                    get_tile_chebyshev_distance(((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_04,
                        ((S_800A94A0_6 *)((u8 *)linked_object - 0x14))->unk_00);
                    select_nearby_target_and_initialize_slot(effect, effect_position, 8, 0x300);
                } else {
                    select_nearby_target_and_initialize_slot(effect, effect_position, 8, 0x300);
                }
            } else {
                select_nearby_target_and_initialize_slot(effect, effect_position, 8, 0x300);
            }
            if (text_context) {
                /* retail evidence: the test's operands survive (the arm compiled away); reconstructed as a conditional update of a local nothing reads in the retail build - any dead local set reproduces the bytes (lane r118_fable_f4; decision 45, docs/evidence/r97_decisions.md) */
                effect_mode = 0;
            }
        } else {
            map_state = &reference_tile_object;
            if (!(actor_state->unk_14 & 0x8000)) {
                if (!(map_state->sprite_flags & 0x8000)) {
                    process_nearby_object_midpoint(map_state, actor_state, ((S_800A94A0_9 *)(((u8 *)dungeon_actor_ring_anchor)))->unk_88,
                        ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_A0, 8, 0x300);
                    goto set_effect_scale;
                }
            }
            direction_offset = ((u16) ((S_800A94A0_9 *)(((u8 *)dungeon_actor_ring_anchor)))->unk_2A >> 8) & 0xE;
            setup_object_within_planar_range(actor - 0x20, (map_state->tile_position.parts.tile_x << 6) + ((s32) (*(u16 *)((u8 *)direction_x_offsets + direction_offset)
                << 0x10) >> 0x11) + 0x20, (map_state->tile_position.parts.tile_y << 6) + ((s32) (*(u16 *)((u8 *)direction_y_offsets
                + direction_offset) << 0x10) >> 0x11) + 0x20, ((S_800A94A0_9 *)(((u8 *)dungeon_actor_ring_anchor)))->unk_88, 8, 0x300);
        }
set_effect_scale:
        if ((mode << 0x10) != 0) {
            spend_actor_mp(actor, D_800DD8B4[effect_id] << 6);
        } else {
            spend_actor_mp(actor, D_800DD880[effect_id] << 8);
        }
        if ((effect != NULL) && ((s8) ((S_800A94A0_0 *)((u8 *)actor - 0x18))->unk_2B > 0)) {
            new_text_context = get_unused_text_buffer();
            message = append_entity_display_text(actor, new_text_context);
            message = expand_text_control_codes(&D_800E1C58, message);
            if (((u32)(u16)mode << 0x10) != 0) {
                effect_id = resolve_alternate_spell_id(effect_id);
                name_text = item_action_definitions[effect_id].unk_08;
                message = expand_text_control_codes(name_text, message);
            } else {
                name_text = item_action_definitions[effect_id].unk_00;
                message = expand_text_control_codes(name_text, message);
            }
            func_80099290(expand_text_control_codes(&D_80089080, message));
            display_text_with_fullwidth_adjustment(new_text_context);
            return effect;
        }
    }
    return effect;
}
