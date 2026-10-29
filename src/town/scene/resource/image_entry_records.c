#include "common.h"
#include "shared/town_scene_image.h"
#include "town/scene/flags.h"
#include "town/scene/object.h"

/* The scene image's two entry records (include/shared/town_scene_image.h); the entry
 * functions are this image's own code at its 0x80016000 load base. */
const TownSceneEntry D_80016004[2] __attribute__((aligned(4))) = {
    { 0x4C070707, init_object_set_runtime_pointers_rev_b, 0x1 },
    { 0x4C070707, dispatch_flag_test_state, 0x10F48 },
};
