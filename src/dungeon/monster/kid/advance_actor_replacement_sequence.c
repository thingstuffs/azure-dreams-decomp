#include "shared/audio_commands.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_cd_callback.h"
#include "shared/slus_callbacks.h"
#include "shared/dungeon_effect_status.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80174800_arg0.h"

#include "slus/gp_shared_81510.h"
#include "sdk/libc.h"
#include "dungeon/system.h"
#include "engine/node.h"

typedef struct S_80174B20_14 {
    u8 pad_00[0x60];
    void * unk_60;
} S_80174B20_14;   /* arg3 in advance_actor_replacement_sequence */

typedef struct S_80174B20_16 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174B20_16;   /* ((S_80174B20_14 *)arg3)->unk_60 in advance_actor_replacement_sequence */

typedef struct S_80174B20_0_pre {
    u16 unk_00;
} S_80174B20_0_pre;   /* the 0x2 bytes before arg0 in advance_actor_replacement_sequence, addressed as arg0[-1] */

typedef struct S_80174B20_1 {
    u8 pad_00[0x13];
    u8 unk_13;
    u8 pad_14[0x8];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x34];
    void * unk_60;
    u8 pad_64[0x9];
    s8 unk_6D;
    u8 pad_6E[0x1C];
    u16 unk_8A;
} S_80174B20_1;   /* arg3 in advance_actor_replacement_sequence */

typedef struct S_80174B20_2 {
    u8 unk_00;
} S_80174B20_2;   /* &D_8017521D in advance_actor_replacement_sequence */

typedef struct S_80174B20_4 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_80174B20_4;

typedef struct S_80174B20_7 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
    u8 pad_14A4[0x3D74];
    s16 unk_5218;
} S_80174B20_7;



typedef struct S_80174B20_9 {
    u8 pad_00[0x4];
    s8 unk_04;
    u8 pad_05[0x7];
    union { s32 s; void * u; } unk_0C;   /* accessed as both */
    s32 unk_10;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0xC];
    u8 * unk_2C;
} S_80174B20_9;

typedef struct S_80174B20_11_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_80174B20_11_pre;

typedef struct S_80174B20_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_80174B20_11;

/* cfail-repair: tf7-phase1-cache-v3 */
void select_record_entry_and_value(void *state, void *entries, short index);     /* extern */
s32 Control_CD(); /* extern */
#include "slus/sound_set_cd_cue_parameters_api.h" /* extern */
#include "engine/graphics/run_cd_image_commands_api.h" /* extern */
int read_stream_cue_start_offset(void);                           /* extern */
#include "engine/texture/select_indirect_table_entry_api.h"              /* extern */
s32 lookup_masked_byte_table();  /* extern */
#include "dungeon/level/unlink_entity_node_api.h"                      /* extern */
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"             /* extern */
#include "dungeon/item/decrement_monster_entry_count_api.h"                 /* extern */
#include "dungeon/actor/advance_staged_entity_load_api.h"                /* extern */
s32 create_status_linked_render_effect();     /* extern */
#include "dungeon/select_nearby_target_and_initialize_slot_api.h" /* extern */
void create_randomly_rotated_offset_effect(); /* extern */
extern s32 cd_cue_base;
extern void *actor_effect_color_targets[];
extern u8 dungeon_resource_buffer[];
s32 update_actor_state_after_map_check(void *initial_payload, s32 entry_data, Entry *entry, s32 unused);
void blend_effect_channels_to_gray(u8 *task, void *context, SpriteFrameState *input);
extern u32 kid_image_commands;
extern s32 D_80175200[];
extern s16 D_80175218;
extern M2C_UNK kid_image_load_done;
extern u8 kid_effect_load_done;
extern s32 D_80175220;

/* Advances the actor replacement sequence, including its visual effects and cleanup. */
/* Loads Kid's transition effects, fades the view tint and emits seven rotated sprites, then replaces the
 * actor and restores facing. */
