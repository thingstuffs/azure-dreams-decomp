#ifndef DUNGEON_LEVEL_DEPTH_BIASED_SPRITE_RENDERING_G00350_H
#define DUNGEON_LEVEL_DEPTH_BIASED_SPRITE_RENDERING_G00350_H
/* Depth biased sprite rendering shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800B6D74. */

#include "common.h"
#include "slus/data.h"
#include "shared/game_work.h"
#include "shared/gpu_packets.h"
#include "dungeon/level.h"
#include "sdk/libgpu.h"
#include "sdk/libgte.h"

typedef struct S_800BC3E4_0_pre {
    void * unk_00;
    u8 pad_04[0x4];
} S_800BC3E4_0_pre;

/* node in traverse_nodes_and_render_unflagged */
typedef struct S_800BC3E4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800BC3E4_1;

/* primitive in traverse_nodes_and_render_unflagged */
typedef struct S_800BC3E4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800BC3E4_3;

/* packet + 7 in render_projected_sprite_with_depth_bias */
typedef struct S_800BC4D4_6 {
    u16 unk_00;
} S_800BC4D4_6;

extern s32 is_frame_packet_arena_overflowed(void *); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void func_80067EF4(void *, s32, s32);

/* Functions defined in this translation unit. */

#endif
