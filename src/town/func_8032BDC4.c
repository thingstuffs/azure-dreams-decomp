#include "common.h"

/* Calls townSetScriptFlagBit with the fixed argument 0xD8A. */
void townDispatchEventD8A(void) {
    townSetScriptFlagBit(0xD8A);
}
