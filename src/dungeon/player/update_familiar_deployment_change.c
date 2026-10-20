#include "shared/dungeon_actor_callbacks.h"
#include "common.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/dungeon_moving_views.h"

/* cfail-repair: tf7-phase1-cache-v3 */
s32 Control_CD(); /* extern */
void func_800424E0();          /* extern */
void func_80042560();                      /* extern */
M2C_UNK func_80042640();                  /* extern */
void runtime_map_type_16_entry_code();                      /* extern */
M2C_UNK register_and_upload_sprite_resource();                     /* extern */
s32 begin_sprite_resource_load_with_completion_flag();                   /* extern */
void set_sprite_animation_frame(); /* extern */
void create_familiar_deployment_effect_with_owner_state();      /* extern */
void create_familiar_deployment_overlay();      /* extern */
void store_recalled_familiar(); /* extern */
s32 get_unused_text_buffer();                         /* extern */
s32 expand_text_control_codes();                  /* extern */
void *func_80099290();                         /* extern */
s32 write_text_byte_and_advance();                    /* extern */
s32 append_entity_display_text();                     /* extern */
void process_unflagged_linked_entries();                         /* extern */
void process_unflagged_linked_entries_alt();                         /* extern */
void unlink_entity_node();                      /* extern */
void *(*load_monster_resource_data())(M2C_UNK, s8, s8, s16); /* extern */
s32 retain_spawn_resource();                 /* extern */
s32 find_or_retain_sprite_resource_slot();                     /* extern */
void decrement_monster_entry_count();                 /* extern */
s32 has_pending_dungeon_activity();                         /* extern */
void func_800A31D0();                      /* extern */
s32 play_sound_if_enabled();                     /* extern */
s32 display_text_with_fullwidth_adjustment();                         /* extern */
extern s32 D_80081488;
extern M2C_UNK D_8008149C;
extern void *D_80082EB0[];
extern u8 D_800DD138[];
extern u8 D_800DD140[];
extern u8 D_800DD260;
extern M2C_UNK D_800DD262;
extern M2C_UNK D_800E05E1;
extern M2C_UNK D_800E05F0;
extern M2C_UNK D_800E06FA;
extern M2C_UNK D_800E0714;
extern s32 D_800E3D74[];
extern void *D_800E3DF0[];
extern s8 D_800E3E40;

typedef union ScratchS1 {
    s32 value;
    void **base;
} ScratchS1;


typedef struct S_8009345C_0 {
    u8 pad_00[0x8C];
    M2C_UNK * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
} S_8009345C_0;   /* actor in update_familiar_deployment_change */

typedef struct S_8009345C_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8009345C_1;   /* entity in update_familiar_deployment_change */

typedef struct S_8009345C_2 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x30];
    s32 unk_5C;
    void * unk_60;
    u8 pad_64[0xE];
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x14];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_8009345C_2;   /* ctx in update_familiar_deployment_change */

typedef struct S_8009345C_3 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8009345C_3;

typedef struct S_8009345C_4 {
    union { u16 u; s16 s; } unk_00;   /* accessed as both */
} S_8009345C_4;   /* &D_800DD262 in update_familiar_deployment_change */

typedef struct S_8009345C_5_pre {
    u16 unk_00;
} S_8009345C_5_pre;   /* 0x2-byte header immediately before the payload. */

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

typedef struct S_8009345C_10 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_8009345C_10;

typedef struct S_8009345C_11 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_8009345C_11;

typedef struct S_8009345C_12 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_8009345C_12;

   /* map in update_familiar_deployment_change */

typedef struct S_8009345C_14 {
    u8 pad_00[0xD0];
    void * unk_D0;
} S_8009345C_14;

typedef struct S_8009345C_15 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
} S_8009345C_15;   /* ((S_8009345C_2 *)ctx)->unk_60 in update_familiar_deployment_change */

typedef struct S_8009345C_16 {
    u8 pad_00[0xAC];
    s32 unk_AC;
} S_8009345C_16;   /* ((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor) in update_familiar_deployment_change */

