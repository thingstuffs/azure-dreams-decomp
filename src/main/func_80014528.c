#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80025C7C();                /* extern */
M2C_UNK func_80026868();                    /* extern */
void func_80027570() __attribute__((noreturn));                            /* extern */
M2C_UNK func_80027C90();                         
typedef struct S_80027528_0 {
    s32 unk_00;
    u8 pad_04[0x10];
    s32 unk_14;
} S_80027528_0;   /* arg0 in func_80027528 */

/* extern */

void func_80027528(void *arg0) {
    s32 temp_a1;

    func_80027C90(arg0 - 0x20);
    temp_a1 = ((S_80027528_0 *)arg0)->unk_00;
    if (temp_a1 == 0) {
        func_80025C7C(((S_80027528_0 *)arg0)->unk_14, 0);
        func_80027570();
    } else {
        func_80026868(((S_80027528_0 *)arg0)->unk_14, temp_a1);
    }
}
