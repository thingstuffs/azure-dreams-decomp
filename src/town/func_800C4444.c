#include "common.h"
#include "m2c_compat.h"

extern unsigned char D_800717D0[16];
extern M2C_UNK D_800D4398;

/* Handle the koya_into_exe script call. */
void koya_into_exe(void) {
    func_8003AF58(D_800717D0, &D_800D4398);
}
