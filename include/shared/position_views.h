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
typedef struct SignedPositionView {
    unsigned char pad_00[0x2];
    short unk_02;
    unsigned char pad_04[0x2];
    short unk_06;
    unsigned char pad_08[0x2];
    short unk_0A;
} SignedPositionView;

/* Signed position integer half at +A; never substituted with an unsigned height view. */
typedef struct SignedHeightView {
    unsigned char pad_00[0xA];
    short unk_0A;
} SignedHeightView;

/* Three signed motion words at +C/+10/+14, preserving the sparse 0x18 extent. */
typedef struct MotionDeltaView {
    unsigned char pad_00[0xC];
    int unk_0C;
    int unk_10;
    int unk_14;
} MotionDeltaView;

/* Unsigned X/Z position halves with an opaque middle coordinate. */
typedef struct UnsignedPositionXZView {
    unsigned char pad_00[2];
    unsigned short unk_02;
    unsigned char pad_04[6];
    unsigned short unk_0A;
} UnsignedPositionXZView;

#endif
