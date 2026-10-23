#include "shared/audio_commands.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/def_table.h"
#include "shared/object_node.h"
#include "shared/record_ptrs.h"
#include "shared/slus_callbacks.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "engine/cd.h"
extern int abs(int);

typedef struct {
    u32 x;
    u32 y;
    u32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} VecData;

typedef struct {
    u8 pad[0x12];
    u8 type;
    u8 pad13;
} ItemData;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} ShortVec;

typedef struct S_func_80FDD1A0_1 {
    u8 pad_00[0x8C];
    void *unk_8C;
    u8 pad_90[0x08];
    u16 unk_98;
    u8 pad_9A[0x01];
    u8 unk_9B;
    u8 pad_9C[0x0A];
    u16 unk_A6;
    void *unk_A8;
} S_func_80FDD1A0_1;

typedef struct S_func_80FDD1A0_2 {
    u8 pad_00[0x04];
    s8 unk_04;
    u8 pad_05[0x07];
    s32 unk_0C;
    u8 pad_10[0x02];
    u16 unk_12;
    u16 unk_14;
    u8 pad_16[0x06];
    u16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x04];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x02];
    s32 unk_28;
    u8 *unk_2C;
} S_func_80FDD1A0_2;

typedef struct S_func_80FDD1A0_3 {
    u8 pad_00[0x08];
    u8 unk_08;
    u8 pad_09[0x02];
    u8 unk_0B;
    u8 pad_0C[0x02];
    u8 unk_0E;
    u8 pad_0F[0x0D];
    u32 unk_1C;
    u8 pad_20[0x0A];
    union { s16 s; u16 u; } unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x18];
    void *unk_60;
    u8 pad_64[0x09];
    union { s8 s; u8 u; } unk_6D;
    u8 pad_6E[0x04];
    union { s8 s; u8 u; } unk_72;
    union { s8 s; u8 u; } unk_73;
} S_func_80FDD1A0_3;

typedef struct S_func_80FDD1A0_4 {
    u8 pad_00[0x08];
    VecData *unk_08;
    void *unk_0C;
    void *unk_10;
    u8 pad_14[0x36];
    u16 unk_4A;
    u8 pad_4C[0x6F];
    u8 unk_BB;
} S_func_80FDD1A0_4;

extern void *allocate_list_node(s32, void *);
extern void register_node(void *, void *);
extern void select_sprite_entry(void *, s32, s32);
extern void *scan_actor_along_heading(void *, u8, u8, s16, s32);
extern void set_record_integer_tile_center(void *, u8, u8);
extern void advance_status_timers(void *);
extern void play_sound_if_enabled(s32);
extern s32 create_actor_spell_effect(void *, u8 *, s32, u16 *);
extern void create_two_row_object_group(void *, s16);

extern u8 effect_update_tag[];
extern u8 D_80170838[16];
extern u8 killer_action_resume_address;
#include "dungeon/monster/killer.h"
extern u8 D_80174078[];

/* Updates item use, its visual effect, and the actor's return to idle. */
/* Starts a targeted spell with two effect rows, keeps its child at the actor's position, and releases it
 * on completion. */
