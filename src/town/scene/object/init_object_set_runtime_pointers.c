#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene/flags.h"
#include "town/scene/event.h"
#include "town/scene.h"
#include "town/scene/object.h"
#include "town/map/variant_data.h"
#include "shared/town_root.h"
#include "town/data.h"

extern TownSpawnEntry D_8001C480[];
extern u32 D_8001DA10[];
extern TownObjectSet *D_8001C370;
extern u8 D_8001DCD0;

/* Initializes town resources and stores their pointers in the runtime. */
void init_object_set_runtime_pointers(void) {
    s16 *position;
    Rec_D_80016000 *runtime;

    position = scene_dependency_ids;
    update_dependent_entry_ids(scene_dependency_ids[0], position[1], position[2]);
    initialize_active_event_data();
    build_object_set_and_select_lists((s32 *)D_8001C370, D_8001C480, D_8001DA10);
    runtime = town_scene_root;
    runtime->unk_28 = D_8001C480;
    runtime->unk_34 = scene_object_image_data;
    runtime->unk_2C = &D_8001DCD0;
}
