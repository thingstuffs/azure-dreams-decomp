#include "common.h"
#include "m2c_compat.h"

void townSetScriptFlagBit();                     /* extern */
extern M2C_UNK D_8001DCD4;

/* Passes two fixed IDs to townSetScriptFlagBit and returns the address of D_8001DCD4. */
M2C_UNK *townDispatchTwoEventsAndReturnBuffer(void) {
    townSetScriptFlagBit(0xDAC);
    townSetScriptFlagBit(0xD77);
    return &D_8001DCD4;
}
