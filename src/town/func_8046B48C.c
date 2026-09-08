#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8001E670();                         /* extern */
extern s16 D_8001792C;

/* Pass the current value of D_8001792C to func_8001E670. */
void func_8001C48C(void) {
    func_8001E670(D_8001792C);
}
