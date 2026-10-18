#include "common.h"

/* Existing-identity bank: words 0..84 are byte-proven data, not C code. */
extern s32 D_80126A60;
extern s32 *D_8012974C;

void store_cached_value_at_pointer(void);
/* Store D_80126A60 at the destination pointed to by D_8012974C. */
void store_cached_value_at_pointer(void) {
    *D_8012974C = D_80126A60;
}
