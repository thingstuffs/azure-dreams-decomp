#include "common.h"
#include "shared/town_dispatch_data.h"
#include "town/scene/hooks.h"
void func_800171B8(void *);                   /* extern */

/* Passes D_80018AE8 to func_800171B8. */
void forward_shared_data(void) {
    func_800171B8(&D_80018AE8);
}
