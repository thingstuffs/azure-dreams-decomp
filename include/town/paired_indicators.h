#ifndef TOWN_PAIRED_INDICATORS_H
#define TOWN_PAIRED_INDICATORS_H

#include "common.h"
#include "shared/object_node.h"

/* The two indicator callbacks read these owner values for blinking and reveal. */
typedef struct IndicatorOwner {
    u8 pad_00[0x62];
    u16 blink_flags;
    u16 value;
} IndicatorOwner;

/* Both town indicator initializers fill two position triples. Their child
 * callbacks copy one triple into ObjectPosition and mirror the hidden bit. */
typedef struct PairedIndicators {
    IndicatorOwner *owner;
    s16 first_x;
    s16 first_y;
    s16 first_z;
    u8 pad_0A[2];
    s16 second_x;
    s16 second_y;
    s16 second_z;
    u8 pad_12[2];
    s32 blink_color;
    s16 state;
    u16 blink_ticks;
    s16 first_target_z;
    s16 second_target_z;
    u16 threshold;
    s16 kind;
    u16 flags;
} PairedIndicators;

/* ObjectNodeHeader precedes this body; nonzero selects the first indicator. */
typedef struct IndicatorChild {
    PairedIndicators *source;
    u8 pad_04[4];
    s16 use_first;
} IndicatorChild;

typedef struct IndicatorChildNode {
    ObjectNodeHeader header;
    IndicatorChild work;
} IndicatorChildNode;

#endif
