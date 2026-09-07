#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003FA78();                /* extern */
s32 func_80408644();                         /* extern */
extern u8 D_80400090[];
extern u8 D_8040009C[];
extern u8 D_804000A4[];
extern u8 D_804000B0[];
extern u8 D_804000BC[];
extern u8 D_804000D0[];

void func_8001A8FC(void) {
    func_8003FA78(&D_80400090[0], *(s32 *)0x804094EC);
    func_8003FA78(&D_8040009C[0], *(s32 *)0x804094E8);
    func_8003FA78(&D_804000A4[0], *(s32 *)0x80409500);
    func_8003FA78(&D_804000B0[0], *(s32 *)0x80409504);
    func_8003FA78(&D_804000BC[0], func_80408644(0));
    func_8003FA78(&D_804000D0[0], func_80408644(1));
}
