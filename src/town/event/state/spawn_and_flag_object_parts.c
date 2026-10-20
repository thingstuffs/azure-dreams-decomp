#include "common.h"

extern void SD_Call(s32 flags);
extern void spawn_randomized_effect_parts(void *source_data, s32 spawn_arg);
extern void unlink_scene_list_node(void *node);
extern void unlink_node_if_registered(void *block_data);
extern void run_the_follow_up_action_has_eligible_type_passes_check(s32 check_value);
struct S_800814A0 {
    s32 v;
    s32 pad[2];
};
extern struct S_800814A0 D_800814A0;

/* Process an object action and set the object and global 0x8000 flags. */
void spawn_and_flag_object_parts(unsigned short *object, s32 unused, s32 action_id)
{
    SD_Call(0x600);
    spawn_randomized_effect_parts(object, action_id);
    unlink_scene_list_node(object);
    unlink_node_if_registered(object);
    object[-1] |= 0x8000;
    D_800814A0.v |= 0x8000;
    run_the_follow_up_action_has_eligible_type_passes_check(action_id);
}
