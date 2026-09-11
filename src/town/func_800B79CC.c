#include "common.h"

#ifdef NON_MATCHING
#define ASM_KEEP(value) ((void)0)
static volatile s32 hidden_v1;
#elif __GNUC__ < 3
#define ASM_KEEP(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
register s32 hidden_v1 ASM_REG("$3");
#else
#define LEGACY_ASM_KEEP(value) ASM_KEEP(value)
s32 hidden_v1;
#endif

/* Set two entry bytes to complementary values derived from the amount. */
void *func_800B512C(void *entry, s16 amount) {
    u8 *base = entry;
    s32 remaining;

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
