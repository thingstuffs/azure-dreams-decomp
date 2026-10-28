#include "dungeon/monster/beldo_large.h"
#include "shared/runtime_dispatch.h"
#include "shared/sprite_frame_state.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "shared/dir_step.h"
#include "shared/entity_objects.h"
#include "shared/record_ptrs.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_800E3D7C.h"
#include "dungeon/player/item.h"
#include "sdk/libgte.h"
#include "dungeon/system.h"

typedef struct S_80171D74_0 {
    s32 unk_00;
} S_80171D74_0;   /* D_8008333C in advance_linked_actor_motion_script */


typedef struct S_80171D74_2 {
    u8 pad_00[0x8];
    void * unk_08;
} S_80171D74_2;   /* D_80175D50[0] in advance_linked_actor_motion_script */


typedef struct S_80171D74_4 {
    u8 pad_00[0x2A];
    union { u16 n; u16 v; } unk_2A;   /* accessed as both */
    u8 pad_2C[0x5C];
    u16 unk_88;
} S_80171D74_4;

typedef struct S_80171D74_6 {
    s16 unk_00;
} S_80171D74_6;   /* D_80083228 in advance_linked_actor_motion_script */

typedef struct S_80171D74_7 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    s32 unk_08;
} S_80171D74_7;

typedef struct S_80171D74_8 {
    u8 pad_00[0x27];
    u8 unk_27;
    u8 pad_28[0x2];
    u16 unk_2A;
} S_80171D74_8;

typedef struct S_80171D74_10 {
    u8 pad_00[0x32];
    s16 unk_32;
} S_80171D74_10;   /* D_80175DB8[0] in advance_linked_actor_motion_script */

typedef struct S_80171D74_11 {
    s16 unk_00;
    u16 unk_02;
} S_80171D74_11;   /* sp2_base16 in advance_linked_actor_motion_script */

typedef struct S_80171D74_13 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_13;

typedef struct S_80171D74_14 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_14;

typedef struct S_80171D74_15 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_15;

typedef struct S_80171D74_16 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_16;

typedef struct S_80171D74_17 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_17;

typedef struct S_80171D74_18 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_18;

typedef struct S_80171D74_19 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_19;

typedef struct S_80171D74_20 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_20;

typedef struct S_80171D74_21 {
    u8 pad_00[0x4];
    u16 unk_04;
} S_80171D74_21;

typedef struct { u32 v; } __attribute__((packed)) UA32;
typedef struct { UA32 word[8]; } __attribute__((packed)) Table32;

typedef struct { s16 x; u16 y; } ScriptDirection;

#define SP1_X_AT(base, a) (((ScriptDirection *)((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C)))->x)
#define SP1_Y_AT(base, a) (((ScriptDirection *)((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C)))->y)
#define SP2_X_AT(base, a) (((ScriptDirection *)((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C)))->x)
#define SP2_Y_AT(base, a) (((ScriptDirection *)((u8 *)(base) + ((((u16)(a)) >> 7) & 0x1C)))->y)

void request_scene_state_with_parameters(u16, s16, s16, s16, s32); /* extern */
#include "engine/texture/select_indirect_table_entry_api.h"              /* extern */
#include "engine/graphics/select_sprite_entry_api.h"         /* extern */
#include "slus.h"
void snapshot_inventory_and_familiars();                 /* extern */
s32 is_special_floor_entry_absent();                      /* extern */
void create_rotating_clipped_sprite(u32 *, s16);             /* extern */
struct S_8016738C_3; void create_color_cycling_pulse(struct S_8016738C_3 *);                      /* extern */
struct EntityRec; void create_layered_sprite_pulse(struct EntityRec *);                      /* extern */
void create_forward_layered_sprite_pulse();                  /* extern */
struct S_8016F5D8_0; struct S_8016F5D8_1; struct S_8016F5D8_2; void update_phase_driven_motion_offset(struct S_8016F5D8_1 *, struct S_8016F5D8_2 *, struct S_8016F5D8_0 *);      /* extern */
void apply_script_direction_record(void *, u8 *, void *);      /* extern */
void create_action_offset_object(void);                            /* extern */
extern Table32 D_8016482C;
extern Table32 D_80164AC0;
extern u8 beldo_large_frame_set_8[16];
extern u8 D_80173DAC[16];
extern u8 beldo_large_frame_set_14[16];
extern void *beldo_actor_nodes[3];
extern void *beldo_script_node[3];
extern void *encounter_offset_object[16];

