#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80020984(void);
extern s32 func_80021A84(s32 arg0);
extern void func_80022E9C(void *arg0);
extern void func_8002302C(void *arg0);
extern void func_80023054(void *arg0);
extern u8 D_800274A8[];
extern u8 D_800274D8[];
extern u8 D_8002789C[];

void func_80027584(void *arg0) {
    register s32 state_five ASM_REG("$19");
    s32 result;
    s32 count;
    void *context;

    count = 0;
    state_five = 5;
    ASM_KEEP(state_five);
    do {
        result = func_80021A84(FIELD(arg0, s32, 0xC));
        if (result != state_five) {
            break;
        }
    } while (count++ < 6);

    FIELD(arg0, s32, 0x38) = 0;
    func_80020984();
    if (result == 1) {
        context = (u8 *)arg0 - 0x20;
        ASM_KEEP(context);
        FIELD(arg0, void *, 0x2C) = D_8002789C;
        func_80023054(context);
        FIELD(arg0, void *, -0x10) = D_800274D8;
    } else if (result == 4) {
        context = (u8 *)arg0 - 0x20;
        FIELD(arg0, void *, 0x2C) = D_8002789C;
        func_80022E9C(context);
        FIELD(arg0, void *, -0x10) = D_800274A8;
    } else {
        context = (u8 *)arg0 - 0x20;
        FIELD(arg0, void *, 0x2C) = D_8002789C;
        func_8002302C(context);
        FIELD(arg0, void *, -0x10) = D_800274D8;
    }
}
