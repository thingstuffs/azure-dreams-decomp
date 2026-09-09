#include "common.h"

extern s32 rand(void);

/* Returns twice the signed 16-bit base plus 0-8, randomly negated and truncated to 16 bits. */
s32 func_81088650(s32 base)
{
    s32 random_roll;
    s16 result;
    s32 offset;

    result = base;
    random_roll = rand();
    offset = (random_roll % 9) + ((result << 16) >> 15);
    result = offset;
    if (rand() & 1) {
        result = -offset;
    }
    return (result << 16) >> 16;
}
