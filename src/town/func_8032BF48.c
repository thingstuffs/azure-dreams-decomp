#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80018A54();                            /* extern */
M2C_UNK func_8001AD60();                     /* extern */
s32 func_8001ADE0();                         /* extern */
extern M2C_UNK D_8001B314;
extern M2C_UNK *D_8001C370;
extern s8 D_8001ED72;
extern s8 D_8001F092;

/* Initializes the active data pointer and refreshes two status flags. */
void func_80016748(void) {
    D_8001C370 = &D_8001B314;
    func_8001AD60(0xD52);
    func_8001AD60(0xD76);
    func_8001AD60(0xD77);
    if (func_8001ADE0(0xD32) == 0) {
        func_80018A54();
    }
    D_8001ED72 = func_8001ADE0(0x1463) == 0;
    D_8001F092 = func_8001ADE0(0x9B) != 0;
}
