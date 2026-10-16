#include "common.h"

/* Invokes townSetScriptFlagBit with code 0xDAF. */
void townDispatchEventDAF(void) {
    townSetScriptFlagBit(0xDAF);
}