void advance_actor_replacement_sequence(ActorRecord *state, ObjectPosition *position, SpriteFrameState *entity, ActorRecord *actor) {
    s32 tint;
    S_80174B20_7 *globals_base;
    s32 global_flags;
    u16 active_count;
    s16 next_ray;
    s16 ray_index;
    s32 direction;
    s32 effect_ready;
    s32 color_index;
    s32 random_value;
    s32 style_index;
    s16 style;
    s32 position_z;
    u16 fade_ticks;
    u16 finish_ticks;
    u16 previous_ticks;
    u8 phase;
    S_80174B20_4 *target_color;
    ObjectPosition *effect_position;
    GameWork *scene_color;
    S_80174B20_9 *sprite;
    ObjectNodeHeader *effect;
    void *new_actor;
    void *replacement;

    scene_color = &g_game_work;
    phase = ((Rec_func_80174800_arg0 *)state)->unk_9B;
    switch (phase) {
    case 0:
        ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
        return;
    case 1:
        run_cd_image_commands(&kid_image_commands, (u8 *)(&kid_image_load_done), 0);
        ((Rec_func_80174800_arg0 *)state)->unk_B0 = 0;
        ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
        ((S_80174B20_1 *)actor)->unk_8A = (u16) ((S_80174B20_1 *)actor)->unk_2A;
        actor->flags1C = (s32) (actor->flags1C & 0xFFFBFFFF);
    case 2:
        direction = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((S_80174B20_1 *)actor)->unk_2A + 0x100) >> 9) & 7;
        if ((*(u8 *)&kid_image_load_done) == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            ((S_80174B20_1 *)actor)->unk_2A = (u16) (((S_80174B20_1 *)actor)->unk_2A + 0x200);
            return;
        }
        run_cd_image_commands(&kid_image_commands, (u8 *)(&kid_image_load_done), 1);
        sound_set_cd_cue_parameters(0, cd_cue_base, 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, read_stream_cue_start_offset(), NULL);
        (*(s8 *)&kid_effect_load_done) = 0;
        Control_CD(0xFF, set_byte_one, &kid_effect_load_done);
        select_nearby_target_and_initialize_slot((s32)(((u8 *)actor - 0x20)), position, 8, 0x300);
        ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
        ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
    case 3:
        previous_ticks = ((Rec_func_80174800_arg0 *)state)->unk_96;
        fade_ticks = previous_ticks - 1;
        ((Rec_func_80174800_arg0 *)state)->unk_96 = fade_ticks;
        if ((fade_ticks << 0x10) <= 0) {
            effect_ready = ((S_80174B20_2 *)(&kid_effect_load_done))->unk_00;
            ((Rec_func_80174800_arg0 *)state)->unk_96 = previous_ticks;
            if (effect_ready == 0) {
                return;
            }
            ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            return;
        }
        color_index = lookup_masked_byte_table(actor);
        target_color = actor_effect_color_targets[color_index];
        scene_color->view.tint.parts.tint_r = (u8) (scene_color->view.tint.parts.tint_r + ((s32) (target_color->unk_00
            - scene_color->view.tint.parts.tint_r) / (s16) ((Rec_func_80174800_arg0 *)state)->unk_96));
        scene_color->view.tint.parts.tint_g = (u8) (scene_color->view.tint.parts.tint_g + ((s32) (target_color->unk_01
            - scene_color->view.tint.parts.tint_g) / (s16) ((Rec_func_80174800_arg0 *)state)->unk_96));
        scene_color->view.tint.parts.tint_b = (u8) (scene_color->view.tint.parts.tint_b + ((s32) (target_color->unk_02
            - scene_color->view.tint.parts.tint_b) / (s16) ((Rec_func_80174800_arg0 *)state)->unk_96));
        return;
    case 4:
        effect = allocate_flagged_object_node(0x12);
        if (effect == NULL) {
            return;
        }
        effect->update_callback = &blend_effect_channels_to_gray;
        register_node(effect, &update_actor_state_after_map_check);
        tint = 0x808080;
        ((Rec_func_80174800_arg0 *)state)->unk_AC = effect;
        effect->position->x.v = (s32) position->x.v;
        effect->position->y.v = (s32) position->y.v;
        effect_position = effect->position;
        position_z = position->z.v;
        D_80175218 = -4;
        effect_position->z.v = position_z;
        sprite = effect->sprite;
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0C.s = tint;
        style_index = lookup_masked_byte_table(actor) - 1;
        style = style_index;
        if ((style_index << 0x10) < 0) {
            random_value = rand();
            style = random_value % 3;
        }
        select_record_entry_and_value(sprite, &dungeon_resource_buffer[(*(s32 *)((u8 *)D_80175200 + (s16) style * 4))], 0);
        entity->flags = (u16) (entity->flags | 0x80);
        ray_index = 1;
        ((Rec_func_80174800_arg0 *)state)->unk_96 = 0U;
        ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
        do {
            create_randomly_rotated_offset_effect(state, position, entity, (s16) (ray_index << 0xA));
            next_ray = ray_index + 1;
            ray_index = next_ray;
        } while (next_ray < 8);
        return;
    case 5:
        sprite = ((Rec_func_80174800_arg0 *)state)->unk_AC;
        sprite = sprite->unk_0C.u;
        if (sprite->unk_14 & 0xE000) {
            ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
            ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
            decrement_monster_entry_count(actor->species, 3);
            update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y, 0x300);
            unlink_entity_node(actor);
            sprite = ((S_80174B20_9 *)((u8 *)actor - 0x20));
            sprite->unk_10 = (s32) (sprite->unk_10 | 0x80000000);
        }
    case 6:
        if (((Rec_func_80174800_arg0 *)state)->unk_9B != 6) {
            return;
        }
        if (create_status_linked_render_effect(position, D_80175220, D_80175218, &staged_spawn_count) == 0) {
            return;
        }
        ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
        ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
        decrement_monster_entry_count(actor->species, 3);
        update_map_cell_flags_with_item_limit(entity->tile_x, entity->tile_y, 0x300);
        unlink_entity_node(actor);
        sprite = ((S_80174B20_9 *)((u8 *)actor - 0x20));
        sprite->unk_10 = (s32) (sprite->unk_10 | 0x80000000);
        return;
    case 7:
        new_actor = advance_staged_entity_load((s32)(entity), actor);
        ((S_80174B20_1 *)actor)->unk_60 = new_actor;
        if (new_actor == NULL) {
            return;
        }
        ((Rec_func_80174800_arg0 *)state)->unk_96 = 0x10U;
        ((Rec_func_80174800_arg0 *)state)->unk_9B = (u8) (((Rec_func_80174800_arg0 *)state)->unk_9B + 1);
        ((S_80174B20_16 *)(((S_80174B20_14 *)actor)->unk_60))->unk_2A = (u16) ((S_80174B20_1 *)actor)->unk_2A;
        replacement = ((S_80174B20_1 *)actor)->unk_60;
        sprite = ((S_80174B20_11_pre *)replacement)[-1].unk_00;
        select_indirect_table_entry((struct S_80047738 *)(sprite), sprite->unk_2C[((s32) (g_game_work.view.camera_rotation.parts.viewAngle
            + (s16) ((S_80174B20_11 *)replacement)->unk_2A + 0x100) >> 9) & 7], sprite->unk_04);
        sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFFE);
    case 8:
        finish_ticks = ((Rec_func_80174800_arg0 *)state)->unk_96 - 1;
        ((Rec_func_80174800_arg0 *)state)->unk_96 = finish_ticks;
        if ((finish_ticks << 0x10) > 0) {
            return;
        }
        globals_base = (void *)0x80080000;
        ((S_80174B20_16 *)(((S_80174B20_14 *)actor)->unk_60))->unk_2A = (u16) ((S_80174B20_1 *)actor)->unk_8A;
        ((S_80174B20_0_pre *)state)[-1].unk_00 = (u16) (((S_80174B20_0_pre *)state)[-1].unk_00 | 0x8000);
        global_flags = globals_base->unk_14A0;
        active_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count);
        globals_base->unk_14A0 = global_flags | 0x8000;
        g_dungeon_status.activity_counts.parts.pending_action_count = active_count - 1;
        actor->pending_turn_updates = 0;
        return;
    default:
        return;
    }
}
