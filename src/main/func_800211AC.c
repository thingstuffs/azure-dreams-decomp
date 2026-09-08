#include "common.h"


typedef struct StatePair {
    s32 first;
    s32 second;
} StatePair;

extern s32 D_801379A8;
extern s32 D_801379B0;
extern s8 D_8008CA34;
extern s32 D_804090F8[];
extern s32 D_80400854;
extern s32 D_80400860;

extern void func_8003FA78(void *arg0, s32 arg1);
extern void func_8003FD58(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern void func_80063FF8(s32 arg0);
extern void func_804008A0(s32 arg0);
extern void func_80400EF8(void);
extern StatePair *func_804017EC(void);
extern void func_804018FC(void);
extern void func_80407830(s32 arg0, s32 arg1);
extern void func_8040787C(s32 arg0, StatePair *arg1, s32 *arg2);
extern void func_804080A4(void);
extern void func_804084DC(void *arg0);


typedef struct S_804081AC_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_804081AC_0;   /* object in func_804081AC */

/* Handles menu selection input and refreshes the displayed state pair. */
void func_804081AC(void *menu)
{
    s32 state_changed[2];
    StatePair *state;
    StatePair *display_state;
    s32 buttons;
    s32 button_flags;
    s32 selection_changed;
    s32 old_selection;

    buttons = D_801379A8;
    selection_changed = 0;
    if (buttons != 0) {
        button_flags = D_801379B0;
        if (button_flags & 0x40) {
            s32 *linked_object;

            func_80063FF8(0x515);
            func_804084DC((u8 *)menu - 0x20);
            D_8008CA34 = 2;
            func_80400EF8();
            func_8003FD58(0, 0xF, 0, 0);
            linked_object = (*(s32 * *)((u8 *)menu + 0x14));
            ((S_804081AC_0 *)linked_object)->unk_1E |= 0x2000;
            goto selection_check;
        } else if (button_flags & 0x20) {
            func_80063FF8(0x514);
            func_804008A0((*(s32 *)((u8 *)menu + 0xC)));
            (*(s32 *)((u8 *)menu + 0x34)) = 0;
            (*(void * *)((u8 *)menu + -0x10)) = func_804080A4;
            goto function_return;
        } else if (buttons & 0xA000) {
            if (buttons & 0x8000) {
                old_selection = (*(s32 *)((u8 *)menu + 0xC));
                (*(s32 *)((u8 *)menu + 0xC)) = 0;
                if (old_selection != 0) {
                    selection_changed = 1;
                }
            } else {
                old_selection = (*(s32 *)((u8 *)menu + 0xC));
                if (old_selection == 0) {
                    selection_changed = 1;
                }
                (*(s32 *)((u8 *)menu + 0xC)) = 1;
            }
        }

selection_check:
        if (selection_changed != 0) {
            func_80063FF8(0x502);
            func_80407830((*(s32 *)((u8 *)menu + 0x24)), (*(s32 *)((u8 *)menu + 0xC)));
        }
    }

    state = func_804017EC();
    state_changed[0] = state->first != (*(s32 *)((u8 *)menu + 0x18));
    state_changed[1] = state->second != (*(s32 *)((u8 *)menu + 0x1C));
    display_state = state;
    (*(StatePair *)((u8 *)menu + 0x18)) = *state;
    func_8040787C((*(s32 *)((u8 *)menu + 0x24)), display_state, state_changed);
    func_8003FA78(&D_80400854, D_804090F8[state->first]);
    func_8003FA78(&D_80400860, D_804090F8[state->second]);
    func_804018FC();

function_return:
    return;
}
