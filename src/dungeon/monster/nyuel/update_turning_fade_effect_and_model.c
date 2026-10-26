#include "shared/audio_commands.h"

struct ObjectPosition;
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_cd_callback.h"
#include "shared/dungeon_effect_status.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "shared/entity.h"

typedef struct S_801749A8_8 {
    u8 pad_00[0x8];
    void * unk_08;
} S_801749A8_8;

typedef struct S_801749A8_10 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_801749A8_10;

typedef struct S_801749A8_11 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801749A8_11;   /* ((Rec_D_80082E80 *)arg3)->unk_60.as_pv in update_turning_fade_effect_and_model */

typedef struct S_801749A8_0_pre {
    u16 unk_00;
} S_801749A8_0_pre;   /* the 0x2 bytes before arg0 in update_turning_fade_effect_and_model, addressed as arg0[-1] */

typedef struct S_801749A8_0 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0x3];
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    s16 unk_A8;
} S_801749A8_0;   /* arg0 in update_turning_fade_effect_and_model */

typedef struct S_801749A8_2 {
    u8 pad_00[0xC];
    union { void * s; s32 u; } unk_0C;   /* accessed as both */
    union { void * s; s32 u; } unk_10;   /* accessed as both */
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
    u8 pad_20[0x88];
    u8 unk_A8;
    u8 unk_A9;
    u8 unk_AA;
} S_801749A8_2;

typedef struct S_801749A8_3 {
    u8 unk_00;
    u8 unk_01;
    u8 unk_02;
} S_801749A8_3;

typedef struct S_801749A8_6_pre {
    void * unk_00;
    u8 pad_04[0x10];
} S_801749A8_6_pre;

typedef struct S_801749A8_6 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_801749A8_6;

extern s32 cd_cue_base[];
struct S_8003E2D8;
typedef struct S_8003E2D8 S_8003E2D8;
extern u8 dungeon_resource_buffer[];
extern s16 D_80174F48[];
extern s32 Control_CD(s32 event_code, void *event_data, s32 payload);
extern void sound_set_cd_cue_parameters(int value_0, int value_1, int value_2, int value_3);
void run_cd_image_commands();
s32 register_node(); /* Unprototyped: two, three or four arguments; retail reads only the node and draw key. */
extern int read_stream_cue_start_offset(void);
void select_record_entry_and_value(void *state, void *entries, short index);
s32 select_indirect_table_entry();
s32 rand();
void unlink_entity_node();
void update_map_cell_flags_with_item_limit();
void decrement_monster_entry_count();
void *advance_staged_entity_load();
s32 play_sound_if_enabled();
s32 create_status_linked_render_effect();
s32 select_nearby_target_and_initialize_slot(void * slot_id,void *target, s32 target_id, s32 slot_value);
void create_cylindrical_effect();
s32 lookup_masked_byte_table(void *, ...);
extern u8 *actor_effect_color_targets[];
extern void func_8017487C(u8 *task, void *context, u8 *input);
extern u32 nyuel_image_commands;
extern s32 D_80174FB4;
extern u8 nyuel_image_load_done[];
extern u8 nyuel_effect_load_done[];
extern s32 D_80174FD0[];

/* Updates the turning, color fade, effect, and model replacement sequence. */
/* Loads Nyuel's transition effects, fades the view tint and creates a cylinder, then replaces the actor
 * and restores facing. */
