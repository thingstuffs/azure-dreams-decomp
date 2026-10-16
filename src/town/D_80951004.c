#include "common.h"
#include "shared/town_scene_image.h"

extern void townInvokeMatchCallbackOrLookup(void);
extern void townForwardSceneInputsB(void);

/* The scene image's two entry records (include/shared/town_scene_image.h); the entry
 * functions are this image's own code at its 0x80016000 load base. */
const TownSceneEntry D_80016004[2] __attribute__((aligned(4))) = {
    { 0x4C070707, townInvokeMatchCallbackOrLookup, 0x1 },
    { 0x4C070707, townForwardSceneInputsB, 0x10F48 },
};
