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
extern void SD_Call(s32 arg0);
extern void func_800A68F4(void);
extern void func_800277BC(void);


typedef struct S_8002789C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8002789C_0;   /* object in func_8002789C */

/* Handles menu input and refreshes the displayed state. */
void func_8002789C(void *menu)
{
    s32 state_changed[2];
    StatePair *state;
    StatePair *display_state;
    s32 buttons;
    s32 button_flags;
    s32 selection_changed;
    s32 selection;
    s32 *controller;

    buttons = D_80083160[2];
    controller = D_80083160;
    selection_changed = 0;
    if (buttons != 0) {
        button_flags = controller[4];
        if (button_flags & 0x20) {
            s32 *object;

            SD_Call(0x515);
            func_80027C90((u8 *)menu - 0x20);
            func_80027BF4();
            if (D_80082E6B == 3) {
                func_80040AA0(3);
                goto selection_check;
            }
            func_80044144(0, 0, 0, 0);
            object = (*(s32 * *)((u8 *)menu + 0x14));
            ((S_8002789C_0 *)object)->unk_1E |= 0x2000;
            if ((*(s32 *)((u8 *)menu + 0)) == 2) {
                func_800A68F4();
            }
            goto selection_check;
        } else if (button_flags & 0x40) {
            SD_Call(0x503);
            func_80020924((*(s32 *)((u8 *)menu + 0xC)));
            (*(s32 *)((u8 *)menu + 0x34)) = 0;
            (*(void * *)((u8 *)menu + -0x10)) = func_800277BC;
            goto function_return;
        } else if (buttons & 0xA000) {
            if (buttons & 0x8000) {
                selection = (*(s32 *)((u8 *)menu + 0xC));
                if (selection != 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 0;
            } else {
                selection = (*(s32 *)((u8 *)menu + 0xC));
                if (selection == 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 1;
            }
        }

selection_check:
        if (selection_changed != 0) {
            SD_Call(0x502);
            func_80026FD4((*(s32 *)((u8 *)menu + 0x24)), (*(s32 *)((u8 *)menu + 0xC)));
        }
    }

    state = func_800217D4();
    state_changed[0] = state->first != (*(s32 *)((u8 *)menu + 0x18));
    state_changed[1] = state->second != (*(s32 *)((u8 *)menu + 0x1C));
    display_state = state;
    (*(StatePair *)((u8 *)menu + 0x18)) = *state;
    func_80026FF8((*(s32 *)((u8 *)menu + 0x24)), display_state, state_changed);
    func_80021904();

function_return:
    return;
}
