#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80400908(void);
extern s32 func_80401B30(s32 arg0);
extern void func_804030F4(void *arg0);
extern void func_80403284(void *arg0);
extern void func_804032AC(void *arg0);
extern u8 D_80407D90[];
extern u8 D_80407DB8[];
extern u8 D_804081AC[];

void func_80407E64(void *arg0) {
    register s32 state_five ASM_REG("$19");
    s32 result;
    s32 count;
    void *context;

    count = 0;
    state_five = 5;
    ASM_KEEP(state_five);
    do {
        result = func_80401B30(FIELD(arg0, s32, 0xC));
        if (result != state_five) {
            break;
        }
    } while (count++ < 6);

    FIELD(arg0, s32, 0x38) = 0;
    func_80400908();
    if (result == 1) {
        context = (u8 *)arg0 - 0x20;
        ASM_KEEP(context);
        FIELD(arg0, void *, 0x2C) = D_804081AC;
        func_804032AC(context);
        FIELD(arg0, void *, -0x10) = D_80407DB8;
    } else if (result == 4) {
        context = (u8 *)arg0 - 0x20;
        FIELD(arg0, void *, 0x2C) = D_804081AC;
        func_804030F4(context);
        FIELD(arg0, void *, -0x10) = D_80407D90;
    } else {
        context = (u8 *)arg0 - 0x20;
        FIELD(arg0, void *, 0x2C) = D_804081AC;
        func_80403284(context);
        FIELD(arg0, void *, -0x10) = D_80407DB8;
    }
}
