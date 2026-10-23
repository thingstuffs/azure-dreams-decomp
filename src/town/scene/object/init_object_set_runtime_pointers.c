#include "common.h"
#include "shared/record_ptrs.h"

typedef struct TownRuntime {
    u8 pad_00[0x28];
    void *field_28;
    void *field_2C;
    u8 pad_30[4];
    void *field_34;
} TownRuntime;

extern s16 scene_dependency_ids[3];
extern s32 D_8001C370;
extern u8 D_8001C480[0x10];
extern u8 D_8001DA10;
extern u8 scene_object_image_data;
extern u8 D_8001DCD0;

extern void update_dependent_entry_ids(s16 checked_id, s16 first_id, s16 second_id);
extern void initialize_active_event_data(void);
extern void build_object_set_and_select_lists(s32, void *, void *);

/* Initializes town resources and stores their pointers in the runtime. */
void init_object_set_runtime_pointers(void) {
    s16 *position;
    TownRuntime *runtime;

    position = scene_dependency_ids;
    update_dependent_entry_ids(scene_dependency_ids[0], position[1], position[2]);
    initialize_active_event_data();
    build_object_set_and_select_lists(D_8001C370, D_8001C480, &D_8001DA10);
    runtime = *(TownRuntime **)((u8 *)(&town_scene_root));
    runtime->field_28 = D_8001C480;
    runtime->field_34 = &scene_object_image_data;
    runtime->field_2C = &D_8001DCD0;
}
