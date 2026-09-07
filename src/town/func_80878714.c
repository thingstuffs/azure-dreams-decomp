#include "common.h"

extern s32 *D_807030A4[];
extern void func_8070276C(void) __attribute__((noreturn));

s32 func_80702714(s32 arg0)
{
    register s32 input ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 one;
    register s32 value ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 *ptr;
    s32 word;
    unsigned long offset;

    input = arg0;
    one = 1;
    if (input != 0) {
        if (input != one) {
            word = input;
            if (input < 0) {
                word = input + 31;
            }
            value = word >> 5;
            offset = value << 2;
            value <<= 5;
            offset += (unsigned long)D_807030A4[0];
            value = input - value;
            value = one << value;
            ptr = (s32 *)offset;
            value &= *ptr;
            ASM_TAILSLOT_PIN_TIED(value);   /* MATCH pin: retail immediate-load split depends on it */
            func_8070276C();
        }
        {
            register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
#ifdef NON_MATCHING
            zero = 0;
#endif
            value = zero + 1;
            ASM_TAILSLOT_PIN_TIED(value);   /* MATCH pin: retail immediate-load split depends on it */
            func_8070276C();
        }
    }
    {
        register s32 zero ASM_REG("$0");   /* MATCH pin: retail immediate-load split depends on it */
#ifdef NON_MATCHING
        zero = 0;
#endif
        return zero;
    }
}

/* MECHANISM: Nested nonzero/default fallthrough gives the frameless retail CFG; loading
   the table base before remainder formation fills its delay slot with the subu.
   Tied v0 tail pins form both jumps, while block-local $zero carriers force literal
   addiu/move materialization without fencing a2 out of the first branch delay. */
