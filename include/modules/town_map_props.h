#ifndef MODULE_TOWN_MAP_PROPS_H
#define MODULE_TOWN_MAP_PROPS_H
#include "common.h"
#include "m2c_compat.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "records/Rec_D_80082E80.h"
typedef struct TownPropPosition { s32 unk_00, unk_04, unk_08; } TownPropPosition;
struct S_800BDE7C_0;
struct TownGridOutputView;
struct S_800BDFA0_0;
struct TownPropAnimationActor;
struct TownPropAnimationDestination;
struct S_800BE214_0;
struct TrailHeightView;
void *create_positioned_graphic_object_2(TownPropPosition *position, s32 object_param, s32 graphics_id);
void *create_positioned_visual_object(TownPropPosition *position, s32 object_data, s32 angle, s32 visual_data);
void apply_item_and_update_matching_actor_state(s16 start_x, s16 start_y, s16 mode, s32 pair_index);
void fill_wrapped_four_by_four_grid(s32 start_x, s16 start_y, s32 unused_value);
void update_record_output_grid(struct S_800BDE7C_0 *record, s32 unused_value, struct TownGridOutputView *output, s32 unused_value2);
void no_op_effect_callback(void);
void initialize_record_visual_state(struct S_800BDFA0_0 *record, s32 unused, s32 value);
void copy_record_state_to_destination(struct TownPropAnimationActor *self, s32 unused_value, struct TownPropAnimationDestination *destination);
void advance_actor_animation_pose(struct S_800BE214_0 *actor, struct TrailHeightView *pose, Rec_D_80082E80 *animation);
void func_8003DB94(void *destination, void *animation, s16 mode);
void *allocate_list_node(s32 object_type, void *list);
void *func_8003FD64(s32 object_type, void *list);
s32 register_node(void *entry, s32 registration_id);
s32 func_8004491C(void *entry, s32 registration_id);
void func_800478B8(void *animation);
s32 check_transform_identifier_and_hook(s32 requested_id);
s32 service_script_controller(void);
s32 func_800352FC(void);
s32 func_80064584(s32 angle);
s32 rand(void);
s32 draw_linked_lit_meshes(void *group_data, void *position, void *render_data, s32 unused);
void randomize_paired_object_motion(void *pair);
void advance_motion_and_flag_zero_velocity(void *actor, void *motion, s32 actor_id);
void *memcpy(void *dst, const void *src, u32 n);
/* The caller's historical short arguments are explicit casts in its body.
 * The grid helper's third argument is passed by retail and unused by it. */
#endif
