#ifndef ENGINE_SCENE_SCENE_LOAD_H
#define ENGINE_SCENE_SCENE_LOAD_H
#include "common.h"
#include "shared/object_node.h"
/* Scene-load body prefix shared by the load and completion callbacks. */
typedef struct SceneLoadBody {
    ObjectNodeHeader *parent;
    ObjectNodeHeader *task;
    void *result;
    s32 unk_0C;
} SceneLoadBody;
void propagate_task_flag_to_parent(SceneLoadBody *record);
#endif
