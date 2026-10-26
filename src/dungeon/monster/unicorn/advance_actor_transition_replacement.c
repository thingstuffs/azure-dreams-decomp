#include "shared/audio_commands.h"
#include "sdk/libc.h"
#include "dungeon/system.h"
#include "engine/texture.h"

struct ObjectPosition;
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_status.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif

extern s32 cd_cue_base[];
extern u8 *actor_effect_color_targets[];
extern u8 dungeon_resource_buffer[200000];
extern u8 D_80173F68[];
extern u8 D_801745D8[];
extern u8 D_80174E24[];
extern s32 D_80174E2C[];
extern s16 D_80174E38[];
extern s32 unicorn_image_load_done[];
extern u8 unicorn_effect_load_done[];
extern void *D_80174E40[];

extern void select_record_entry_and_value(void *state, void *entries, short index);
extern s32 Control_CD();
extern void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
extern s32 run_cd_image_commands();
extern s32 read_stream_cue_start_offset(void);
extern s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern s32 lookup_masked_byte_table();
extern s32 unlink_entity_node();
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern void decrement_monster_entry_count(s16 requested_id, s16 requested_type);
extern void *advance_staged_entity_load();
extern s32 create_status_linked_render_effect();
extern s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);
extern void create_angular_offset_effect();

typedef struct S_80174704_0_pre {
    u16 unk_00;
} S_80174704_0_pre;   /* the 0x2 bytes before arg0 in advance_actor_transition_replacement, addressed as arg0[-1] */

typedef struct S_80174704_0 {
    u8 pad_00[0x96];
    union { u16 u; s16 s; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x10];
    union { void * p; u8 * p2; } unk_AC;   /* accessed as both */
    union { s16 s; u16 u; } unk_B0;   /* accessed as both */
} S_80174704_0;   /* arg0 in advance_actor_transition_replacement */

typedef struct S_80174704_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    u32 unk_1C;
    u8 pad_20[0xA];
    union { u16 u; s16 s; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x34];
    u8 * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80174704_1;   /* arg3 in advance_actor_transition_replacement */

typedef struct S_80174704_2 {
    u8 unk_00;
} S_80174704_2;   /* D_80174E3C in advance_actor_transition_replacement */

typedef struct S_80174704_3 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x3];
    void * unk_08;
    union { u8 * p; s32 i; } unk_0C;   /* accessed as both */
    union { void * p; u32 i; } unk_10;   /* accessed as both */
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
    u8 pad_30[0x78];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_80174704_3;

typedef struct S_80174704_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80174704_4;   /* target in advance_actor_transition_replacement */

typedef struct S_80174704_6 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_80174704_6;   /* repeat_dst in advance_actor_transition_replacement */

typedef struct S_80174704_8_pre {
    u8 * unk_00;
    u8 pad_04[0x10];
} S_80174704_8_pre;   /* the 0x14 bytes before linked2 in advance_actor_transition_replacement, addressed as linked2[-1] */

typedef struct S_80174704_8 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_80174704_8;   /* linked2 in advance_actor_transition_replacement */

typedef struct S_80174704_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80174704_10;

typedef struct S_80174704_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174704_11;   /* ((S_80174704_1 *)arg3)->unk_60 in advance_actor_transition_replacement */

/* Updates an actor transition through turning, color fading, effects, and replacement. */
/* Loads Unicorn's transition effects, fades the view tint and emits angular sparks, then replaces the
 * actor and restores facing. */
