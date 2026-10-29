#ifndef DUNGEON_OVL_7F469800_P03_H
#define DUNGEON_OVL_7F469800_P03_H
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "records/Rec_D_80082E80.h"
#include "records/Rec_func_80172CC0_arg0.h"

typedef struct T_80172CC0_S_80172CC0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x28];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x18];
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} T_80172CC0_S_80172CC0_0;   /* state in func_80172CC0 */


typedef struct T_80172CC0_S_80172CC0_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} T_80172CC0_S_80172CC0_2;   /* entry in func_80172CC0 */


typedef struct T_80172CC0_S_80172CC0_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} T_80172CC0_S_80172CC0_4;   /* (u8 *)state + ((T_80172CC0_S_80172CC0_0 *)state)->unk_8A.s in func_80172CC0 */





#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/dir_step.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "dungeon/level/room_flags.h"
#include "shared/actor_action_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status.h"
#include "shared/object_node.h"

#ifndef NULL
#define NULL 0
#endif













typedef struct T_80173734_S_80173734_0 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 unk_48;
    u8 pad_49[0x17];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x10];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    s16 unk_88;
} T_80173734_S_80173734_0;   /* arg3 in func_80173734 */


typedef struct T_80173734_S_80173734_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} T_80173734_S_80173734_2;   /* arg2 in func_80173734 */

typedef struct T_80173734_S_80173734_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
    s16 unk_AC;
} T_80173734_S_80173734_3;   /* arg0 in func_80173734 */

typedef struct T_80173734_S_80173734_4_pre {
    void * unk_00;
    u8 pad_04[0x10];
} T_80173734_S_80173734_4_pre;   /* the 0x14 bytes before ((T_80173734_S_80173734_0 *)arg3)->unk_60 in func_80173734, addressed as ((T_80173734_S_80173734_0 *)arg3)->unk_60[-1] */






typedef struct T_80173B48_S_80173B48_0 {
    u8 pad_00[0x14];
    u32 unk_14;
    u8 pad_18[0x12];
    s16 unk_2A;
    u8 pad_2C[0x1C];
    u8 unk_48;
    u8 pad_49[0x17];
    void * unk_60;
    u8 pad_64[0x6];
    u16 unk_6A;
    u8 pad_6C[0x1];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    s8 unk_72;
    s8 unk_73;
    u8 pad_74[0x10];
    u8 unk_84;
    u8 unk_85;
    u8 pad_86[0x2];
    s16 unk_88;
} T_80173B48_S_80173B48_0;   /* arg3 in func_80173B48 */

typedef struct T_80173B48_S_80173B48_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0xE];
    s16 unk_AA;
    s16 unk_AC;
} T_80173B48_S_80173B48_1;   /* arg0 in func_80173B48 */

typedef struct T_80173B48_S_80173B48_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} T_80173B48_S_80173B48_2;   /* arg2 in func_80173B48 */

typedef struct T_80173B48_S_80173B48_3_pre {
    void * unk_00;
    u8 pad_04[0x10];
} T_80173B48_S_80173B48_3_pre;   /* the 0x14 bytes before ((T_80173B48_S_80173B48_0 *)arg3)->unk_60 in func_80173B48, addressed as ((T_80173B48_S_80173B48_0 *)arg3)->unk_60[-1] */




extern void select_sprite_entry(void *object, s16 table_index, s16 entry_index);
extern void func_80047784(SpriteFrameState *object, s16 table_index, s16 entry_index);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);
extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s16 check_movement_clearance_and_height();
extern s32 check_entity_relation();
extern s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
extern s16 get_actor_height_difference(ActorRecord *left_record, ActorRecord *right_record);
extern s32 update_actor_proximity_flag(void *source, void *state, s32 lower_limit, s32 upper_limit, s8 *result);
extern s32 generate_random_value(void);
extern void update_actor_status_and_mp(ActorRecord *entity);
extern s16 sample_terrain_surface_height();
extern void resolve_attack_damage_and_effects(void *, void *, s16, s16);
extern void prepare_directional_attack(void *, void *, s16, s16, void *);
extern s16 get_tile_chebyshev_distance(void *, void *);
extern s16 try_claim_dungeon_action_slot(ActorRecord *actor);
extern s32 check_entity_interaction_compatibility(void *, void *);
extern void setup_object_within_planar_range(void *, s32, s32, s16, s32, s32);
extern void apply_camera_offset_and_select_target(void *,void *, s32, s32);
extern s32 troll_stored_path_frames;
extern s32 troll_frame_set;
extern s32 troll_frame_set_4;
extern s16 actor_turn_angle_offsets[];
extern u8 D_80175E9C[];
extern u8 D_80175EA4[];
extern u8 D_80175EAC[];
extern u16 direction_x_offsets[];
extern u16 direction_y_offsets[];
void advance_actor_stored_path_2(ActorRecord *movement, ObjectPosition *actor_index, SpriteFrameState *actor, ActorRecord *path_state);
void reset_actor_directional_animation(ActorRecord *state, ObjectPosition *unused, SpriteFrameState *display, ActorRecord *entity);
#endif
