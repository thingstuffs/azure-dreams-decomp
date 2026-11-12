#ifndef DUNGEON_OVL_BF3084_H
#define DUNGEON_OVL_BF3084_H
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/point_tile_scratch.h"


/* Builds and links rendering packets for a chain of positioned entries. */

s32 queue_linked_render_packets(u8 *entry, u16 *position);
#endif
