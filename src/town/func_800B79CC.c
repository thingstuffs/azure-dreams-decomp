#include "common.h"

/* Set two entry bytes to complementary values derived from the amount. */
void *func_800B512C(void *entry, s16 amount) {
    u8 *base = entry;
    s32 remaining;
    s32 hidden_v1;

    if (amount < 300) {
        s32 quotient = amount / 4;

        hidden_v1 = quotient + 1;
    } else {
        hidden_v1 = 64;
    }

    remaining = 64;
    remaining -= hidden_v1;
    base[2] = remaining;
    {
        void *result = base;

        base[10] = hidden_v1;
        return result;
    }
}
