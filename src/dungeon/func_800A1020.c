#include "common.h"

/* Sets the enable flag for mode 1, or mode 0 when incrementing the value preserves its quotient by five. */
s32 func_800A6780(void) {
    register s8 *flagBase ASM_REG("$7") = (s8 *)0x80080000;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 *stateBase ASM_REG("$3") = (s32 *)0x80010000;   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    s32 enabledValue;
    s32 mode;
    s32 boundaryValue;

    ASM_KEEP(flagBase);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(stateBase);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    mode = stateBase[0x2090 / 4];
    enabledValue = 1;
    flagBase[0xA88] = 0;
    if (mode != enabledValue) {
        if (mode != 0) {
            return 0;
        }
        boundaryValue = stateBase[0x234 / 4];
        if (boundaryValue / 5 != (boundaryValue + 1) / 5) {
            return 0;
        }
    }
    flagBase[0xA88] = enabledValue;
    return 1;
}
