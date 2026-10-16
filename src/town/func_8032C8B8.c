#include "common.h"

extern s32 townGetScriptFlagMask(s32 flagIndex);
extern void townSetScriptFlagBit(s32 bit_index);
extern void townClearScriptFlagBit(s32 bit_index);
extern u8 D_8001E259[];
extern u8 D_8001E405[];

/* Select a handler and data pointer based on the query for 0xD53. */
void *townSelectHandlerDataForFlagD53(void) {
    if (townGetScriptFlagMask(0xD53) != 0) {
        townClearScriptFlagBit(0xD53);
        return D_8001E259;
    }
    townSetScriptFlagBit(0xD53);
    return D_8001E405;
}
