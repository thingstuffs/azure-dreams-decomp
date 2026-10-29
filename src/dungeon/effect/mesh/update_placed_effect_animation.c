#include "shared/audio_commands.h"
#include "common.h"
#include "shared/tile_object.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"

typedef struct S_81978428_1 {
    u16 unk_00;
} S_81978428_1;   /* self->part4 in update_placed_effect_animation */

typedef struct S_81978428_2 {
    u8 pad_00[0x96];
    u16 unk_96;
    u8 pad_98[0xE];
    u16 unk_A6;
    u8 unk_A8;
} S_81978428_2;   /* case0_global in update_placed_effect_animation */

typedef struct S_81978428_3 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_81978428_3;   /* angle_global in update_placed_effect_animation */

typedef struct S_81978428_6 {
    u8 pad_00[0x2];
    union { u16 s; s16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
} S_81978428_6;   /* work in update_placed_effect_animation */

typedef struct S_81978428_8 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_8;   /* case3_object in update_placed_effect_animation */

typedef struct S_81978428_9 {
    u8 pad_00[0x1C];
    u32 unk_1C;
} S_81978428_9;   /* after_object in update_placed_effect_animation */

typedef struct S_81978428_10 {
    u8 pad_00[0xC];
    u32 unk_0C;
} S_81978428_10;   /* after_aux in update_placed_effect_animation */

typedef struct S_81978428_12_pre {
    u16 unk_00;
} S_81978428_12_pre;   /* the 0x2 bytes before self in update_placed_effect_animation, addressed as self[-1] */



typedef struct {
    void *part0;
    void *part4;
    u8 kind;
    u8 effect;
    s16 state;
    u8 pad0C[2];
    u16 angle;
    u16 counter;
    u8 pad12[2];
    void *object;
    s16 timer;
    s16 flag;
} State81978428;

typedef struct {
    s16 pad0;
    u16 x;
    s16 pad4;
    u16 y;
    s16 pad8;
    s16 z;
    u8 pad0C[8];
} Scratch81978428;


extern void func_800243C0(void *, void *);
extern s32 read_sound_mode_blocking_status(s32);
extern void play_sound_if_enabled(s32);
#include "dungeon/item/actor_target.h"
#include "dungeon/item.h"
extern u16 get_surface_height_at_record(void *);
extern s32 check_left_tile_and_center_height(s32 x, s32 y, s32 z);
extern void func_80025A9C(void *, void *, void *);
extern void func_80025508(void *, void *);
extern void apply_attack_power_and_element_effects(void *, s32, u8, s32, s16, void *, s32);

/* Advances the object effect through placement, animation, and cleanup states. */
void update_placed_effect_animation(State81978428 *state, s32 *position_out)
{
    State81978428 *self = state;
    s32 *position = position_out;
    S_81978428_6 *target_pos;
    s32 step_count;
    TileObject *tile_map;
    u8 *tint_data;
    Scratch81978428 fallback_pos;
    void *spawned_object;
    u16 timer;
    s32 state_index;
    s32 tile_step;
    s32 tile_step_2;
    s32 tile_step_3;
    s32 tile_step_4;

    timer = self->counter;
    state_index = self->state;
    timer++;
    self->counter = timer;
    switch (state_index) {
    case 0:
        {
            ActorRecord *init_page;
            u16 next_state;

            next_state = self->state;
            init_page = primary_actor_record;
            self->counter = 0;
            next_state++;
            self->state = next_state;
            ((PlayerRecord *)init_page)->unk_F4 = 0;
            func_800243C0((u8 *)self->part0 - 0x20, self->part4);
        }
    case 1:
        {
            u8 *player_page;
            S_81978428_2 *player_state;
            u8 *facing_player;

            if ((((S_81978428_1 *)(self->part4))->unk_00 & 0x80) == 0) {
                break;
            }
            player_page = (u8 *)0x80080000;
            player_state = (S_81978428_2 *)(*(u8 **)(player_page + 0x14A8));
            self->timer = 10;
            player_state->unk_96 = 8;
            player_state->unk_A6--;
            player_state->unk_A8 = self->kind;
            facing_player = *(u8 **)(player_page + 0x14A8);
            self->angle = ((S_81978428_3 *)facing_player)->unk_2A;
            self->state++;
            if (read_sound_mode_blocking_status(4) != 2) {
                play_sound_if_enabled(AUDIO_PLAY_CD_CUE);
                break;
            }
            play_sound_if_enabled(AUDIO_RESUME_CD);
            break;
        }

    case 2:
        timer = self->timer;
        timer--;
        self->timer = timer;
        if ((s32)((u32)timer << 16) > 0) {
            break;
        }

        {
            ActorRecord *player;
            s32 spawn_angle;
            s32 player_x;
            player_x = view_reference_entity.x.v;
            player = primary_actor_record;
            position[0] = player_x;
            position[1] = view_reference_entity.y.v;
            position[2] = (s32)player->ground_height << 16;
            spawn_angle = player->facing;
            tile_map = &reference_tile_object;
            spawned_object = scan_actor_along_heading(player, tile_map->tile_position.parts.tile_x, tile_map->tile_position.parts.tile_y, spawn_angle, 8);
        }
        self->object = spawned_object;
        if (spawned_object != 0) {
            target_pos = *(void **)((u8 *)spawned_object - 0x18);
        } else {
            target_pos = (S_81978428_6 *)&fallback_pos;
            {
                u8 tile_x;
                u8 tile_y;

                tile_x = tile_map->tile_position.parts.tile_x;
                target_pos->unk_02.s = (tile_x << 6) + 0x20;
                tile_y = tile_map->tile_position.parts.tile_y;
                target_pos->unk_06.s = (tile_y << 6) + 0x20;
            }

            for (step_count = 0; step_count < 8; step_count++) {
                {
                    ActorRecord *player;

                    player = primary_actor_record;
                    tile_step = dir_step_x[(((u16)player->facing) >> 9) & 7];
                    target_pos->unk_02.u += tile_step << 6;
                    tile_step_2 = dir_step_y[(((u16)player->facing) >> 9) & 7];
                    target_pos->unk_06.u += tile_step_2 << 6;
                    target_pos->unk_0A.s = ((u16)player->ground_height);
                }
                target_pos->unk_0A.s = get_surface_height_at_record(target_pos);
                if (target_pos->unk_0A.u >= 0x201) {
                    ActorRecord *player;
                    player = primary_actor_record;
                    target_pos->unk_0A.s = ((u16)player->ground_height);
                }

                if ((check_left_tile_and_center_height(target_pos->unk_02.s, target_pos->unk_06.s,
                                    target_pos->unk_0A.u) << 16) != 0) {
                    ActorRecord *player;

                    player = primary_actor_record;
                    tile_step_3 = dir_step_x[(((u16)player->facing) >> 9) & 7];
                    target_pos->unk_02.u -= tile_step_3 << 6;
                    tile_step_4 = dir_step_y[(((u16)player->facing) >> 9) & 7];
                    target_pos->unk_06.u -= tile_step_4 << 6;
                    target_pos->unk_0A.s = ((u16)player->ground_height);
                    target_pos->unk_0A.s = get_surface_height_at_record(target_pos);
                    if (target_pos->unk_0A.u >= 0x201) {
                        ActorRecord *height_player;
                        height_player = primary_actor_record;
                        target_pos->unk_0A.s = ((u16)height_player->ground_height);
                    }
                    break;
                }
            }
        }

        func_80025A9C(self, position, target_pos);
        {
            u16 next_state = self->state;
            u16 wait_frames;
            wait_frames = 0x10;
            self->timer = wait_frames;
            self->state = next_state + 1;
        }
        break;

    case 3:
        timer = self->timer;
        timer--;
        self->timer = timer;
        if ((s32)((u32)timer << 16) > 0) {
            break;
        }
        {
            u16 next_state = 0x18;
            void *child_object;

            self->timer = next_state;
            next_state = self->state;
            child_object = self->object;
            next_state++;
            self->state = next_state;
            if (child_object != 0) {
                func_80025508(self, *(void **)((u8 *)child_object - 0x18));
            }
        }
        break;

    case 4:
        {
            S_81978428_8 *tinted_object = self->object;

            if (tinted_object != 0) {
                u8 *reloaded_object;
                s16 tint_timer;

                tinted_object->unk_1C |= 0x10000000;
                tint_timer = self->timer;
                reloaded_object = *(u8 **)((u8 *)self + 0x14);
                tint_data = *(u8 **)(reloaded_object - 0x14);
                if (tint_timer >= 0xC) {
                    u8 blue = tint_data[0xE] + 8;
                    tint_data[0xE] = blue;
                    if (tint_data[0xC] >= 0xE1) {
                        tint_data[0xC] = 0xE0;
                    }
                } else {
                    u8 blue = tint_data[0xE] - 8;
                    tint_data[0xE] = blue;
                    if (blue < 0x80) {
                        tint_data[0xE] = 0x80;
                    }
                }
            }
        }

        {
            u32 map_flags = reference_tile_object.sprite_flags;
            if ((map_flags & 0x8000) == 0) {
                timer = self->timer;
                timer--;
                self->timer = timer;
                if ((s32)((u32)timer << 16) >= 0) {
                    break;
                }
            }
        }

        {
            u8 *effect_object = self->object;

            if (effect_object != 0) {
                s32 effect_size = 10;
                s32 effect_scale;
                effect_scale = effect_size;
                apply_attack_power_and_element_effects(self->object, effect_size, self->effect, effect_scale,
                              (s16)((self->angle << 9) + 0x800), self->part0, 1);
                {
                    u32 clear_tint_mask = 0xEFFFFFFF;
                    u32 neutral_color = 0x00808080;
                    u8 *reset_object = self->object;
                    tint_data = *(u8 **)(reset_object - 0x14);

                    ((S_81978428_9 *)reset_object)->unk_1C &= clear_tint_mask;
                    ((S_81978428_10 *)tint_data)->unk_0C = neutral_color;
                }
            }
        }
        if (self->flag != 0) {
            self->state++;
            break;
        }
        g_dungeon_status.active_actor = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        ((S_81978428_12_pre *)self)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;

    case 5:
        if (self->flag != 0) {
            break;
        }

        g_dungeon_status.active_actor = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count--;
        ((S_81978428_12_pre *)self)[-1].unk_00 |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    self->flag = 0;
}
