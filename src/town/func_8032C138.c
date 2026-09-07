#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80019B54();
extern M2C_UNK func_80019BC0();
extern s32 func_8001B0C8();

void func_80016938(s32 arg0, M2C_UNK arg1) {
    if (func_8001B0C8() >= 0x14) {
        func_80019BC0();
    }
    func_80019B54(arg0, arg1);
}
