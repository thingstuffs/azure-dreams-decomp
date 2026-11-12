#ifndef DUNGEON_OVL_CA1084_H
#define DUNGEON_OVL_CA1084_H
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/point_tile_scratch.h"


s32 queue_linked_object_draw_packets(u8 *object_data, u16 *position);
#endif
