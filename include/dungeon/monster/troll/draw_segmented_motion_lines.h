#ifndef DUNGEON_MONSTER_TROLL_DRAW_SEGMENTED_MOTION_LINES_H
#define DUNGEON_MONSTER_TROLL_DRAW_SEGMENTED_MOTION_LINES_H
#include "common.h"
#include "shared/entity.h"
#include "shared/vector.h"
#include "shared/gpu_packets.h"
#include "shared/sprite_frame_state.h"

/* Effect body drawn as a segmented line: the motion vector at +0x58 runs
 * from the effect origin; the renderer reads the integer half of each axis. */
typedef struct SegmentedLineState {
    u8 pad_00[0x58];
    Fixed1616 vector_x;
    Fixed1616 vector_y;
    Fixed1616 vector_z;
} SegmentedLineState;

/* Flat-shaded two-point line packet (LINE_F2, three command words). */
typedef struct SegmentedLinePacket {
    GpuLinkTag tag;
    SpriteColor color;
    s32 xy0;
    s32 xy1;
} SegmentedLinePacket;

/* Draw-mode packet queued after the lines (two command words). */
typedef struct SegmentedLineDrawMode {
    GpuLinkTag tag;
    s32 command[2];
} SegmentedLineDrawMode;

/* Projection workspace in the scratchpad while the lines are built. */
typedef struct SegmentedLineScratch {
    u8 pad_00[0x24];
    union { int *words; GpuLinkTag *links; } ordering_table;
    u16 flags;
    u8 pad_2A[0xA];
    IntVector3 scale;
    u8 pad_40[0x14];
    GteMatrix transform;
    GteMatrix rotation;
    u8 pad_94[0x10];
    GteShortVector angles;
    u8 pad_AC[4];
    GteShortVector point[4];
    s32 projection;
    s32 projection_flags;
    u8 pad_D8[0x28];
    s32 depth;
} SegmentedLineScratch;

/* The scratchpad RAM holding SegmentedLineScratch. */
#define SEGMENTED_LINE_SCRATCH ((SegmentedLineScratch *)0x1F800000)

#endif
