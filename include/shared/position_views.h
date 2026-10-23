#ifndef SHARED_POSITION_VIEWS_H
#define SHARED_POSITION_VIEWS_H
#include "common.h"


/* Exact access views shared across registered binary consumers. */
/* Unsigned countdown/state halfword at +A; preserves wrap and signed tests at each use. */
typedef struct UnsignedCountdownView {
    unsigned char pad_00[0xA];
    unsigned short unk_0A;
} UnsignedCountdownView;

/* Signed integer halves at +2/+6/+A in a twelve-byte position projection. */
/* Signed integer halves of a position supplied by the caller; this view owns no separate allocation. */
typedef struct SignedPositionView {
    unsigned char pad_00[0x2];
    short x; /* signed integer X component, in world units */
    unsigned char pad_04[0x2];
    short y; /* signed integer Y component, in world units */
    unsigned char pad_08[0x2];
    short z; /* signed integer height component, in world units */
} SignedPositionView;

/* Signed position integer half at +A; never substituted with an unsigned height view. */
/* Signed height projection of a caller-owned position record; no separate allocation. */
typedef struct SignedHeightView {
    unsigned char pad_00[0xA];
    short z; /* signed integer height component, in world units */
} SignedHeightView;

/* Three signed motion words at +C/+10/+14, preserving the sparse 0x18 extent. */
/* Three motion increments within a caller-owned position record.
 * add_motion_deltas_to_position adds them to the corresponding 16.16 coordinates. */
typedef struct MotionDeltaView {
    unsigned char pad_00[0xC];
    int velocity_x; /* X increment per motion update, in 16.16 world units */
    int velocity_y; /* Y increment per motion update, in 16.16 world units */
    int velocity_z; /* height increment per motion update, in 16.16 world units */
} MotionDeltaView;

/* Unsigned dungeon status flags and pending action count; the legacy view name is retained. */
typedef struct UnsignedPositionXZView {
    unsigned char pad_00[2];
    unsigned short flags;
    unsigned char pad_04[6];
    unsigned short pending_action_count;
} UnsignedPositionXZView;

#endif
