#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_800AB778_19 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_19;   /* page4 in advance_actor_removal */

typedef struct S_800AB778_20 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_20;   /* page16 in advance_actor_removal */

typedef struct S_800AB778_21 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x60];
    s32 unk_110;
} S_800AB778_21;   /* ((Rec_D_800E3D7C *)(&D_800E3D7C))->unk_00.at00_pv.v in advance_actor_removal */

typedef struct S_800AB778_22 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_22;   /* ((S_800AB778_19 *)page4)->unk_3D7C in advance_actor_removal */

typedef struct S_800AB778_23 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_23;   /* ((S_800AB778_20 *)page16)->unk_3D7C in advance_actor_removal */

typedef struct S_800AB778_24 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AB778_24;   /* ((S_800AB778_22 *)(((S_800AB778_19 *)page4)->unk_3D7C))->unk_110 in advance_actor_removal */

typedef struct S_800AB778_25 {
    u8 pad_00[0x3];
    u8 unk_03;
} S_800AB778_25;   /* ((S_800AB778_23 *)(((S_800AB778_20 *)page16)->unk_3D7C))->unk_110 in advance_actor_removal */

typedef struct S_800AB778_0_pre {
    u16 unk_00;
} S_800AB778_0_pre;   /* the 0x2 bytes before arg3 in advance_actor_removal, addressed as arg3[-1] */

typedef struct S_800AB778_1 {
    u8 pad_00[0x96];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800AB778_1;   /* arg0 in advance_actor_removal */

typedef struct S_800AB778_3 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    u8 unk_24;
    u8 unk_25;
} S_800AB778_3;   /* arg2 in advance_actor_removal */

typedef struct S_800AB778_6 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800AB778_6;

typedef struct S_800AB778_7 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800AB778_7;

typedef struct S_800AB778_8 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_8;   /* page4 in advance_actor_removal */

typedef struct S_800AB778_9 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_9;   /* page_obj4 in advance_actor_removal */

typedef struct S_800AB778_10 {
    s32 unk_00;
} S_800AB778_10;   /* &D_800814A0 in advance_actor_removal */

typedef struct S_800AB778_12 {
    u8 pad_00[0xAC];
    s32 unk_AC;
    u8 pad_B0[0x20];
    s32 unk_D0;
} S_800AB778_12;

typedef struct S_800AB778_13 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_800AB778_13;

typedef struct S_800AB778_14 {
    u8 pad_00[0x3D7C];
    void * unk_3D7C;
} S_800AB778_14;   /* page16 in advance_actor_removal */

typedef struct S_800AB778_15 {
    u8 pad_00[0x110];
    void * unk_110;
} S_800AB778_15;   /* page_obj16 in advance_actor_removal */

typedef struct S_800AB778_16 {
    s32 unk_00;
} S_800AB778_16;   /* global16 in advance_actor_removal */

typedef struct {
    u8 pad00[0x13];
    s8 field13;
    u8 pad14[0x78];
} D_800E3E48_Entry;

void build_entity_slot_snapshot();
s32 get_entity_effect_value();
s32 get_entity_class();
void clear_player_linked_action_flags();
void clear_slot_and_update_linked_state();
s32 get_unused_text_buffer();
s32 expand_text_control_codes();
void *func_80099290();
s32 write_text_byte_and_advance();
s32 append_entity_display_text();
void adjust_source_value_and_finalize();
void unlink_entity_node();
void update_map_cell_flags_with_item_limit();
void decrement_monster_entry_count();
s16 find_entity_slot_by_field_ac();
s32 has_pending_action_or_turn_count();
void func_800A31D0();
s32 display_text_with_fullwidth_adjustment();
void begin_actor_flagged_action();
void *create_orbiting_teleport_effect();
extern s32 D_800814A0;
extern s16 D_800DCE68;
extern s16 D_800DCED4[];
extern M2C_UNK D_800E0C34;
extern M2C_UNK D_800E0C58;
extern M2C_UNK D_800E0C67;
extern void *D_800E3DF0[];
extern D_800E3E48_Entry D_800E3E48[];

