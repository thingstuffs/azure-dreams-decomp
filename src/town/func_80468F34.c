#include "common.h"
#include "m2c_compat.h"
void func_80019D60(void *);                   /* extern */
extern M2C_UNK D_80017BA0;

/* Pass D_80017BA0 to func_80019D60. */
void apply_global_delta_record_a(void) {
    func_80019D60(&D_80017BA0);
}
