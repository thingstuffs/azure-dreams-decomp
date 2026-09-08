#include "common.h"
#include "m2c_compat.h"

typedef struct S_800A78AC_0_pre {
    u16 unk_00;
} S_800A78AC_0_pre;   /* the 0x2 bytes before arg0 in func_800A78AC, addressed as arg0[-1] */

typedef struct S_800A78AC_0 {
    u8 pad_00[0x50];
    M2C_UNK (*unk_50)();
} S_800A78AC_0;   /* arg0 in func_800A78AC */


M2C_UNK func_800478B8();                     /* extern */

/* Call the record handler and update its data if the record remains active. */
void func_800A78AC(void *record, M2C_UNK unused, M2C_UNK update_data) {
    M2C_UNK (*handler)();

    handler = ((S_800A78AC_0 *)record)->unk_50;
    if (handler != NULL) {
        handler();
        if (!(((S_800A78AC_0_pre *)record)[-1].unk_00 & 0x8000)) {
            func_800478B8(update_data);
        }
    }
}