/* Advance actor removal, updating its visual effects and clearing its references. */
s32 advance_actor_removal(S_800AB778_1 *state, void *unused_context, S_800AB778_3 *visual, void *actor) {
    s32 effect_flags;
    s16 actor_slot16;
    s16 fade_ticks;
    s32 actor_slot4;
    s32 object_id16;
    s32 object_id4;
    s32 event_arg;
    s32 actor_flags;
    s32 event_source;
    u16 scale_x;
    u16 scale_y;
    u16 state4_count;
    u16 state16_count;
    s32 actor_type;
    u8 state_or_type;
    u8 effect_x;
    u8 effect_y;
    void **object_slot16;
    void **object_slot4;
    S_800AB778_12 *actor_entry16;
    S_800AB778_6 *actor_entry4;
    s16 template_index;
    u32 template_base;
    S_800AB778_8 *globals_page4;
    S_800AB778_14 *globals_page16;
    S_800AB778_9 *globals4;
    S_800AB778_15 *globals16;
    s32 *update_flags;
    s32 state4_owner;
    s32 effect_actor_flags;
    void *state4_event;
    register s32 state4_result;
    s32 flags_mask;

    actor_flags = ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v;
    if (actor_flags & 0x20000000) {
        ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v = actor_flags | 0x400000;
        begin_actor_flagged_action(state, unused_context, visual, actor);
        return 0;
    }

    state_or_type = state->unk_9B;
    switch (state_or_type) {
    case 0:
    {
        register s32 next_state;

        if (((Rec_D_80082E80 *)actor)->unk_43 != 0xFD) {
            if ((has_pending_action_or_turn_count(actor) << 0x10) != 0) {
                break;
            }
        } else {
            ((S_800AB778_21 *)((*(void * *)&((EntityRec *)(((s32 *)&D_800E3D7C)))->x)))->unk_110 = 0;
        }
        g_dungeon_status.unk_0A++;
        next_state = 3;
        state->unk_9B = next_state;
        break;
    }

    case 3:
        if (((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v & 0x80000) {
            clear_player_linked_action_flags();
        }
        if (((Rec_D_80082E80 *)actor)->unk_43 < 0x40U) {
            s32 event_index;
            s32 event_mode;

            event_index = get_entity_class(actor);
            state4_event = actor;
            event_mode = 2;
            create_orbiting_teleport_effect(state4_event,
                D_800DCED4[event_index],
                (s32)state4_event
                    == ((S_800AB778_21 *)((*(void * *)&((EntityRec *)(((s32 *)&D_800E3D7C)))->x)))->unk_AC,
                    event_mode);
            state->unk_96.s = 0;
            state->unk_9B = 0x10;
            break;
        }
        if (((SpriteFrameState *)visual)->clut == 0) {
            ((SpriteFrameState *)visual)->clut = 0xFF80U;
        }
        ((SpriteFrameState *)visual)->tpage_abr = 0x20;
        ((SpriteFrameState *)visual)->flags |= 0xC;
        state->unk_96.s = 0x10;
        ((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v |= 0x10000000;
        state->unk_9B++;
        break;

    case 4:
        ((SpriteFrameState *)visual)->color.c.r -=
            (s32)((SpriteFrameState *)visual)->color.c.r / state->unk_96.s;
        ((SpriteFrameState *)visual)->color.c.g -=
            (s32)((SpriteFrameState *)visual)->color.c.g / state->unk_96.s;
        ((SpriteFrameState *)visual)->color.c.b -=
            (s32)((SpriteFrameState *)visual)->color.c.b / state->unk_96.s;
        scale_x = ((SpriteFrameState *)visual)->scale_x;
        ((SpriteFrameState *)visual)->scale_x = scale_x +
            ((s32)(0x400 - scale_x) / state->unk_96.s);
        scale_y = ((SpriteFrameState *)visual)->scale_y;
        ((SpriteFrameState *)visual)->scale_y = scale_y +
            ((s32)(0x400 - scale_y) / state->unk_96.s);
        fade_ticks = state->unk_96.u - 1;
        state->unk_96.s = fade_ticks;
        if (((fade_ticks << 0x10) > 0) &&
            !(((SpriteFrameState *)visual)->flags & 0x8000)) {
            return 0;
        }
        event_source = get_unused_text_buffer();
        event_arg = write_text_byte_and_advance(8, event_source);
        state_or_type = ((Rec_D_80082E80 *)actor)->unk_43;
        if (state_or_type == 0xFF) {
            state4_result = append_entity_display_text(actor, event_arg);
            state4_event = &D_800E0C58;
            func_80099290(expand_text_control_codes(state4_event, state4_result));
            display_text_with_fullwidth_adjustment(event_source);
        } else if (state_or_type == 0xFE) {
            state4_result = append_entity_display_text(actor, event_arg);
            state4_event = &D_800E0C67;
            func_80099290(expand_text_control_codes(state4_event, state4_result));
            display_text_with_fullwidth_adjustment(event_source);
        } else {
            u16 *state4_global;

            state4_global = (u16 *)&D_800DCE68;
            (*state4_global)--;
            g_dungeon_status.unk_0A--;
        }
        func_800A31D0(actor);
        actor_slot4 = find_entity_slot_by_field_ac(actor);
        if (actor_slot4 >= 0) {
            void *actor_base4;

            actor_base4 = (*(void * *)&((EntityRec *)(((s32 *)&D_800E3D7C)))->x);
            actor_entry4 = (void *)((actor_slot4 * 4) + (s32)actor_base4);
            actor_entry4->unk_AC = 0;
            actor_entry4->unk_D0 = 0;
        }
        globals_page4 = (void *)0x800E0000;
        if (((S_800AB778_22 *)(((S_800AB778_19 *)globals_page4)->unk_3D7C))->unk_110 != NULL) {
            decrement_monster_entry_count(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 3);
            object_id4 =
                ((S_800AB778_24 *)(((S_800AB778_22 *)(((S_800AB778_19 *)globals_page4)->unk_3D7C))->unk_110))->unk_03 & 0x1F;
            object_slot4 = &D_800E3DF0[object_id4];
            ((S_800AB778_7 *)(*object_slot4))->unk_13 = 0;
            D_800E3E48[object_id4].field13 = 0;
            globals4 = globals_page4->unk_3D7C;
            *object_slot4 = NULL;
            clear_slot_and_update_linked_state(globals4->unk_110);
        } else {
            decrement_monster_entry_count(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 2);
        }
        if ((get_entity_effect_value(actor, 0x1B) << 0x10) == 0) {
            effect_actor_flags = ((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v;
            effect_x = ((SpriteFrameState *)visual)->unk_24;
            effect_y = ((SpriteFrameState *)visual)->unk_25;
            effect_flags = 0x3000;
            if (effect_actor_flags & 0x2000) {
                effect_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(effect_x, effect_y, effect_flags);
        }
        unlink_entity_node(actor);
        ((S_800AB778_0_pre *)actor)[-1].unk_00 |= 0x8000;
        ((S_800AB778_10 *)(&D_800814A0))->unk_00 |= 0x8000;
        state4_count = ((u16)g_dungeon_status.unk_0A);
        state4_owner = ((s32)g_dungeon_status.unk_0C);
        state4_count--;
        g_dungeon_status.unk_0A = state4_count;
        if (state4_owner == (s32)actor) {
            g_dungeon_status.unk_0C = 0;
            return 0;
        }
        return 0;

    case 16:
        ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v = actor_flags | 0x4000;
        flags_mask = actor_flags & 0x4000;
        adjust_source_value_and_finalize(actor, &D_800E0C34);
        if (flags_mask == 0) {
            ((Rec_D_80082E80 *)actor)->unk_14.at00_s32.v &= ~0x4000;
        }
        func_800A31D0(actor);
        actor_type = ((Rec_D_80082E80 *)actor)->unk_43;
        ((Rec_D_80082E80 *)actor)->unk_44 = 0;
        if ((get_entity_effect_value(actor, 0xA) << 0x10) != 0) {
            ((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v = ((Rec_D_80082E80 *)actor)->unk_A8;
        }
        template_base = 0x80010A80;
        template_index = actor_type;
        build_entity_slot_snapshot(&((u8 *)template_base)[template_index * 0x54], actor);
        decrement_monster_entry_count(((Rec_D_80082E80 *)actor)->unk_12.at01_u8.v, 3);
        actor_slot16 = find_entity_slot_by_field_ac(actor);
        if (actor_slot16 >= 0) {
            void *actor_base16;

            actor_base16 = (*(void * *)&((EntityRec *)(((s32 *)&D_800E3D7C)))->x);
            actor_entry16 = (void *)((actor_slot16 * 4) + (s32)actor_base16);
            actor_entry16->unk_AC = 0;
            actor_entry16->unk_D0 = 0;
        }
        globals_page16 = (void *)0x800E0000;
        object_id16 =
            ((S_800AB778_25 *)(((S_800AB778_23 *)(((S_800AB778_20 *)globals_page16)->unk_3D7C))->unk_110))->unk_03 & 0x1F;
        object_slot16 = &D_800E3DF0[object_id16];
        ((S_800AB778_13 *)(*object_slot16))->unk_13 = 0;
        D_800E3E48[object_id16].field13 = 0;
        globals16 = globals_page16->unk_3D7C;
        *object_slot16 = NULL;
        clear_slot_and_update_linked_state(globals16->unk_110);
        if ((get_entity_effect_value(actor, 0x1B) << 0x10) == 0) {
            effect_actor_flags = ((Rec_D_80082E80 *)actor)->unk_1C.at00_s32.v;
            effect_x = ((SpriteFrameState *)visual)->unk_24;
            effect_y = ((SpriteFrameState *)visual)->unk_25;
            effect_flags = 0x3000;
            if (effect_actor_flags & 0x2000) {
                effect_flags = 0x300;
            }
            update_map_cell_flags_with_item_limit(effect_x, effect_y, effect_flags);
        }
        unlink_entity_node(actor);
        update_flags = (s32 *)&D_800814A0;
        ((S_800AB778_0_pre *)actor)[-1].unk_00 |= 0x8000;
        ((S_800AB778_16 *)update_flags)->unk_00 |= 0x8000;
        state16_count = ((u16)g_dungeon_status.unk_0A);
        state16_count--;
        g_dungeon_status.unk_0A = state16_count;
    }
    return 0;
}
