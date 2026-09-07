#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_80063FF8(s32 code);
extern void func_80405F24(void *arg0);
extern void func_804060C4(void);
extern void func_804060D8(void);
extern s32 func_80058FF0(s32 current, s32 direction, s32 amount);
extern void func_80405B98(void *arg0);
extern s32 func_804016D0(void);
extern void func_804018FC(void);
extern void func_80406720(void *arg0);
extern void func_804083FC(s32 current, s32 mode);
extern volatile s32 D_801379A8;
extern volatile s32 D_801379B0;
extern u8 D_80405AB4[];

void func_8001EFC4(u8 *root)
{
    register s32 action ASM_REG("$16") = 0;
    s32 entry_flags;
    s32 flags8;
    register s32 flags10 ASM_REG("$3");
    s32 value;
    s32 side;

    entry_flags = D_801379A8;
    if (entry_flags != 0) {
        s32 flags20;
        s32 flags5000;

        flags20 = D_801379B0;
        if (flags20 & 0x40) {
            func_80063FF8(0x515);
            FIELD(root, void *, -0x10) = D_80405AB4;
        }
        flags10 = D_801379B0;
        if (flags10 & 0x20) {
            func_80063FF8(0x514);
            func_80405F24(root);
            return func_804060D8();
        }
        flags5000 = D_801379A8;
        if (flags5000 & 0x5000) {
            side = flags10 & 0x5000;
            if (side != 0) {
                FIELD(root, s32, 0x30) = 0;
                flags10 = D_801379B0;
                if (flags10 & 0x1000) {
                    goto negative_tail;
                }
                side = flags10 & 0x4000;
                ASM_KEEP(side);
                return func_804060C4();
            }
            value = FIELD(root, s32, 0x30);
            if (value < 13) {
                side = value + 1;
                goto store_counter;
            }
            side = value - 2;
            FIELD(root, s32, 0x30) = side;
            flags8 = D_801379A8;
            if (flags8 & 0x1000) {
negative_tail:
                ASM_KEEP(action);
                action = -1;
                ASM_TAILSLOT_PIN_TIED(action);
                return func_804060D8();
            }
            side = flags8 & 0x4000;
            if (side) {
                action = 1;
                ASM_TAILSLOT_PIN_TIED(action);
                return func_804060D8();
            }
        }
        goto common;

store_counter:
        FIELD(root, s32, 0x30) = side;

common:
        ASM_KEEP(action);
        if (action != 0) {
            func_80063FF8(0x502);
            value = func_80058FF0(FIELD(root, s32, 0x28), action, 5);
            FIELD(root, s32, 0x28) = value;
            func_80405B98(root);
        }
    }

    action = func_804016D0();
    func_804018FC();
    if (action == 0) {
        goto exit;
    }
    if (action == 1) {
        goto exit;
    }
    func_80406720(root - 0x20);
    func_804083FC(FIELD(root, s32, 0x20), 0);

exit:
    return;
}
