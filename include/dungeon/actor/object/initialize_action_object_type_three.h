#ifndef DUNGEON_OVL_16B08_LOCAL_H
#define DUNGEON_OVL_16B08_LOCAL_H
#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80094268_arg0.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6D14_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6DBC_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6EC0_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6F00_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6F40_InitState;
void call_the_handler_selects_nonzero_entry();
extern void update_movement_and_expire_state(void);
extern M2C_UNK D_800D00A0;
void dispatch_sound_by_global_flag();
extern void update_actor_and_dispatch_state(void);
extern M2C_UNK D_800D00B0;
extern void update_threshold_and_interaction(void);
extern void update_countdown_and_fallback(void);
extern M2C_UNK D_800D00C0;
extern void update_threshold_bound_object(void);
extern u8 D_800D00B8[16];
void store_the_valid_shared_angle_in_offset_hex_10();
extern void update_actor_movement_actions(void);
extern M2C_UNK D_800D0108;
s16 SD_Call();
extern void update_actor_input_actions(void);
extern M2C_UNK D_800D0110;
extern u8 D_800D0118[];
extern void dispatch_actor_interaction_with_fallback(void);
extern void update_actor_with_interaction_state(void);
extern M2C_UNK D_800D0120;
extern u8 D_800D0128[];
extern void update_actor_movement_and_interaction(void);
extern void update_actor_position_and_interaction(void);
extern M2C_UNK D_800D0130;
extern void update_town_object_from_input(void);
extern M2C_UNK D_800D0140;
extern u8 D_800D0148[];
extern void update_threshold_object_with_interaction(void);
extern void update_actor_movement_with_radial_effects(void);
extern u8 D_800D0138[];
extern void update_threshold_countdown_with_busy_check(void);
extern void update_actor_interaction_actions(void);
void initialize_action_object_type_three(Rec_func_80094268_arg0 *object);
void initialize_actor_action_state(Rec_func_80094268_arg0 *object, EntityRec *state, M2C_UNK setupArg);
void initialize_threshold_interaction_action(Rec_func_8009431C_arg0 *record);
void initialize_action_object_type_six(Rec_func_80094268_arg0 *object);
void initialize_action_object(M2C_UNK **object);
void func_800943B8(Rec_func_80094268_arg0 *object, M2C_UNK setup_arg, M2C_UNK context, M2C_UNK setup_extra);
void initialize_action_object_and_play_sound(M2C_UNK **object, M2C_UNK unused, M2C_UNK context);
void initialize_action_handler_with_count_six(ovl_16b08_local_7FFF6D14_InitState *state, void *unused, void *context);
void initialize_action_object_with_counter(Rec_func_80094268_arg0 *object, M2C_UNK unused, M2C_UNK context);
void initialize_actor_movement_interaction_action(ovl_16b08_local_7FFF6DBC_InitState *state, void *unused, void *context);
void initialize_actor_position_interaction_action(Rec_func_80094268_arg0 *object, M2C_UNK setup_arg, M2C_UNK context, M2C_UNK setup_extra);
void initialize_input_driven_scene_object(M2C_UNK **outputSlot, EntityRec *state, M2C_UNK initContext);
void initialize_threshold_interaction_object(ovl_16b08_local_7FFF6EC0_InitState *state, void *unused, void *context);
void initialize_action_callback_from_entry(ovl_16b08_local_7FFF6F00_InitState *state, void *unused, void *context);
void initialize_busy_checked_countdown_action(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context);
void initialize_actor_interaction_state_19(Rec_func_80094268_arg0 *record);
#endif