/* Advances the object replacement sequence, including animation, messages, and cleanup. */
void update_familiar_deployment_change(void *actor, MovingPosition *map, void *entity, void *context) {

    M2C_UNK *remove_text;
    M2C_UNK *create_text;
    s32 remove_message;
    s32 load_id;
    s32 create_id;
    s32 object_flags;
    s32 cleanup_slot;
    s32 create_message;
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
    void *removed_object;
    void *object_scale;
    void *object_position;
    ScratchS1 message_or_list;

    state = ((S_8009345C_0 *)actor)->unk_9B;
    switch (state) {
    case 0:
        if (!(((S_8009345C_1 *)entity)->unk_14 & 0x6000)) {
            return;
        }
        (*(void **)((u8 *)entity + (0x2C))) = D_800DD138;
        set_sprite_animation_frame(entity, D_800DD138[((s32) (g_game_work.view.viewAngle + ((S_8009345C_2 *)context)->unk_2A + 0x100)
            >> 9) & 7], 0, 1);
        create_familiar_deployment_effect_with_owner_state(actor, map, entity);
        create_familiar_deployment_overlay(actor, map, entity);
        entity_flags = ((S_8009345C_1 *)entity)->unk_14;
        D_800DD260 = 0;
        ((S_8009345C_1 *)entity)->unk_14 = (u16) (entity_flags | 0x200);
        ((S_8009345C_0 *)actor)->unk_96 = 0x10U;
        selected_slot = ((S_8009345C_2 *)context)->unk_8A.s;
        slot_bits = ((S_8009345C_2 *)context)->unk_8A.u;
        selected_object = (void *) ((S_8009345C_3 *)(((selected_slot * 4) + actor)))->unk_AC;
        ((S_8009345C_4 *)(&D_800DD262))->unk_00.u = slot_bits;
        ((S_8009345C_2 *)context)->unk_60 = selected_object;
        ((S_8009345C_0 *)actor)->unk_9B++;
        return;
    case 1:
        start_ticks = ((S_8009345C_0 *)actor)->unk_96 - 1;
        ((S_8009345C_0 *)actor)->unk_96 = start_ticks;
        if ((start_ticks << 0x10) > 0) {
            return;
        }
        if (((S_8009345C_2 *)context)->unk_60 != NULL) {
            store_recalled_familiar(actor, map, entity, context);
            ((S_8009345C_0 *)actor)->unk_9B++;
            return;
        }
        next_state = ((S_8009345C_0 *)actor)->unk_9B + 2;
        break;
    case 2:
        if (!(((S_8009345C_15 *)(((S_8009345C_2 *)context)->unk_60))->unk_1C & 0x800000)) {
            return;
        }
        message_or_list.value = get_unused_text_buffer();
        remove_message = write_text_byte_and_advance(8, message_or_list.value);
        if (((S_8009345C_4 *)(&D_800DD262))->unk_00.s != 0) {
            remove_text = &D_800E05F0;
        } else {
            remove_text = &D_800E05E1;
        }
        func_80099290(expand_text_control_codes(&D_800E06FA, append_entity_display_text(((S_8009345C_2 *)context)->unk_60,
            expand_text_control_codes(remove_text, remove_message))));
        display_text_with_fullwidth_adjustment(message_or_list.value);
        old_object = ((S_8009345C_2 *)context)->unk_60;
        D_800DD260 = 1;
        func_800A31D0(old_object);
        ((S_8009345C_16 *)(((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor)))->unk_AC = 0;
        decrement_monster_entry_count(((S_8009345C_15 *)(((S_8009345C_2 *)context)->unk_60))->unk_13, 3);
        unlink_entity_node(((S_8009345C_2 *)context)->unk_60);
        removed_object = ((S_8009345C_2 *)context)->unk_60;
        ((S_8009345C_5_pre *)removed_object)[-1].unk_00 = (u16) (((S_8009345C_5_pre *)removed_object)[-1].unk_00
            | 0x8000);
        (*(s32 *)&object_flag_block.flags) = (s32) (object_flag_block.flags | 0x8000);
        if (D_80082EB0[0] == NULL) {
            ((S_8009345C_0 *)actor)->unk_96 = 0U;
            next_state = ((S_8009345C_0 *)actor)->unk_9B + 4;
            break;
        }
        ((S_8009345C_0 *)actor)->unk_9B++;
        return;
    case 3:
        if ((has_pending_dungeon_activity(0) << 0x10) != 0) {
            return;
        }
        message_or_list.base = D_80082EB0;
        load_id = find_or_retain_sprite_resource_slot(((S_8009345C_7 *)(*message_or_list.base))->unk_00, 3);
        if (load_id != 0) {
            D_80081488 = begin_sprite_resource_load_with_completion_flag(((S_8009345C_7 *)(*message_or_list.base))->unk_00, &D_8008149C);
            load_monster_resource_data(((S_8009345C_7 *)(*message_or_list.base))->unk_00, load_id, 0);
            (*(s8 *)&D_800E3E40) = 0;
            Control_CD(0xFF, set_byte_one, &D_800E3E40);
        }
        ((S_8009345C_0 *)actor)->unk_9B++;
        return;
    case 4:
        if (((S_8009345C_8 *)(&D_800E3E40))->unk_00 == 0) {
            return;
        }
        if (D_80081488 != 0) {
            register_and_upload_sprite_resource(((S_8009345C_9 *)(D_80082EB0[0]))->unk_00, D_80081488);
        }
        ((S_8009345C_0 *)actor)->unk_9B++;
        return;
    case 5:
        message_or_list.base = D_80082EB0;
        create_id = find_or_retain_sprite_resource_slot(((S_8009345C_7 *)(*message_or_list.base))->unk_00, 3);
        if (create_id != 0) {
            runtime_map_type_16_entry_code(*message_or_list.base);
            new_object = load_monster_resource_data(((S_8009345C_7 *)(*message_or_list.base))->unk_00, create_id, 1)(1,
                ((S_8009345C_2 *)context)->unk_72, ((S_8009345C_2 *)context)->unk_73,
                (s16) (((S_8009345C_2 *)context)->unk_88 - 0x20));
            if (new_object != NULL) {
                (*(void **)((u8 *)(((((S_8009345C_4 *)(&D_800DD262))->unk_00.s * 4) + actor)) + (0xAC))) = new_object;
                D_800E3DF0[((S_8009345C_7 *)(*message_or_list.base))->unk_03 & 0x1F] = new_object;
                object_scale = ((S_8009345C_10_pre *)new_object)[-1].unk_04;
                ((S_8009345C_11 *)object_scale)->unk_1E = 0x800;
                ((S_8009345C_11 *)object_scale)->unk_1C = 0x800;
                object_position = ((S_8009345C_10_pre *)new_object)[-1].unk_00;
                ((S_8009345C_12 *)object_position)->unk_02 = (u16) map->unk_02;
                ((S_8009345C_12 *)object_position)->unk_06 = (u16) map->unk_06;
                ((S_8009345C_12 *)object_position)->unk_0A = (s16) (map->unk_0A - 0x10);
                func_80042640(new_object, ((S_8009345C_10 *)new_object)->unk_13);
                func_800424E0(new_object, ((S_8009345C_10 *)new_object)->unk_13, *message_or_list.base);
                object_flags = ((S_8009345C_10 *)new_object)->unk_1C;
                object_slot = ((S_8009345C_4 *)(&D_800DD262))->unk_00.s;
                ((S_8009345C_10 *)new_object)->unk_1C = object_flags | 0x02000000;
                ((S_8009345C_14 *)(((object_slot * 4) + actor)))->unk_D0 = D_80082EB0[0];
                ((S_8009345C_9 *)(D_80082EB0[0]))->unk_03 = (u8) (((S_8009345C_9 *)(D_80082EB0[0]))->unk_03 | 0x20);
                message_or_list.value = get_unused_text_buffer(0x02000000);
                create_message = message_or_list.value;
                if (D_800DD260 == 0) {
                    create_message = write_text_byte_and_advance(8, create_message);
                }
                if (((S_8009345C_4 *)(&D_800DD262))->unk_00.s != 0) {
                    create_text = &D_800E05F0;
                } else {
                    create_text = &D_800E05E1;
                }
                func_80099290(expand_text_control_codes(&D_800E0714, append_entity_display_text(new_object, expand_text_control_codes(create_text,
                    create_message))));
                display_text_with_fullwidth_adjustment(message_or_list.value);
                cleanup_slot = ((S_8009345C_4 *)(&D_800DD262))->unk_00.s;
                D_800E3D74[cleanup_slot] = 0;
                retain_spawn_resource(((S_8009345C_9 *)(D_80082EB0[0]))->unk_00, 3);
                func_80042560(new_object);
                play_sound_if_enabled(0x704);
            }
        }
        next_state = ((S_8009345C_0 *)actor)->unk_9B;
        start_ticks = 0x10U;
        ((S_8009345C_0 *)actor)->unk_96 = start_ticks;
        next_state = next_state + 1;
        break;
    case 7:
        end_ticks = ((S_8009345C_0 *)actor)->unk_96 - 1;
        ((S_8009345C_0 *)actor)->unk_96 = end_ticks;
        if ((end_ticks << 0x10) > 0) {
            return;
        }
        (*(void **)((u8 *)entity + (0x2C))) = D_800DD140;
        set_sprite_animation_frame(entity, D_800DD140[((s32) (g_game_work.view.viewAngle + ((S_8009345C_2 *)context)->unk_2A + 0x100)
            >> 9) & 7], 0, 1);
        ((S_8009345C_0 *)actor)->unk_9B++;
        return;
    case 8:
        if (!(((S_8009345C_1 *)entity)->unk_14 & 0x6000)) {
            return;
        }
        ((S_8009345C_0 *)actor)->unk_8C = handle_player_input;
        process_unflagged_linked_entries_alt(((S_8009345C_2 *)context)->unk_5C);
        process_unflagged_linked_entries(((S_8009345C_2 *)context)->unk_5C);
        g_dungeon_status.flags = (u16) (g_dungeon_status.flags | 0x812);
        ((S_8009345C_1 *)entity)->unk_14 = (u16) (((S_8009345C_1 *)entity)->unk_14 & 0xFDFF);
    case 6:
        ((S_8009345C_0 *)actor)->unk_9B++;
        return;
    case 9:
    default:
        return;
    }
    ((S_8009345C_0 *)actor)->unk_9B = next_state;
}
