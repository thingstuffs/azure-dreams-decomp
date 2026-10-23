#ifndef DUNGEON_OVL_7CE800_H
#define DUNGEON_OVL_7CE800_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "modules/dungeon_native_abi.h"
#include "shared/dungeon_moving_views.h"
extern void *active_action_object;
typedef union { u8 first; s8 bytes[9]; } DungeonFlagBuffer9;
extern DungeonFlagBuffer9 scripted_boundary_active;
void select_record_entry_and_value(void *,void *,s32);
struct ColorPart;
struct DungeonObject;
struct Position3;
struct S807AF9A4;
struct S_807AFB48_0;
struct S_807AFB48_2;

struct S_807AFC9C_4;
struct S_807B09A0_0;
struct UnkStruct807B11B8;
typedef struct DirectionOffsets {
    u16 x0;
    u16 y0;
    u16 x1;
    u16 y1;
    u16 x2;
    u16 y2;
    u16 x3;
    u16 y3;
    u16 x4;
    u16 y4;
    u16 x5;
    u16 y5;
    u16 x6;
    u16 y6;
    u16 x7;
    u16 y7;
} __attribute__((packed)) DirectionOffsets;
extern const DirectionOffsets dungeon_7ce800_directions;
void update_sprite_from_third_argument(M2C_UNK unused_first, M2C_UNK unused_second, M2C_UNK value);
void create_positioned_view_marker(s16 x, s16 y);
void advance_dungeon_tile_action_state(u8 *state, u8 *actor, u8 *target);
void create_slot_positioned_effect(s16 x, s16 y, s32 slot);
void update_overlay_state_and_retire(void *data);
void initialize_overlay_effect_state(void);
void mark_special_actors_and_set_player_tile(void);
void update_dungeon_tile_boundary_state(void *owner);
void create_tile_boundary_updater(void);
void mark_scripted_map_boundary(void);
s32 draw_linked_particle_effect_primitives(struct DungeonObject *object, u16 *origin);
void advance_linked_particle_effect_state(struct S807AF9A4 *data);
void create_linked_particle_controller(void *sourceData);
void converge_particle_position_and_color(void *transition, struct S_807AFB48_0 *position, struct S_807AFB48_2 *color);
void create_converging_color_particle(s32 spawn_arg, MovingPosition *origin, struct S_807AFC9C_4 *source);
void update_owner_attached_color_effect(void *effect, struct Position3 *position, struct ColorPart *tint);
void create_owner_attached_color_effect(void *parent_data);
void advance_reverse_direction_particle(void *motion_data, s16 *position);
void create_reverse_direction_particle(EntityRec *source, s16 state_value, s32 render_value);
void begin_active_object_action(void);
void func_800F7BA0(void);
void finish_active_object_action(void);
s32 update_special_actor_transition(void);
void reset_active_object_action(void);
void func_800F80F0(s16 tile_x, s16 tile_y, s16 initial_value);
void emit_scattered_animated_particles(struct S_807B09A0_0 *emitter);
s32 render_particle_effect_object(void *object, s32 caller_a1, void *caller_a2);
void move_sprite_until_animation_finishes(u16 *object_data, struct UnkStruct807B11B8 *motion, SpriteFrameState *update_state);
#endif
