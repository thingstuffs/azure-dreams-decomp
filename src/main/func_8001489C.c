#include "common.h"


typedef struct StatePair {
    s32 first;
    s32 second;
} StatePair;

extern s32 D_80083160[];
extern u8 D_80082E6B;

extern void func_80020924(s32 arg0);
extern StatePair *func_800217D4(void);
extern void func_80021904(void);
extern void func_80026FD4(s32 arg0, s32 arg1);
extern void func_80026FF8(s32 arg0, StatePair *arg1, s32 *arg2);
extern void func_80027BF4(void);
extern void func_80027C90(void *arg0);
extern void func_80040AA0(s32 arg0);
extern void func_80044144(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80053DA8(s32 arg0);
extern void func_800A68F4(void);
extern void func_800277BC(void);


typedef struct S_8002789C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002789C_0;   /* object in func_8002789C */

void func_8002789C(void *arg0)
{
    s32 changed[2];
    StatePair *state;
    StatePair *state_arg;
    s32 input;
    s32 flags;
    s32 status;
    s32 value;
    s32 *controller;

    input = D_80083160[2];
    controller = D_80083160;
    status = 0;
    if (input != 0) {
        flags = controller[4];
        if (flags & 0x20) {
            s32 *object;

            func_80053DA8(0x515);
            func_80027C90((u8 *)arg0 - 0x20);
            func_80027BF4();
            if (D_80082E6B == 3) {
                func_80040AA0(3);
                goto status_check;
            }
            func_80044144(0, 0, 0, 0);
            object = (*(s32 * *)((u8 *)arg0 + 0x14));
            ((S_8002789C_0 *)object)->unk_1E |= 0x2000;
            if ((*(s32 *)((u8 *)arg0 + 0)) == 2) {
                func_800A68F4();
            }
            goto status_check;
        } else if (flags & 0x40) {
            func_80053DA8(0x503);
            func_80020924((*(s32 *)((u8 *)arg0 + 0xC)));
            (*(s32 *)((u8 *)arg0 + 0x34)) = 0;
            (*(void * *)((u8 *)arg0 + -0x10)) = func_800277BC;
            goto function_return;
        } else if (input & 0xA000) {
            if (input & 0x8000) {
                value = (*(s32 *)((u8 *)arg0 + 0xC));
                if (value != 0) {
                    status = 1;
                }
                (*(s32 *)((u8 *)arg0 + 0xC)) = 0;
            } else {
                value = (*(s32 *)((u8 *)arg0 + 0xC));
                if (value == 0) {
                    status = 1;
                }
                (*(s32 *)((u8 *)arg0 + 0xC)) = 1;
            }
        }

status_check:
        if (status != 0) {
            func_80053DA8(0x502);
            func_80026FD4((*(s32 *)((u8 *)arg0 + 0x24)), (*(s32 *)((u8 *)arg0 + 0xC)));
        }
    }

    state = func_800217D4();
    changed[0] = state->first != (*(s32 *)((u8 *)arg0 + 0x18));
    changed[1] = state->second != (*(s32 *)((u8 *)arg0 + 0x1C));
    state_arg = state;
    (*(StatePair *)((u8 *)arg0 + 0x18)) = *state;
    func_80026FF8((*(s32 *)((u8 *)arg0 + 0x24)), state_arg, changed);
    func_80021904();

function_return:
    return;
}
