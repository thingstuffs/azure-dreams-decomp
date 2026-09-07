#include "common.h"

#ifdef NON_MATCHING
#define LEGACY_ASM_KEEP(value) ((void)0)
static volatile s32 hidden_v1;
#elif __GNUC__ < 3
#define LEGACY_ASM_KEEP(value) __asm__ __volatile__("" : "=r"(value) : "0"(value))
register s32 hidden_v1 ASM_REG("$3");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
#else
#define LEGACY_ASM_KEEP(value) ASM_KEEP(value)
s32 hidden_v1;
#endif

extern void *func_800B515C(void);

void *func_800B512C(void *arg0, s16 arg1) {
    if (arg1 < 300) {
        s32 quotient = arg1 / 4;

        hidden_v1 = quotient + 1;
        return func_800B515C();
    }

    hidden_v1 = 64;
    {
        u8 *base = arg0;
        s32 zero = 64;

        LEGACY_ASM_KEEP(zero);
        zero -= hidden_v1;
        base[2] = zero;
        {
            void *result = base;

            LEGACY_ASM_KEEP(result);
            base[10] = hidden_v1;
            LEGACY_ASM_KEEP(base);
            return result;
        }
    }
}
