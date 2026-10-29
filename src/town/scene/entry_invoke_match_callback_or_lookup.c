#include "common.h"
#include "shared/town_scene_image.h"
#include "town/scene.h"

extern void forward_scene_inputs_b(void);

/* The scene image's two entry records (include/shared/town_scene_image.h); the entry
 * functions are this image's own code at its 0x80016000 load base. */
const TownSceneEntry D_80016004[2] __attribute__((aligned(4))) = {
    { 0x4C070707, invoke_match_callback_or_lookup, 0x1 },
    { 0x4C070707, forward_scene_inputs_b, 0x10F48 },
};
