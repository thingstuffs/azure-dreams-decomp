#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001809C_1 {
    u8 pad_00[0x68];
    s32 (*unk_68)(M2C_UNK, M2C_UNK, M2C_UNK, M2C_UNK *);
} S_8001809C_1;   /* D_80016000->unk_20 in func_8001809C */


typedef struct S_8001809C_0 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001809C_0;   /* D_80016000 in func_8001809C */


M2C_UNK func_80017F3C();                   /* extern */
M2C_UNK func_80018824();          /* extern */
extern S_8001809C_0 *D_80016000;
extern M2C_UNK D_8001B218;
extern s32 D_8001B318;

void func_8001809C(void) {
    func_80018824(&D_8001B218, 0x100);
    func_80017F3C(&D_8001B218);
    D_8001B318 = ((S_8001809C_1 *)(D_80016000->unk_20))->unk_68(0, 0, 1, &D_8001B218);
}
