#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_8070021C();
extern s32 func_807002A4();
extern s32 func_807002D4();
extern void func_80700AFC(void) __attribute__((noreturn));
extern s32 func_80700B7C();

void func_808B32AC(s32 arg0)
{
    register s32 temp_v0 ASM_REG("$2");
    void *temp_v1;

    if (func_8070021C(2) == 0) {
        func_807002D4(2);
        temp_v0 = arg0;
        ASM_TAILSLOT_PIN_TIED(temp_v0);
        func_80700AFC();
    }
    else {
        func_807002A4(2);
        temp_v1 = *(void **)0xA0700F40;
        FIELD(temp_v1, u8, 0xE) = FIELD(temp_v1, u8, 0xE);
        func_80700B7C();
    }
}
