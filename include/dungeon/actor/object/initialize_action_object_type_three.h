#ifndef DUNGEON_OVL_16B08_LOCAL_H
#define DUNGEON_OVL_16B08_LOCAL_H
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "records/Rec_func_8009431C_arg0.h"
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6D14_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6DBC_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6EC0_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6F00_InitState;
typedef struct { void *callback; u8 pad4[6]; s16 count; } ovl_16b08_local_7FFF6F40_InitState;
void dispatch_selected_entry_if_nonzero();
extern void update_movement_and_expire_state(void);
extern s32 type_three_action_handler_table[];
void play_sound_by_height_range(void);
extern void update_actor_and_dispatch_state(void);
extern s32 D_800D00B0[];
extern void update_airborne_object_with_land_timer(TownObjectRecord *state, ObjectPosition *entity, SpriteFrameState *context);
extern void update_countdown_and_fallback(void);
extern s32 D_800D00C0[];
extern void update_airborne_object_with_land_effects(void *context, ObjectPosition *object, void *update_arg);
extern u8 action_object_handler_table[16];
void store_input_angle(void *record_arg);
extern void update_actor_movement_actions(void);
extern s32 D_800D0108[];
s16 SD_Call(int flags);
extern void update_actor_input_actions(void);
extern s32 D_800D0110[];
extern u8 D_800D0118[];
extern void dispatch_actor_interaction_with_fallback(void);
extern void update_actor_with_interaction_state(TownObjectRecord *controller, ObjectPosition *entity, SpriteFrameState *context);
extern s32 counted_action_handler_table[];
extern u8 movement_action_handler_table[];
extern void update_actor_movement_and_interaction(void *actor, ObjectPosition *position, s32 context);
extern void update_actor_position_and_interaction(TownObjectRecord *actor, ObjectPosition *body, s32 context);
extern s32 D_800D0130[];
extern void update_town_object_from_input(void *context, ObjectPosition *object, void *action_data);
extern s32 D_800D0140[];
extern u8 D_800D0148[];
extern void update_threshold_object_with_interaction(void);
extern void update_actor_movement_with_radial_effects(s32 object_id, ObjectPosition *object, s32 update_context);
extern u8 countdown_action_handler_table[];
extern void update_ground_countdown_unless_busy(void *state, ObjectPosition *object, s32 context);
extern void update_actor_interaction_actions(void *self_arg, ObjectPosition *target_arg, SpriteFrameState *sprite);
void initialize_action_object_type_three(TownObjectRecord *object);
void initialize_actor_action_state(TownObjectRecord *object, EntityRec *state, s32 setupArg);
void initialize_threshold_interaction_action(Rec_func_8009431C_arg0 *record);
void initialize_action_object_type_six(TownObjectRecord *object);
void initialize_action_object(s32 **object);
void initialize_movement_actions(TownObjectRecord *object, s32 setup_arg, s32 context, s32 setup_extra);
void initialize_action_object_and_play_sound(s32 **object, s32 unused, s32 context);
void initialize_interaction_fallback_action(ovl_16b08_local_7FFF6D14_InitState *state, void *unused, void *context);
void initialize_action_object_with_counter(TownObjectRecord *object, s32 unused, s32 context);
void initialize_actor_movement_interaction_action(ovl_16b08_local_7FFF6DBC_InitState *state, void *unused, void *context);
void initialize_actor_position_interaction_action(TownObjectRecord *object, s32 setup_arg, s32 context, s32 setup_extra);
void initialize_input_driven_scene_object(s32 **outputSlot, EntityRec *state, s32 initContext);
void initialize_threshold_interaction_object(ovl_16b08_local_7FFF6EC0_InitState *state, void *unused, void *context);
void init_radial_effects_action(ovl_16b08_local_7FFF6F00_InitState *state, void *unused, void *context);
void initialize_busy_checked_countdown_action(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context);
void install_actor_interaction_handler(TownObjectRecord *record);
#endif
