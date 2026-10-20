#include "common.h"
#include "m2c_compat.h"
void func_80019D60(void *);                   /* extern */
extern M2C_UNK D_80017BAC;

/* Passes D_80017BAC to func_80019D60. */
void apply_global_delta_record_k(void) {
    func_80019D60(&D_80017BAC);
}
