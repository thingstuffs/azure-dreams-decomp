#ifndef DUNGEON_OVL_C9B084_H
#define DUNGEON_OVL_C9B084_H
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/point_tile_scratch.h"


s32 queue_linked_render_packets(u8 *entry_data, u16 *position);
#endif