void update_turning_fade_effect_and_model(void *sequence, EntityRec *position, SpriteFrameState *actor, void *target) {
    u8 *target_color;
    s16 direction;
    s32 effect_choice;
    s32 movement_done;
    void * model_addr;
    s16 effect_index;
    u16 turn_angle;
    u16 fade_ticks;
    s16 ticks_left;
    u16 fade_timer;
    u8 state;
    u8 ready;
    S_801749A8_2 *object;
    SpriteFrameState *sprite;
    void *model;

    object = ((struct S_8003E2D8 *)&g_game_work);
    state = ((S_801749A8_0 *)sequence)->unk_9B;
    switch (state) {
    case 0:
        ((S_801749A8_0 *)sequence)->unk_9B = (u8)(((S_801749A8_0 *)sequence)->unk_9B + 1);
        return;
    case 1:
        run_cd_image_commands(&nyuel_image_commands, &nyuel_image_load_done, 0);
        ((S_801749A8_0 *)sequence)->unk_A8 = 0;
        ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
        ((Rec_D_80082E80 *)target)->unk_8A = (u16) ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v;
    case 2:
        direction = ((s32) (g_game_work.view.camera_rotation.parts.viewAngle + (s16) ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v + 0x100)
            >> 9) & 7;
        if (nyuel_image_load_done[0] == 0 || direction != 2) {
            if (direction == 2) {
                return;
            }
            turn_angle = ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v + 0x200;
            ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v = turn_angle;
            return;
        }
        run_cd_image_commands(&nyuel_image_commands, &nyuel_image_load_done, 1);
        sound_set_cd_cue_parameters(0, *cd_cue_base, 0x04000AD4, 0x05000CC4);
        Control_CD(0x15, read_stream_cue_start_offset(), NULL);
        nyuel_effect_load_done[0] = 0;
        Control_CD(0xFF, (s32) set_byte_one, &nyuel_effect_load_done);
        select_nearby_target_and_initialize_slot(target - 0x20, position, 8, 0x300);
        ((S_801749A8_0 *)sequence)->unk_96 = 0x10U;
        ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
    case 3:
        fade_timer = ((S_801749A8_0 *)sequence)->unk_96;
        fade_ticks = fade_timer - 1;
        ((S_801749A8_0 *)sequence)->unk_96 = fade_ticks;
        if ((fade_ticks << 0x10) <= 0) {
            ready = nyuel_effect_load_done[0];
            ((S_801749A8_0 *)sequence)->unk_96 = fade_timer;
            if (ready == 0) {
                return;
            }
            ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
            play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
            return;
        }
        target_color = actor_effect_color_targets[lookup_masked_byte_table(target)];
        object->unk_A8 = (u8) (object->unk_A8 + ((s32) (((S_801749A8_3 *)target_color)->unk_00
            - object->unk_A8) / (s16) ((S_801749A8_0 *)sequence)->unk_96));
        object->unk_A9 = (u8) (object->unk_A9 + ((s32) (((S_801749A8_3 *)target_color)->unk_01
            - object->unk_A9) / (s16) ((S_801749A8_0 *)sequence)->unk_96));
        object->unk_AA = (u8) (object->unk_AA + ((s32) (((S_801749A8_3 *)target_color)->unk_02
            - object->unk_AA) / (s16) ((S_801749A8_0 *)sequence)->unk_96));
        return;
    case 4:
        object = allocate_flagged_object_node(0x12);
        if (object == 0) {
            return;
        }
        object->unk_10.s = &func_8017487C;
        register_node(object, project_sprite_chain);
        ((S_801749A8_0 *)sequence)->unk_A4 = object;
        ((S_801749A8_10 *)(((S_801749A8_8 *)object)->unk_08))->unk_00 = (s32) position->x.v;
        ((S_801749A8_10 *)(((S_801749A8_8 *)object)->unk_08))->unk_04 = (s32) position->y.v;
        ((S_801749A8_10 *)(((S_801749A8_8 *)object)->unk_08))->unk_08 = (s32) position->z.v;
        object = object->unk_0C.s;
        object->unk_1E = 0x1000;
        object->unk_1C = 0x1000;
        object->unk_0C.u = 0x808080;
        effect_choice = lookup_masked_byte_table(target) - 1;
        effect_index = effect_choice;
        if ((effect_choice << 0x10) < 0) {
            effect_index = rand() % 3;
        }
        select_record_entry_and_value(object, &dungeon_resource_buffer[*(((s32) (effect_index << 0x10) >> 0x10) + &D_80174FB4)], 0);
        actor->flags = (u16) (actor->flags | 0x80);
        ((S_801749A8_0 *)sequence)->unk_96 = 0U;
        ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
        create_cylindrical_effect(sequence, position, actor);
        return;
    case 5:
        object = ((S_801749A8_0 *)sequence)->unk_A4;
        object = object->unk_0C.s;
        if (object->unk_14 & 0xE000) {
            ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
        }
    case 6:
        if (((S_801749A8_0 *)sequence)->unk_9B != 6) {
            return;
        }
        movement_done = create_status_linked_render_effect(position, D_80174FD0[0], D_80174F48[0], &staged_spawn_count);
        if (movement_done == 0) {
            return;
        }
        ((S_801749A8_0 *)sequence)->unk_96 = 0x10U;
        ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
        decrement_monster_entry_count(((Rec_D_80082E80 *)target)->unk_12.at01_u8.v, 3);
        update_map_cell_flags_with_item_limit(actor->tile_x, actor->tile_y, 0x300);
        unlink_entity_node(target);
        object = target - 0x20;
        object->unk_10.u = object->unk_10.u | 0x80000000;
        return;
    case 7:
        model_addr = advance_staged_entity_load(actor, target);
        ((Rec_D_80082E80 *)target)->unk_60.as_pv = (void *) model_addr;
        if (model_addr == 0) {
            return;
        }
        ((S_801749A8_0 *)sequence)->unk_96 = 0x10U;
        ((S_801749A8_0 *)sequence)->unk_9B = (u8) (((S_801749A8_0 *)sequence)->unk_9B + 1);
        ((S_801749A8_11 *)(((Rec_D_80082E80 *)target)->unk_60.as_pv))->unk_2A =
            (u16) ((Rec_D_80082E80 *)target)->unk_28.at02_u16.v;
        model = ((Rec_D_80082E80 *)target)->unk_60.as_pv;
        sprite = ((S_801749A8_6_pre *)model)[-1].unk_00;
        select_indirect_table_entry(sprite, *(*(u8 **)&sprite->frameTable + (((s32) (g_game_work.view.camera_rotation.parts.viewAngle
            + (s16) ((S_801749A8_6 *)model)->unk_2A + 0x100) >> 9) & 7)), sprite->unk_04);
        sprite->flags = (u16) (sprite->flags & 0xFFFE);
    case 8:
        ticks_left = ((S_801749A8_0 *)sequence)->unk_96 - 1;
        ((S_801749A8_0 *)sequence)->unk_96 = ticks_left;
        if (ticks_left > 0) {
            return;
        }
        ((S_801749A8_11 *)(((Rec_D_80082E80 *)target)->unk_60.as_pv))->unk_2A =
            (u16) ((Rec_D_80082E80 *)target)->unk_8A;
        ((S_801749A8_0_pre *)sequence)[-1].unk_00 = (u16) (((S_801749A8_0_pre *)sequence)[-1].unk_00 | 0x8000);
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        g_dungeon_status.activity_counts.parts.pending_action_count = (u16)(((u16)g_dungeon_status.activity_counts.parts.pending_action_count) - 1);
        ((Rec_D_80082E80 *)target)->unk_6D = 0;
        return;
    }
}
