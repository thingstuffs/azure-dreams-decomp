#ifndef DUNGEON_PLAYER_CAMERA_DEPTH_PRESETS_DATA_H
#define DUNGEON_PLAYER_CAMERA_DEPTH_PRESETS_DATA_H

#include "common.h"
#include "engine/camera/interpolation.h"

/* Dungeon view-depth presets at 0x800DD26C. */
extern s16 camera_depth_presets[];

/* Rotation targets at 0x800DCE60 precede the depth halfword.
 * The independently bound camera_depth_target starts at offset six. */
typedef struct DungeonCameraTargets {
    CameraRotationTarget rotation;
    s16 depth;
} DungeonCameraTargets;

extern DungeonCameraTargets dungeon_camera_targets;

#endif