/* Advances a scripted movement sequence and updates the sprite facing. */
/* Runs Beldo's timed leaps, turns, and sprite effects, changes map flags, and saves party state for a
 * scene change. */
void advance_linked_actor_motion_script(ActorRecord *state_in, ObjectPosition *motion_in, SpriteFrameState *sprite_in) {
    Table32 offset_table;
    Table32 direction_table;
    s16 right_angle;
    s16 quarter_turn;
    s16 sprite_dir;
    s16 turn_frame;
    s16 spin_frame;
    s16 owner_height;
    s16 turn_value;
    s16 facing_angle;
    s32 speed;
    MapGrid *map_info;
    s32 map_tiles;
    u16 left_angle;
    u16 wait_frame;
    u16 return_frames;
    u16 arc_frame;
    u16 approach_frames;
    u16 bounce_frame;
    u16 spin_up_frame;
    u16 launch_frame;
    u16 hop_frame;
    u16 wobble_frame;
    u16 frame_or_height;
    u16 spiral_frame;
    u16 effect_wait_frame;
    u16 rise_frame;
    u16 finish_frame;
    u16 pause_frame;
    u16 sway_frame;
    u16 lift_frame;
    u16 slide_frame;
    u16 appear_frame;
    u16 travel_frame;
    u16 turned_angle;
    u16 old_angle;
    s32 phase;
    s32 hop_vel_y;
    s32 launch_vel_y;
    S_80171D74_8 *target_state;
    s32 launch_vel_z;
    s32 hop_vel_z;
    S_80171D74_4 *owner_state;
    S_80171D74_7 *target_pos;
    S_80171D74_13 *tile_nw;
    S_80171D74_14 *tile_n;
    S_80171D74_15 *tile_ne;
    S_80171D74_16 *tile_w;
    S_80171D74_17 *tile_center;
    S_80171D74_18 *tile_e;
    S_80171D74_19 *tile_sw;
    S_80171D74_20 *tile_s;
    S_80171D74_21 *tile_se;
    s32 angle_tmp;

    offset_table = *((Table32 *)(&D_8016482C));
    direction_table = *((Table32 *)(&D_80164AC0));
    map_info = &g_game_work.map;
    map_tiles = ((S_80171D74_0 *)((s32 *)(&g_game_work.map)))->unk_00;
    owner_state = beldo_script_node[0] + 0x20;
    advance_sprite_animation_and_textures(sprite_in);
    phase = state_in->action_id.u;
    target_pos = ((S_80171D74_2 *)(beldo_actor_nodes[0]))->unk_08;
    target_state = beldo_actor_nodes[0] + 0x20;
    switch (phase) {
    case 0:
        wait_frame = state_in->action_timer.u;
        state_in->action_timer.u = (u16) (wait_frame + 1);
        if ((s16) wait_frame >= 0x1E) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_y = (s32) 0xFFF80000;
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 1:
        motion_in->y.v = motion_in->y.v
        + motion_in->velocity_y;
        rise_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = rise_frame;
        if ((s16) rise_frame >= 0x38) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_x = 0;
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 2:
        pause_frame = state_in->action_timer.u;
        state_in->action_timer.u = (u16) (pause_frame + 1);
        if ((s16) pause_frame >= 0x1E) {
            u8 next_phase;
            next_phase = state_in->action_id.u;
            state_in->action_timer.u = 0U;
            next_phase = next_phase + 1;
            state_in->action_id.u = (u8) next_phase;
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 3:
        sway_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = sway_frame;
        if ((s16) sway_frame == 3) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n + 0x200);
        }
        if ((s16) state_in->action_timer.u == 4) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n + 0x200);
        }
        if ((s16) state_in->action_timer.u == 0x12) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n - 0x200);
        }
        if ((s16) state_in->action_timer.u == 0x14) {
            owner_state->unk_2A.n = (u16) (owner_state->unk_2A.n - 0x200);
        }
        if ((s16) state_in->action_timer.u == 0x1E) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_x = 0;
            motion_in->velocity_y = (s32) 0xFFF80000;
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 4:
        motion_in->y.v = motion_in->y.v
        + motion_in->velocity_y;
        lift_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = lift_frame;
        if ((s16) lift_frame >= 0x10) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_x = 0;
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 6:
        sprite_in->frameTable = &D_80173DAC;
        select_sprite_entry(sprite_in, D_80173DAC[((s32) (((S_80171D74_6 *)((s16 *)(&g_game_work.view.camera_rotation.parts.viewAngle)))->unk_00
            + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 3);
        state_in->action_timer.u = 0U;
        state_in->action_id.u = (u8) (state_in->action_id.u + 1);
        motion_in->velocity_x = (s32) 0x00020000;
        break;
    case 7:
        motion_in->x.v = (s32) (motion_in->x.v
            + motion_in->velocity_x);
        slide_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = slide_frame;
        if ((s16) slide_frame >= 8) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_x = 0;
            sprite_in->flags = (u16) (sprite_in->flags | 0x80);
            motion_in->y.w.i = 1;
            motion_in->x.w.i = 1U;
        }
        if ((s16) state_in->action_timer.u == 3) {
            create_rotating_clipped_sprite((u32 *)(target_pos), 0);
            create_rotating_clipped_sprite((u32 *)(target_pos), 1);
            create_color_cycling_pulse((struct S_8016738C_3 *)(target_pos));
            create_layered_sprite_pulse((struct EntityRec *)(target_pos));
        }
        break;
    case 9:
        create_forward_layered_sprite_pulse(phase, target_state);
        state_in->action_timer.u = 0;
        state_in->action_id.u++;
        break;
    case 10:
        appear_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = appear_frame;
        if ((s16) appear_frame >= 2) {
            u8 *offset_base = (u8 *)&offset_table;
            u8 *direction_base;
            s32 angle_input_m;
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            sprite_in->flags = (u16) (sprite_in->flags & 0xFF7F);
            motion_in->x.w.i = (u16) (target_pos->unk_00.at02.v + (SP1_X_AT(offset_base,
                target_state->unk_2A) * 0x28));
            motion_in->y.w.i = (s16) (target_pos->unk_04.at02.v + ((s16) SP1_Y_AT(offset_base,
                target_state->unk_2A) * 0x28));
            state_in->unk_90.parts.high.s = -0x18;
            state_in->unk_9E.s = 0;
            state_in->unk_A0.value = 0;
            angle_input_m = target_state->unk_2A;
            angle_tmp = angle_input_m - 0x400;
            angle_input_m = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_input_m = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_input_m;
            state_in->unk_94 = 1;
            sprite_in->frameTable = &beldo_large_frame_set_14;
            select_sprite_entry(sprite_in, beldo_large_frame_set_14[((s32) (((S_80171D74_6 *)((s16 *)(&g_game_work.view.camera_rotation.parts.viewAngle)))->unk_00
                + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
            direction_base = (u8 *)&direction_table;
            motion_in->velocity_x = (s32) (0 - (SP2_X_AT(direction_base, owner_state->unk_2A.n) << 0x10));
            motion_in->velocity_y = (void *) (0 - (SP2_Y_AT(direction_base, owner_state->unk_2A.n)
                << 0x10));
            create_action_offset_object();
            update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        }
        break;
    case 11:
        {
            s32 pos_x = motion_in->x.v;
            s32 vel_x = motion_in->velocity_x;
            s32 pos_y = motion_in->y.v;
            s32 vel_y = motion_in->velocity_y;
            motion_in->x.v = pos_x + vel_x;
            motion_in->y.v = pos_y + vel_y;
        }
        travel_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = travel_frame;
        if ((s16) travel_frame >= 0x14) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 13:
        old_angle = owner_state->unk_2A.n;
        turned_angle = old_angle + 0x200;
        owner_state->unk_2A.n = turned_angle;
        if ((s16) turned_angle >= 0x1000) {
            owner_state->unk_2A.n = (u16) (old_angle - 0xE00);
        }
        state_in->action_timer.u = 0U;
        state_in->action_id.u = (u8) (state_in->action_id.u + 1);
        target_state->unk_27 = 3;
        goto shared_tail;
    case 15:
        state_in->action_timer.u = 0x1EU;
        state_in->action_id.u = (u8) (state_in->action_id.u + 1);
                    /* fallthrough */
    case 16:
        motion_in->velocity_x = (((Rec_D_800E3D7C *)(((s32 *)(&view_reference_entity))))->unk_00.at00_vs32.v - motion_in->x.v) / (s16) state_in->action_timer.u;
        motion_in->velocity_y = (view_reference_entity.y.v - motion_in->y.v) / (s16) state_in->action_timer.u;
        motion_in->x.v += motion_in->velocity_x;
        motion_in->y.v += motion_in->velocity_y;
        return_frames = state_in->action_timer.u - 1;
        state_in->action_timer.u = return_frames;
        if ((return_frames << 0x10) <= 0) {
            u8 *direction_entry;
            s32 angle_input_m;
            u32 direction_offset;
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            ((S_80171D74_10 *)(encounter_offset_object[0]))->unk_32 = 3;
            sprite_in->frameTable = &beldo_large_frame_set_8;
            select_sprite_entry(sprite_in, beldo_large_frame_set_8[((s32) (((S_80171D74_6 *)((s16 *)(&g_game_work.view.camera_rotation.parts.viewAngle)))->unk_00
                + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
            angle_input_m = owner_state->unk_2A.n;
            angle_tmp = angle_input_m + 0x200;
            angle_input_m = angle_tmp;
            if ((s16) angle_tmp >= 0x1000) {
                angle_input_m = angle_tmp - 0x1000;
            }
            direction_offset = (u16) angle_input_m >> 7;
            direction_offset &= 0x1C;
            direction_entry = (u8 *)&direction_table;
            direction_entry += direction_offset;
            motion_in->velocity_x = (s32) (((S_80171D74_11 *)direction_entry)->unk_00 << 0x10);
            motion_in->velocity_y = (s32) (((S_80171D74_11 *)direction_entry)->unk_02 << 0x10);
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 17:
        {
            s32 pos_x = motion_in->x.v;
            s32 vel_x = motion_in->velocity_x;
            s32 pos_y = motion_in->y.v;
            s32 vel_y = motion_in->velocity_y;
            motion_in->x.v = pos_x + vel_x;
            motion_in->y.v = pos_y + vel_y;
        }
        {
            s32 height_offset;
            u16 next_frame;
            height_offset = state_in->unk_90.parts.high.u;
            next_frame = state_in->action_timer.u;
            height_offset = height_offset - 2;
            next_frame = next_frame + 1;
            arc_frame = next_frame;
            state_in->action_timer.u = arc_frame;
            state_in->unk_90.parts.high.u = height_offset;
        }
        if ((s16) arc_frame >= 0x28) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_y = 0;
            motion_in->velocity_x = 0;
        }
        turn_frame = (s16) state_in->action_timer.u;
        if ((turn_frame == 0xA) || (turn_frame == 0x14) || (turn_frame == 0x1E)) {
            s32 angle_input_m;
            angle_input_m = owner_state->unk_2A.n;
            angle_tmp = angle_input_m - 0x200;
            angle_input_m = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_input_m = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_input_m;
            if ((s16) state_in->action_timer.u == 0x1E) {
                play_sound_if_enabled(0x81A);
            }
        }
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 19:
        state_in->action_timer.u = 0x14U;
        state_in->action_id.u = (u8) (state_in->action_id.u + 1);
        tile_nw = ((0x1F << map_info->shiftX) * 6) + map_tiles + 0xBA;
        tile_nw->unk_04 = (u16) (tile_nw->unk_04 & 0x7FFF);
        tile_n = ((0x1F << map_info->shiftX) * 6) + map_tiles + 0xC0;
        tile_n->unk_04 = (u16) (tile_n->unk_04 & 0x7FFF);
        tile_ne = ((0x1F << map_info->shiftX) * 6) + map_tiles + 0xC6;
        tile_ne->unk_04 = (u16) (tile_ne->unk_04 & 0x7FFF);
        tile_w = ((0x20 << map_info->shiftX) * 6) + map_tiles + 0xBA;
        tile_w->unk_04 = (u16) (tile_w->unk_04 & 0x7FFF);
        tile_center = ((0x20 << map_info->shiftX) * 6) + map_tiles + 0xC0;
        tile_center->unk_04 = (u16) (tile_center->unk_04 & 0x7FFF);
        tile_e = ((0x20 << map_info->shiftX) * 6) + map_tiles + 0xC6;
        tile_e->unk_04 = (u16) (tile_e->unk_04 & 0x7FFF);
        tile_sw = ((0x21 << map_info->shiftX) * 6) + map_tiles + 0xBA;
        tile_sw->unk_04 = (u16) (tile_sw->unk_04 & 0x7FFF);
        tile_s = ((0x21 << map_info->shiftX) * 6) + map_tiles + 0xC0;
        tile_s->unk_04 = (u16) (tile_s->unk_04 & 0x7FFF);
        tile_se = ((0x21 << map_info->shiftX) * 6) + map_tiles + 0xC6;
        tile_se->unk_04 = (u16) (tile_se->unk_04 & 0x7FFF);
        motion_in->velocity_x = (s32) target_pos->unk_00.at00.v;
        motion_in->velocity_y = (void *) target_pos->unk_04.at00.v;
        motion_in->velocity_z = (void *) target_pos->unk_08;
                    /* fallthrough */
    case 20:
        motion_in->x.v += (motion_in->velocity_x
            - motion_in->x.v) / (s16) state_in->action_timer.u;
        motion_in->y.v += (motion_in->velocity_y
            - motion_in->y.v) / (s16) state_in->action_timer.u;
        motion_in->z.v += (motion_in->velocity_z
            - motion_in->z.v) / (s16) state_in->action_timer.u;
        approach_frames = state_in->action_timer.u - 1;
        state_in->action_timer.u = approach_frames;
        if ((approach_frames << 0x10) <= 0) {
            state_in->action_timer.u = 0;
            state_in->action_id.u++;
        }
        break;
    case 21:
        if (sprite_in->unk_04 == 0) {
            sprite_in->flags = (u16) (sprite_in->flags | 0x800);
        }
        break;
    case 22:
        {
            u16 next_frame;
            if (sprite_in->unk_04 == 0) {
                sprite_in->flags = (u16) (sprite_in->flags | 0x800);
                bounce_frame = state_in->action_timer.u;
                next_frame = bounce_frame + 1;
            } else {
                bounce_frame = state_in->action_timer.u;
                next_frame = bounce_frame + 1;
            }
            state_in->action_timer.u = next_frame;
            if ((u32) (bounce_frame - 0xA) < 8U) {
                state_in->unk_A0.value = (s32) (rsin(((s32) (next_frame << 0x10) >> 8) - 0xA00)
                    << 8);
                motion_in->z.w.i = (u16) (owner_state->unk_88
                    - state_in->unk_A0.parts.high);
            }
        }
        spin_frame = (s16) state_in->action_timer.u;
        if ((spin_frame == 0x19) || (spin_frame == 0x1E) || (spin_frame == 0x23) || (spin_frame == 0x28)) {
            s32 angle_input_m;
            angle_input_m = owner_state->unk_2A.n;
            angle_tmp = angle_input_m - 0x200;
            angle_input_m = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_input_m = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_input_m;
        }
        if ((s16) state_in->action_timer.u >= 0x2D) {
            state_in->action_timer.u = 0U;
            state_in->unk_90.parts.high.s = -0x18;
            state_in->unk_9E.s = 0;
            state_in->unk_A0.value = 0;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->z.w.i = owner_state->unk_88;
        }
        break;
    case 24:
        spin_up_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = spin_up_frame;
        if (((s16) spin_up_frame == 5) || ((s16) spin_up_frame == 0xA) || ((s16) spin_up_frame == 0xF)
            || ((s16) spin_up_frame == 0x14)) {
            s32 angle_input_m;
            angle_input_m = owner_state->unk_2A.n;
            angle_tmp = angle_input_m - 0x200;
            angle_input_m = angle_tmp;
            if ((angle_tmp << 0x10) < 0) {
                angle_input_m = angle_tmp + 0x1000;
            }
            owner_state->unk_2A.n = angle_input_m;
        }
        if ((s16) state_in->action_timer.u >= 0x18) {
            u8 *direction_base;
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            sprite_in->frameTable = &beldo_large_frame_set_8;
            sprite_in->flags = (u16) (sprite_in->flags & 0xF7FF);
            select_sprite_entry(sprite_in, beldo_large_frame_set_8[((s32) (((S_80171D74_6 *)((s16 *)(&g_game_work.view.camera_rotation.parts.viewAngle)))->unk_00
                + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
            direction_base = (u8 *)&direction_table;
            motion_in->velocity_x = (s32) (SP2_X_AT(direction_base, owner_state->unk_2A.n) << 0x14);
            motion_in->velocity_y = (s32) (SP2_Y_AT(direction_base, owner_state->unk_2A.n) << 0x14);
            motion_in->velocity_z = (void *)0xFFF00000;
        }
        break;
    case 25:
        launch_vel_y = motion_in->velocity_y;
        launch_vel_z = motion_in->velocity_z;
        motion_in->x.v = (s32) (motion_in->x.v
            + motion_in->velocity_x);
        motion_in->y.v = (void *) (motion_in->y.v + launch_vel_y);
        motion_in->z.v = (void *) (motion_in->z.v + launch_vel_z);
        launch_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = launch_frame;
        if ((s16) launch_frame >= 0x28) {
            state_in->action_timer.u = 0;
            state_in->action_id.u++;
        }
        break;
    case 30:
        {
            u8 *direction_base;
            u16 angle;
            u16 direction_y;
            angle = owner_state->unk_2A.v;
            direction_base = (u8 *)&direction_table;
            motion_in->velocity_x = (s32) (SP2_X_AT(direction_base, angle) << 0x13);
            direction_y = SP2_Y_AT(direction_base, owner_state->unk_2A.n);
            motion_in->velocity_z = (void *)0xFFFB0000;
            motion_in->velocity_y = (void *) (direction_y << 0x13);
            state_in->action_timer.u = 0;
            state_in->action_id.u++;
            break;
        }
    case 31:
        hop_vel_y = motion_in->velocity_y;
        hop_vel_z = motion_in->velocity_z;
        motion_in->x.v = (s32) (motion_in->x.v
            + motion_in->velocity_x);
        motion_in->y.v = (void *) (motion_in->y.v + hop_vel_y);
        motion_in->z.v = (void *) (motion_in->z.v + hop_vel_z);
        hop_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = hop_frame;
        if ((s16) hop_frame >= 5) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_z = 0;
            motion_in->velocity_y = 0;
            motion_in->velocity_x = 0;
        }
        break;
    case 32:
        wobble_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = wobble_frame;
        if (((s16) wobble_frame == 2) || ((s16) wobble_frame == 8) || ((s16) wobble_frame == 0xA)
            || ((s16) wobble_frame == 0x10) || ((s16) wobble_frame == 0x12)) {
            turn_value = owner_state->unk_2A.n;
            right_angle = turn_value + 0x200;
            turn_value = right_angle;
            if (right_angle >= 0x1000) {
                turn_value = right_angle - 0x1000;
            }
            owner_state->unk_2A.n = (u16) turn_value;
        }
        turn_value = (s16) state_in->action_timer.u;
        if ((turn_value == 4) || (turn_value == 6) || (turn_value == 0xC) || (turn_value == 0xE) || (turn_value == 0x14)) {
            turn_value = owner_state->unk_2A.n;
            left_angle = turn_value - 0x200;
            turn_value = left_angle;
            if ((s16) left_angle < 0) {
                turn_value = left_angle + 0x1000;
            }
            owner_state->unk_2A.n = turn_value;
        }
        turn_value = (s16) state_in->action_timer.u;
        if (turn_value == 0x1A) {
            sprite_in->frameTable = &beldo_large_frame_set_8;
            sprite_in->flags = (u16) (sprite_in->flags & 0xF7FF);
            select_sprite_entry(sprite_in, beldo_large_frame_set_8[((s32) (((S_80171D74_6 *)((s16 *)(&g_game_work.view.camera_rotation.parts.viewAngle)))->unk_00
                + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7], 0);
        }
        if ((s16) state_in->action_timer.u >= 0x1E) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            motion_in->velocity_z = (void *)0xFFF80000;
        }
        break;
    case 33:
        motion_in->z.v = (void *) (motion_in->z.v
            + motion_in->velocity_z);
        frame_or_height = state_in->action_timer.u + 1;
        state_in->action_timer.u = frame_or_height;
        if ((s16) frame_or_height >= 0xA) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            frame_or_height = ((u16) motion_in->z.w.i);
            motion_in->velocity_z = 0;
            motion_in->velocity_y = 0;
            motion_in->velocity_x = 0;
            owner_height = owner_state->unk_88;
            state_in->unk_9E.s = 0;
            state_in->unk_A0.value = 0;
            state_in->unk_90.parts.high.u = (u16) (frame_or_height - owner_height);
            facing_angle = owner_state->unk_2A.n;
            quarter_turn = facing_angle + 0x400;
            facing_angle = quarter_turn;
            if (quarter_turn >= 0x1000) {
                facing_angle = quarter_turn - 0x1000;
            }
            owner_state->unk_2A.n = (u16) facing_angle;
            select_sprite_entry(sprite_in, *(*(u8 **)&sprite_in->frameTable
                + (((s32) (((S_80171D74_6 *)((s16 *)(&g_game_work.view.camera_rotation.parts.viewAngle)))->unk_00 + facing_angle + 0x100)
                    >> 9) & 7)), 0);
        }
        break;
    case 34:
        {
            spiral_frame = state_in->action_timer.u + 1;
            state_in->action_timer.u = spiral_frame;
            if ((spiral_frame & 3) == 3) {
                s32 angle_input_m;
                angle_input_m = owner_state->unk_2A.n;
                angle_tmp = angle_input_m - 0x200;
                angle_input_m = angle_tmp;
                if ((angle_tmp << 0x10) < 0) {
                    angle_input_m = angle_tmp + 0x1000;
                }
                owner_state->unk_2A.n = angle_input_m;
            }
            speed = ((0x61 - (s16) state_in->action_timer.u) * 0x60000) / 97;
            {
                u8 *direction_base = (u8 *)&direction_table;
                s32 direction_x = SP2_X_AT(direction_base, owner_state->unk_2A.n);
                motion_in->velocity_x = speed * direction_x;
                angle_tmp = (s32)&direction_table;
                {
                    s16 direction_y = (s16) SP2_Y_AT(angle_tmp, owner_state->unk_2A.n);
                    motion_in->velocity_y = speed * direction_y;
                }
                motion_in->x.v += motion_in->velocity_x;
                motion_in->y.v += motion_in->velocity_y;
            }
            if ((s16) state_in->action_timer.u >= 0x58) {
                state_in->action_timer.u = 0U;
                state_in->action_id.u = (u8) (state_in->action_id.u + 1);
                {
                    motion_in->x.w.i = ((u16)view_reference_entity.x.w.i);
                    motion_in->y.w.i = ((u16)view_reference_entity.y.w.i);
                }
            }
        }
    case 5:
    case 12:
    case 14:
    case 18:
shared_tail:
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 40:
        if ((is_special_floor_entry_absent(phase, target_state) << 0x10) != 0) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        }
        break;
    case 41:
        effect_wait_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = effect_wait_frame;
        if ((s16) effect_wait_frame >= 0x3C) {
            state_in->action_timer.u = 0;
            state_in->action_id.u++;
        }
        break;
    case 45:
        if ((is_special_floor_entry_absent(phase, target_state) << 0x10) != 0) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
            g_dungeon_status.activity_counts.parts.pending_action_count = (u16) (((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1);
        }
        apply_script_direction_record(state_in, motion_in, sprite_in);
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 46:
        finish_frame = state_in->action_timer.u + 1;
        state_in->action_timer.u = finish_frame;
        if ((s16) finish_frame >= 0x3C) {
            state_in->action_timer.u = 0U;
            state_in->action_id.u = (u8) (state_in->action_id.u + 1);
        }
        apply_script_direction_record(state_in, motion_in, sprite_in);
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;
    case 35:
        apply_script_direction_record(state_in, motion_in, sprite_in);
        update_phase_driven_motion_offset(state_in, motion_in, sprite_in);
        break;

    case 42:
        snapshot_inventory_and_familiars(((s32)dungeon_actor_ring_anchor), target_state);
        snapshot_inventory_familiar_records();
        runtime_dispatch_state.flags16 = 0x8000;
        request_scene_state_with_parameters(6, 0, 0, 0, 0x8000);
        state_in->action_id.u++;
        break;
    case 47:
        snapshot_inventory_and_familiars(((s32)dungeon_actor_ring_anchor), target_state);
        snapshot_inventory_familiar_records();
        runtime_dispatch_state.flags16 = 0x8000;
        request_scene_state_with_parameters(6, 0, 0, 0, 0x8000);
        state_in->action_id.u++;
        break;
    case 48:
    default:
            break;
    }
    if (beldo_script_node[0] != 0) {
        sprite_dir = ((s32) (((S_80171D74_6 *)((s16 *)(&g_game_work.view.camera_rotation.parts.viewAngle)))->unk_00
            + (s16) owner_state->unk_2A.n + 0x100) >> 9) & 7;
        if (state_in->unk_94 != sprite_dir) {
            select_indirect_table_entry(sprite_in, *(*(u8 **)&sprite_in->frameTable + sprite_dir),
                sprite_in->unk_04);
            state_in->unk_94 = sprite_dir;
        }
        {
            u16 sprite_flags;
            if ((*(u8 *)((u8 *)dir_sprite_flag + sprite_dir)) != 0) {
                sprite_flags = sprite_in->flags | 1;
            } else {
                sprite_flags = sprite_in->flags & 0xFFFE;
            }
            sprite_in->flags = sprite_flags;
        }
    }
    return;

}
