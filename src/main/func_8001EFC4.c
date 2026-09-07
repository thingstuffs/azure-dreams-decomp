#include "common.h"

typedef struct S_8001EFC4_0_pre {
    void * unk_00;
    u8 pad_04[0xC];
} S_8001EFC4_0_pre;   /* the 0x10 bytes before root in func_8001EFC4, addressed as root[-1] */

typedef struct S_8001EFC4_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
} S_8001EFC4_0;   /* root in func_8001EFC4 */



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
    s32 action = 0;
    s32 entry_flags;
    s32 flags8;
    s32 flags10;
    s32 value;
    s32 side;

    entry_flags = D_801379A8;
    if (entry_flags != 0) {
        s32 flags20;
        s32 flags5000;

        flags20 = D_801379B0;
        if (flags20 & 0x40) {
            func_80063FF8(0x515);
            ((S_8001EFC4_0_pre *)root)[-1].unk_00 = D_80405AB4;
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
                (*(s32 *)((u8 *)root + 0x30)) = 0;
                flags10 = D_801379B0;
                if (flags10 & 0x1000) {
                    goto negative_tail;
                }
                side = flags10 & 0x4000;
                ASM_KEEP(side);   /* MATCH pin: retail delay-slot contents depend on it */
                return func_804060C4();
            }
            value = ((S_8001EFC4_0 *)root)->unk_30;
            if (value < 13) {
                side = value + 1;
                goto store_counter;
            }
            side = value - 2;
            (*(s32 *)((u8 *)root + 0x30)) = side;
            flags8 = D_801379A8;
            if (flags8 & 0x1000) {
negative_tail:
                ASM_KEEP(action);   /* MATCH pin: retail basic-block layout depends on it */
                action = -1;
                ASM_TAILSLOT_PIN_TIED(action);   /* MATCH pin: retail delay-slot contents depend on it */
                return func_804060D8();
            }
            side = flags8 & 0x4000;
            if (side) {
                action = 1;
                ASM_TAILSLOT_PIN_TIED(action);   /* MATCH pin: retail delay-slot contents depend on it */
                return func_804060D8();
            }
        }
        goto common;

store_counter:
        ((S_8001EFC4_0 *)root)->unk_30 = side;

common:
        if (action != 0) {
            func_80063FF8(0x502);
            value = func_80058FF0(((S_8001EFC4_0 *)root)->unk_28, action, 5);
            ((S_8001EFC4_0 *)root)->unk_28 = value;
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
    func_804083FC(((S_8001EFC4_0 *)root)->unk_20, 0);

exit:
    return;
}
