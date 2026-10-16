#include "common.h"

extern u8 D_80408ADC[];

/* Jump to the code entry 0x280 bytes before D_80408ADC. */
void cardBootJumpToMenuCodeEntry(void)
{
    goto *(void *)(D_80408ADC - 0x280);
}