void update_item_use(S_func_80FDD1A0_1 *actor, VecData *motion, SpriteFrameState *sprite, S_func_80FDD1A0_3 *actor_data)
{
    s16 use_player = 0;
    S_func_80FDD1A0_4 *effect = 0;
    void *target;
    u8 *item_slot;
    S_func_80FDD1A0_2 *effect_sprite;
    ShortVec sound_pos;
    u8 phase;
    u32 kind_index;

    phase = actor->unk_9B;
    switch (phase) {
    case 0:
        if (actor_data->unk_1C & ACTOR_PLAYER_SIDE) {
            kind_index = (actor_data->unk_46 & 0x3FFF) - 1;
            switch (kind_index) {
            case 6:
                use_player = 1;
            case 2:
                item_slot = &actor_data->unk_0E;
                break;
            case 5:
                use_player = 1;
            case 1:
                item_slot = &actor_data->unk_0B;
                break;
            case 4:
                use_player = 1;
            case 0:
                item_slot = &actor_data->unk_08;
                break;
            case 3:
            default:
                item_slot = 0;
                break;
            }
        } else {
            s32 action_kind = actor_data->unk_46 & 0x3FFF;
            switch (action_kind) {
            case 3:
                item_slot = &actor_data->unk_0E;
                break;
            case 2:
                item_slot = &actor_data->unk_0B;
                break;
            case 1:
                item_slot = &actor_data->unk_08;
                break;
            default:
                item_slot = 0;
                break;
            }
        }

        if (*item_slot != 0) {
            actor->unk_98 &= 0xFF7F;
            {
                s16 player_target;

                player_target = use_player;
                if (player_target != 0) {
                    target = primary_actor_record;
                    actor_data->unk_60 = target;
                    {
                        S_func_80FDD1A0_2 *item_id;

                        item_id = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                        actor_data->unk_72.u = item_id->unk_24;
                        actor_data->unk_73.u = item_id->unk_25;
                    }
                } else {
                    S_func_80FDD1A0_2 *item_id;

                    item_id = (S_func_80FDD1A0_2 *)(*item_slot);
                    if (item_action_definitions[((u8)item_id)].kind == 2) {
                        target = actor_data->unk_60;
                        if (target != 0) {
                            item_id = ((ObjectNodeHeader *)((u8 *)target - 0x20))->sprite;
                            actor_data->unk_72.u = item_id->unk_24;
                            actor_data->unk_73.u = item_id->unk_25;
                        }
                    } else {
                        s32 target_x;
                        s32 abs_x;
                        s32 abs_y;
                        s32 target_y;

                        target = scan_actor_along_heading(
                            actor_data,
                            sprite->unk_24,
                            sprite->unk_25,
                            actor_data->unk_2A.s,
                            0x10);
                        actor_data->unk_60 = target;
                        abs_x = abs(actor_data->unk_72.s);
                        abs_y = abs(actor_data->unk_73.s);
                        actor_data->unk_72.u = abs_x;
                        actor_data->unk_73.u = abs_y;
                    }
                }
            }

            sound_pos.x = motion->x >> 16;
            sound_pos.y = motion->y >> 16;
            sound_pos.z = motion->z >> 16;

            if (!(actor->unk_98 & 0x2000)) {
                void *new_effect;

                new_effect = allocate_list_node(0x112, ((u8 *)(&scene_object_list_anchor)));
                actor->unk_A8 = new_effect;
                effect = new_effect;
                if (effect != 0) {
                    VecData *effect_motion;

                    register_node(effect, project_sprite_chain);
                    effect->unk_10 = effect_update_tag;
                    effect_motion = effect->unk_08;
                    *effect_motion = *motion;
                    effect->unk_BB = 0;
                    effect->unk_4A = actor_data->unk_2A.u;
                    {
                        s32 sprite_flags = sprite->unk_28;
                        effect_sprite = effect->unk_0C;

                        effect_sprite->unk_1E = 0x1000;
                        effect_sprite->unk_1C = 0x1000;
                        effect_sprite->unk_28 = sprite_flags;
                        effect_sprite->unk_14 = sprite->flags;
                        effect_sprite->unk_12 = sprite->clut;
                        {
                            s32 sprite_link = sprite->color.word;

                            effect_sprite->unk_2C = D_80174078;
                            effect_sprite->unk_0C = sprite_link;
                        }
                    }
                }
                actor->unk_98 |= 0x2000;
            }

            {
                u8 *animations;
                s32 direction;

                effect_sprite = actor->unk_A8;
                effect_sprite = ((S_func_80FDD1A0_4 *)effect_sprite)->unk_0C;
                animations = effect_sprite->unk_2C;
                direction = ((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->unk_2A.s + 0x100) >> 9) & 7;
                select_sprite_entry(effect_sprite, animations[direction], 0);
            }
            if (create_actor_spell_effect(actor_data, item_slot, use_player,
                              &actor->unk_98) == 0) {
                return;
            }
            actor->unk_98 &= 0xDFFF;
            sprite->flags &= 0xF7FF;
            play_sound_if_enabled(0x703);
            create_two_row_object_group(&sound_pos, (*item_slot - 1) % 3);
            actor->unk_9B++;
            return;
        }
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)primary_actor_record + 0xA6))--;
        advance_status_timers(actor_data);
        actor_data->unk_6D.u--;
        actor->unk_8C = &killer_action_resume_address;
        actor_data->unk_73.u = 0;
        actor_data->unk_72.u = 0;
        actor_data->unk_46 &= 0x7FFF;
        return;

    case 1:
        if (get_cd_command_queue_depth() != 0) {
            sprite->flags |= 0x800;
            return;
        }
        sprite->flags &= 0xF7FF;
        actor->unk_9B++;
                        /* fallthrough */

    case 2:
        if (actor->unk_A8 != 0) {
            effect = actor->unk_A8;
            *effect->unk_08 = *motion;
        }
        if ((sprite->unk_04 != 4 ||
             !(sprite->flags & 0x1000)) &&
            !(sprite->flags & 0xE000)) {
            return;
        }
        actor->unk_98 |= 0x80;
        if (!(sprite->flags & 0xE000)) {
            return;
        }
        if (actor->unk_A8 != 0) {
            effect->unk_BB = 0xFF;
            actor->unk_A8 = 0;
        }
        sprite->frameTable = killer_direction_frames;
        select_sprite_entry(
            sprite,
            killer_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + actor_data->unk_2A.s + 0x100) >> 9) & 7],
            0);
        motion->dz = 0;
        motion->dy = 0;
        motion->dx = 0;
        set_record_integer_tile_center(motion, sprite->unk_24, sprite->unk_25);
        if (((s32)g_dungeon_status.active_actor) != 0) {
            return;
        }
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        sprite->flags &= 0xF7FF;
        actor->unk_8C = &killer_action_resume_address;
        advance_status_timers(actor_data);
        if (actor_data->unk_6D.s > 0) {
            actor_data->unk_6D.u--;
        }
        actor_data->unk_73.u = 0;
        actor_data->unk_72.u = 0;
        actor_data->unk_46 &= 0x7FFF;
        play_sound_if_enabled(AUDIO_FADE_CD_FAST);
        return;

    default:
        return;
    }
}
