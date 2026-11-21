#ifndef TOWN_SCENE_POSITION_ENTRIES_H
#define TOWN_SCENE_POSITION_ENTRIES_H

#include "common.h"
#include "town/scene/motion.h"

typedef struct ScenePositionEntry {
    s16 id;
    s16 selector;
    s32 result;
} ScenePositionEntry;

/* Zero-terminated list of flags that must all be set before apply_entry_position sets the context flag. */
extern s16 scene_dispatch_context[];

long resolve_entry_with_override_49(void *context, s32 unused, s32 selection);

/* Placed entry points for apply_entry_position. */
s32 func_80018044(ScenePositionEntry *entries, void *object, void *context, s32 selection);
s32 func_800181C8(ScenePositionEntry *entries, void *object, void *context, s32 selection);
s32 func_800182E4(ScenePositionEntry *entries, void *object, void *context, s32 selection);

#endif
