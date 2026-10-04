#include "common.h"

extern s32 func_80019B54();
extern void func_80019BC0();
extern s32 func_8001B0C8();

/* Process the request after checking the threshold of 20. */
void func_80016938(s32 request, s32 context) {
    if (func_8001B0C8() >= 0x14) {
        func_80019BC0();
    }
    func_80019B54(request, context);
}
