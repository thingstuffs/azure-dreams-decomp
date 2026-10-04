#include "common.h"
#include "m2c_compat.h"

#include "common.h"

void func_8003AF58();        /* extern */
extern u8 D_8006AEAC[];
extern u8 D_800717D0[];

/* Passes D_8006AEAC and the shared D_800717D0 context to func_8003AF58. */
void func_8003B400(void) {
    func_8003AF58(&D_800717D0, &D_8006AEAC);
}