void advance_actor_transition_replacement(ActorRecord *action, ObjectPosition *position, SpriteFrameState *entity, ActorRecord *actor) {
    u8 *object = ((u8 *)(&g_game_work));
    u32 color;
    u8 state;
    s32 next_state;

    state = action->action_phase;
    switch (state) {

    case 0:
    {
        next_state = action->action_phase + 1;
        action->action_phase = next_state;
        return;
    }

    case 1:
        run_cd_image_commands(D_80174E24, unicorn_image_load_done, 0);
        ((S_80174704_0 *)action)->unk_B0.s = 0;
        action->action_phase++;
        ((S_80174704_1 *)actor)->unk_8A = ((S_80174704_1 *)actor)->unk_2A.u;
        ((S_80174704_1 *)actor)->unk_1C &= 0xFFFBFFFF;

    case 2:
    {
        s32 direction;
        u16 angle;

        direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174704_1 *)actor)->unk_2A.s + 0x100) >> 9) & 7;
        angle = ((S_80174704_1 *)actor)->unk_2A.u;
        if (((S_80174704_2 *)unicorn_image_load_done)->unk_00 == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((S_80174704_1 *)actor)->unk_2A.u = angle + 0x200;
            return;
        }
        run_cd_image_commands(D_80174E24, unicorn_image_load_done, 1);
        sound_set_cd_cue_parameters(0, cd_cue_base[0], 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, read_stream_cue_start_offset(), 0);
        unicorn_effect_load_done[0] = 0;
        Control_CD(0xFF, set_byte_one, unicorn_effect_load_done);
        select_nearby_target_and_initialize_slot((u8 *)actor - 0x20, position, 8, 0x300);
        ((S_80174704_0 *)action)->unk_96.u = 0x10;
        action->action_phase++;
    }

    case 3:
    {
        u16 old_timer = ((S_80174704_0 *)action)->unk_96.u;
        u16 timer = old_timer - 1;
        u8 *target_color;

        ((S_80174704_0 *)action)->unk_96.u = timer;
        if ((s32)(timer << 16) <= 0) {
            u8 cd_done = unicorn_effect_load_done[0];
            ((S_80174704_0 *)action)->unk_96.u = old_timer;
            if (cd_done == 0) {
                return;
            }
            action->action_phase++;
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            return;
        }

        target_color = actor_effect_color_targets[lookup_masked_byte_table(actor)];
        ((S_80174704_3 *)object)->unk_A8 +=
            (((S_80174704_4 *)target_color)->unk_00 - ((S_80174704_3 *)object)->unk_A8) /
            ((S_80174704_0 *)action)->unk_96.s;
        ((S_80174704_3 *)object)->unk_A9 +=
            (((S_80174704_4 *)target_color)->unk_01 - ((S_80174704_3 *)object)->unk_A9) /
            ((S_80174704_0 *)action)->unk_96.s;
        ((S_80174704_3 *)object)->unk_AA +=
            (((S_80174704_4 *)target_color)->unk_02 - ((S_80174704_3 *)object)->unk_AA) /
            ((S_80174704_0 *)action)->unk_96.s;
        return;
    }

    case 4:
        object = allocate_flagged_object_node(0x12);
        if (object == NULL) {
            return;
        }
        ((S_80174704_3 *)object)->unk_10.p = D_801745D8;
        register_node(object, D_80173F68);
        color = 0x00808080;
        ((S_80174704_0 *)action)->unk_AC.p = object;
        ((S_80174704_10 *)(((S_80174704_3 *)object)->unk_08))->unk_00 = position->x.v;
        ((S_80174704_10 *)(((S_80174704_3 *)object)->unk_08))->unk_04 = position->y.v;
        ((S_80174704_10 *)(((S_80174704_3 *)object)->unk_08))->unk_08 = position->z.v;
        {
            S_80174704_6 *effect_pos = ((S_80174704_3 *)object)->unk_08;
            s32 pos_z = position->z.v;

            D_80174E38[0] = -0x10;
            effect_pos->unk_08 = pos_z;
        }
        object = ((S_80174704_3 *)object)->unk_0C.p;
        ((S_80174704_3 *)object)->unk_1E = 0x1000;
        ((S_80174704_3 *)object)->unk_1C = 0x1000;
        ((S_80174704_3 *)object)->unk_0C.i = color;
        {
            s16 effect_index = lookup_masked_byte_table(actor) - 1;

            if (effect_index < 0) {
                effect_index = rand() % 3;
            }
            select_record_entry_and_value(object, dungeon_resource_buffer + D_80174E2C[effect_index], 0);
        }
        entity->flags |= 0x80;
        ((S_80174704_0 *)action)->unk_96.u = 0;
        next_state = action->action_phase + 1;
        action->action_phase = next_state;
        return;

    case 5:
    {
        u16 old_timer = ((S_80174704_0 *)action)->unk_96.u;
        ((S_80174704_0 *)action)->unk_96.u = old_timer + 1;
        if ((s16)old_timer < 30) {
            s32 angle_step = ((S_80174704_0 *)action)->unk_B0.s;

            create_angular_offset_effect(action, position, entity, actor,
                          (s16)(angle_step << 7), 0);
            ((S_80174704_0 *)action)->unk_B0.u++;
        }
    }
        object = ((S_80174704_0 *)action)->unk_AC.p2;
        object = ((S_80174704_3 *)object)->unk_0C.p;
        if (((S_80174704_3 *)object)->unk_14 & 0xE000) {
            ((S_80174704_0 *)action)->unk_96.u = 0x10;
            action->action_phase++;
            decrement_monster_entry_count(actor->species, 3);
            update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y, 0x300);
            unlink_entity_node(actor);
            object = (u8 *)actor - 0x20;
            ((S_80174704_3 *)object)->unk_10.i |= 0x80000000;
        }

    case 6:
        if (action->action_phase != 6) {
            return;
        }
        if (create_status_linked_render_effect(position, D_80174E40[0], D_80174E38[0], &staged_spawn_count) == 0) {
            return;
        }
        ((S_80174704_0 *)action)->unk_96.u = 0x10;
        action->action_phase++;
        decrement_monster_entry_count(actor->species, 3);
        update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y, 0x300);
        unlink_entity_node(actor);
        object = (u8 *)actor - 0x20;
        ((S_80174704_3 *)object)->unk_10.i |= 0x80000000;
        return;

    case 7:
    {
        u8 *replacement = advance_staged_entity_load(entity, actor);
        ((S_80174704_1 *)actor)->unk_60 = replacement;
        if (replacement == NULL) {
            return;
        }
        ((S_80174704_0 *)action)->unk_96.u = 0x10;
        action->action_phase++;
        ((S_80174704_11 *)(((S_80174704_1 *)actor)->unk_60))->unk_2A = ((S_80174704_1 *)actor)->unk_2A.u;
        {
            u8 *replacement_actor = ((S_80174704_1 *)actor)->unk_60;
            s32 direction;
            u8 *direction_frames;

            object = ((S_80174704_8_pre *)replacement_actor)[-1].unk_00;
            direction = ((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80174704_8 *)replacement_actor)->unk_2A + 0x100) >> 9) & 7;
            direction_frames = ((S_80174704_3 *)object)->unk_2C;
            select_indirect_table_entry(object, direction_frames[direction], ((S_80174704_3 *)object)->unk_04);
        }
        ((S_80174704_3 *)object)->unk_14 &= 0xFFFE;
    }

    case 8:
    {
        u16 timer = ((S_80174704_0 *)action)->unk_96.u - 1;
        ((S_80174704_0 *)action)->unk_96.u = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }
    }
        {

            ((S_80174704_11 *)(((S_80174704_1 *)actor)->unk_60))->unk_2A = ((S_80174704_1 *)actor)->unk_8A;
            ((S_80174704_0_pre *)action)[-1].unk_00 |= 0x8000;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            g_dungeon_status.activity_counts.parts.pending_action_count--;
            actor->pending_turn_updates = 0;
        }

        return;
    }
}
