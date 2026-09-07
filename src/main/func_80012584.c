#include "common.h"

typedef struct S_80025584_0_pre {
    s32 * unk_00;
    u8 pad_04[0xC];
} S_80025584_0_pre;   /* the 0x10 bytes before arg0 in func_80025584, addressed as arg0[-1] */

typedef struct S_80025584_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
} S_80025584_0;   /* arg0 in func_80025584 */



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
            ((S_80025584_0_pre *)arg0)[-1].unk_00 = &D_80024FFC;
        }
        flags = controller[4];
        if (flags & 0x40) {
            func_80053DA8(0x503);
            func_800254E4(arg0);
            goto finish_input;
        }
        if (controller[2] & 0x5000) {
            if (flags & 0x5000) {
                ((S_80025584_0 *)arg0)->unk_30 = 0;
                flags = controller[4];
                if (flags & 0x1000) {
                    status = -1;
                } else if (flags & 0x4000) {
                    status = 1;
                }
            } else {
                value = ((S_80025584_0 *)arg0)->unk_30;
                if (value >= 13) {
                    ((S_80025584_0 *)arg0)->unk_30 = value - 2;
                    flags = controller[2];
                    if (flags & 0x1000) {
                        status = -1;
                    } else if (flags & 0x4000) {
                        status = 1;
                    }
                } else {
                    ((S_80025584_0 *)arg0)->unk_30 = value + 1;
                }
            }
        }

finish_input:
        if (status != 0) {
            func_80053DA8(0x502);
            ((S_80025584_0 *)arg0)->unk_28 =
                func_80049DE8(((S_80025584_0 *)arg0)->unk_28, status, 5);
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
    func_80027AFC(((S_80025584_0 *)arg0)->unk_20, 0);
}
