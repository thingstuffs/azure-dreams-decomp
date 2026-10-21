#include "common.h"
void func_80090A64(void);
#include "records/Rec_func_80094268_arg0.h"
void initialize_scene_action_record(Rec_func_80094268_arg0 *record, void *ptr, void *ptr2);
extern s32 *town_player_action_callback;

/* Initializes the output pointer and the shared data pointer. */
void initialize_shared_scene_data(s32 **out_ptr) {
    *out_ptr = &func_80090A64;
    town_player_action_callback = &initialize_scene_action_record;
}
