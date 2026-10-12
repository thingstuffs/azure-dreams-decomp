#include "common.h"
#include "shared/town_scene_image.h"

extern void func_80016AF4(void);
extern void func_80016A94(void);

/* The scene image's two entry records (include/shared/town_scene_image.h); the entry
 * functions are this image's own code at its 0x80016000 load base. */
const TownSceneEntry D_80016004[2] __attribute__((aligned(4))) = {
    { 0x4C070707, func_80016AF4, 0x1 },
    { 0x4C070707, func_80016A94, 0x10F48 },
};
