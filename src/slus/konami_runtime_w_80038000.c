#include "common.h"

#include "common.h"

extern s8 D_80082B4B;

/* mes_skip_disable_set: Sets the message skip disable flag. */
void func_80038000(s8 skip_disabled) {
    D_80082B4B = skip_disabled;
}
