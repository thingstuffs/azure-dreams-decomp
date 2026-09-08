#include "common.h"
#include "m2c_compat.h"

s32 func_8001894C();
void func_800168B8() __attribute__((noreturn));
s32 func_80018044();
extern M2C_UNK D_80018B18;
extern M2C_UNK D_80018E38;
extern u8 D_8001C59A[16];

void func_8001686C(s32 arg0, M2C_UNK arg1, M2C_UNK arg2) {
    if (func_8001894C(0x510) != 0) {
        u8 *hidden = D_8001C59A;
        ASM_TAILSLOT_PIN(hidden);   /* UNRESOLVED C shape (pin): removing it changes a delay-slot's contents; the source shape that makes it unnecessary has not been found */
        func_800168B8();
        return;
    }
    ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    func_80018044(&D_80018B18, &D_80018E38, arg0, arg2);
}
