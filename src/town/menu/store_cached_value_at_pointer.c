#include "common.h"

extern s32 D_80126A60;
extern s32 *D_8012974C;

/* Store D_80126A60 at the location pointed to by D_8012974C. */
void store_cached_value_at_pointer(void) {
    *D_8012974C = D_80126A60;
}
