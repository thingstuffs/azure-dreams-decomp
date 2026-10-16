#include "common.h"

/* Call townGetScriptFlagMask with request 0xD82. */
void townQueryEventD82(void) {
    townGetScriptFlagMask(0xD82);
}
