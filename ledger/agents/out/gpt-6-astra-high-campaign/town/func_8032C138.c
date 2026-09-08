#include "common.h"

typedef s32 M2C_UNK;

extern M2C_UNK func_80019B54();
extern M2C_UNK func_80019BC0();
extern s32 func_8001B0C8();

/* Process the request after checking the threshold of 20. */
void func_80016938(s32 request, M2C_UNK context) {
    if (func_8001B0C8() >= 0x14) {
        func_80019BC0();
    }
    func_80019B54(request, context);
}
