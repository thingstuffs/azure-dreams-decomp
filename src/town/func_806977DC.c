#include "common.h"
#include "m2c_compat.h"
void func_800171B8(void *);                   /* extern */
extern M2C_UNK D_80018AE8;

/* Passes D_80018AE8 to func_800171B8. */
void func_806977DC(void) {
    func_800171B8(&D_80018AE8);
}
