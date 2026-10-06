#include "common.h"
#include "m2c_compat.h"

typedef struct S_800491F4 S_800491F4;
S_800491F4 *func_800491F4();          /* extern */
extern M2C_UNK D_80028094;

/* Forwards input to func_800491F4 with D_80028094 and the fixed argument 4. */
void func_80027254(void * input) {
    func_800491F4(input, &D_80028094, 4);
}
