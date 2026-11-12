#ifndef DUNGEON_OVL_BE7084_H
#define DUNGEON_OVL_BE7084_H
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/point_tile_scratch.h"


/* Builds and links render packets for a list of positioned entries. */

s32 queue_projected_point_primitives_2(u8 *entry_data, u16 *coords);
#endif
