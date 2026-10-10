/* Selector 59, retail file [0x1990FE8, 0x19910A8); complete callable clone. */
#include "common.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "modules/dungeon_native_abi.h"


/* 16.16 fixed-point coordinate: the whole part is the high halfword. */
typedef union FixedCoord {
    s32 fixed;
    struct {
        u16 frac;
        s16 whole;
    } part;
} FixedCoord;

typedef struct Bank1990800_1990fe8_EffectPosition {
    FixedCoord x;
    FixedCoord y;
    FixedCoord z;
} Bank1990800_1990fe8_EffectPosition;

/* The effect record the callback runs on (the object header precedes it). */
typedef struct Bank1990800_1990fe8_EffectState {
    u8 pad_00[0x32];
    s16 countdown;
    u8 pad_34[0x14];
    s32 height_step;    /* added to the position's z when it is below the floor */
} Bank1990800_1990fe8_EffectState;

/* Adjust height conditionally and set flags when the countdown reaches zero or below. */
void func_800247E8(Bank1990800_1990fe8_EffectState *state, Bank1990800_1990fe8_EffectPosition *position)
{
    s16 countdown;

    D_80025FF4 = 1;
    if (position->z.part.whole <
        (s16)func_800BCB04((u16)position->x.part.whole, (u16)position->y.part.whole, position->z.part.whole + 2)) {
        position->z.fixed += state->height_step;
    }

    countdown = (u16)state->countdown - 4;
    state->countdown = countdown;
    if ((countdown << 16) <= 0) {
        ((ObjectNodeHeader *)state - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}

