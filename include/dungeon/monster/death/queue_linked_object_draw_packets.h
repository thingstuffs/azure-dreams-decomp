#ifndef DUNGEON_OVL_BF9084_H
#define DUNGEON_OVL_BF9084_H
#include "shared/gpu_packets.h"
#include "common.h"
#include "shared/game_work.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"
#include "sdk/libgte_matrix.h"
#include "sdk/libgpu_types.h"
#include "sdk/libgpu_packets.h"
#include "dungeon/effect/point_tile_scratch.h"


/* Queues projected point primitives and draw modes for a linked list. */

s32 queue_linked_object_draw_packets(u8 *item, u16 *coords);
#endif
