#include "common.h"
#include "town/scene.h"
#include "sdk/libgpu.h"

typedef SceneImageRect RECT;

extern RECT D_800D43B0;
extern RECT D_800D43B8;

/* Upload both sb01_over_push images to VRAM, waiting for each transfer. */
void sb01_over_push(void) {
    LoadImage(&D_800D43B0, SCENE_IMAGE_BUFFER_0);
    DrawSync(0);
    LoadImage(&D_800D43B8, SCENE_IMAGE_BUFFER_1);
    DrawSync(0);
}
