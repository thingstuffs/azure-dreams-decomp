#include "common.h"
#include "town/devkit.h"
#include "town/data.h"

struct SceneEntry {
    u8 data[8];
};

extern SceneEntry D_80702BA8[];
extern u8 D_80702C00[];

/* Invoke runtime operation 6 for the scene entry mapped from the index. */
void invoke_indexed_runtime_operation(s32 scene_index)
{
    devkit_runtime_methods->invoke(6, &D_80702BA8[D_80702C00[scene_index]], 0);
}
