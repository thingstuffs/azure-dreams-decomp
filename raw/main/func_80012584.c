#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern s32 D_80083160[];
extern s32 D_80024FFC;

extern s32 func_8002168C(void);
extern void func_80021904(void);
extern void func_800250E8(void *arg0);
extern void func_800254E4(void *arg0);
extern void func_80025D34(void *arg0);
extern void func_80027AFC(s32 arg0, s32 arg1);
extern s32 func_80049DE8(s32 arg0, s32 arg1, s32 arg2);
extern void func_80053DA8(s32 arg0);

void func_80025584(u8 *arg0)
{
    s32 status;
    s32 value;
    s32 flags;
    s32 *controller;

    controller = D_80083160;
    status = 0;
    if (controller[2] != 0) {
        if (controller[4] & 0x20) {
            func_80053DA8(0x515);
            FIELD(arg0, s32 *, -0x10) = &D_80024FFC;
        }
        flags = controller[4];
        if (flags & 0x40) {
            func_80053DA8(0x503);
            func_800254E4(arg0);
            goto finish_input;
        }
        if (controller[2] & 0x5000) {
            if (flags & 0x5000) {
                FIELD(arg0, s32, 0x30) = 0;
                flags = controller[4];
                if (flags & 0x1000) {
                    status = -1;
                } else if (flags & 0x4000) {
                    status = 1;
                }
            } else {
                value = FIELD(arg0, s32, 0x30);
                if (value >= 13) {
                    FIELD(arg0, s32, 0x30) = value - 2;
                    flags = controller[2];
                    if (flags & 0x1000) {
                        status = -1;
                    } else if (flags & 0x4000) {
                        status = 1;
                    }
                } else {
                    FIELD(arg0, s32, 0x30) = value + 1;
                }
            }
        }

finish_input:
        if (status != 0) {
            func_80053DA8(0x502);
            FIELD(arg0, s32, 0x28) =
                func_80049DE8(FIELD(arg0, s32, 0x28), status, 5);
            func_800250E8(arg0);
        }
    }

    status = func_8002168C();
    func_80021904();
    if (status == 0) {
        return;
    }
    if (status == 1) {
        return;
    }
    func_80025D34(arg0 - 0x20);
    func_80027AFC(FIELD(arg0, s32, 0x20), 0);
}
