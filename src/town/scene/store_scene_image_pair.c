#include "common.h"
#include "sdk/libgpu.h"
#include "town/scene.h"

extern SceneImageRect D_800D43B0;
extern SceneImageRect D_800D43B8;

/* Save both scene image rectangles, waiting for each VRAM transfer. */
void store_scene_image_pair(void) {
    StoreImage(&D_800D43B0, SCENE_IMAGE_BUFFER_0);
    DrawSync(0);
    StoreImage(&D_800D43B8, SCENE_IMAGE_BUFFER_1);
    DrawSync(0);
}
