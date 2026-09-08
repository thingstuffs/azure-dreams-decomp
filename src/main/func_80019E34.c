#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8007BFE0();          /* extern */
M2C_UNK func_8007C040();       /* extern */
M2C_UNK func_8007C958();                            /* extern */
M2C_UNK func_8007CB08();                     /* extern */
M2C_UNK func_80400A10();                            /* extern */
M2C_UNK func_804086DC();                     /* extern */
M2C_UNK func_80408730();                            /* extern */
extern M2C_UNK D_8009DDD8;
extern s32 D_8009E390;
extern s32 D_8009E394;
extern s32 D_8013BB6C;
extern s32 D_80400038;
extern s32 D_80400044;

/* Performs first-time initialization and resets overlay state. */
void func_80019E34(void) {
    func_8007C040(&D_80400038, &D_80400044, D_8013BB6C);
    if (D_8013BB6C == 0) {
        D_8013BB6C = 1;
        func_804086DC(1);
        func_80408730();
        func_8007C958();
        func_8007CB08(0);
        D_8009E390 = 0;
        D_8009E394 = 0;
        func_8007BFE0(&D_8009DDD8, 0x280);
    }
    func_80400A10();
    *(s32 *)0x804094F0 = 0;
    *(s32 *)0x804094F4 = 0;
    *(s32 *)0x804094F8 = 0;
    *(s32 *)0x804094FC = 0;
    *(s32 *)0x804094E8 = 0;
}
