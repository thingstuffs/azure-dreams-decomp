#include "common.h"
#include "m2c_compat.h"

typedef struct S_80016DBC_0 {
    u8 pad_00[0x1C];
    void * unk_1C;
} S_80016DBC_0;   /* D_80016000 in func_80016DBC */

typedef struct S_80016DBC_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_80016DBC_1;   /* ((S_80016DBC_0 *)D_80016000)->unk_1C in func_80016DBC */




M2C_UNK func_80018F8C();                         /* extern */
s32 func_800198A4();                /* extern */
M2C_UNK func_8001A554();                     /* extern */
M2C_UNK func_8001A5CC();                     /* extern */
extern S_80016DBC_0 *D_80016000;
extern M2C_UNK D_8002116C;


/* Initializes resources and assigns their data pointer when lookup succeeds. */
void func_80016DBC(void) {
    s32 resource_id;

    resource_id = func_800198A4(0xD, 6);
    if (resource_id != -1) {
        func_80018F8C(resource_id);
        func_8001A554(0x92C);
        func_8001A554(0x92D);
        func_8001A554(0x92E);
        func_8001A554(0x92F);
        func_8001A554(0x930);
        func_8001A554(0x12C6);
        func_8001A5CC(0x943);
        ((S_80016DBC_1 *)(D_80016000->unk_1C))->unk_40 = &D_8002116C;
    }
}
