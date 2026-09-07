#include "common.h"

typedef struct S_80406368_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x10];
    s32 unk_44;
    s32 unk_48;
} S_80406368_0;   /* arg0 in func_80406368 */



extern s32 D_801379A8;
extern s32 D_801379B0;

extern void func_80063FF8(s32 arg0);
extern s32  func_80058FF0(s32 arg0, s32 arg1, s32 arg2);
extern s32  func_804016D0(void);
extern void func_804018FC(void);
extern void func_80405AE8(void *arg0);
extern void func_804062F4(void *arg0);
extern void func_80406358(void *arg0);
extern void func_80406720(void *arg0);
extern void func_804083FC(s32 arg0, s32 arg1);

/* Handles menu navigation, button actions, and display refreshes. */
void func_80406368(void *menu)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 nav_result;
    s32 needs_refresh;
    s32 repeat_ticks;

    held_buttons = D_801379A8;
    nav_result = 0;
    needs_refresh = 0;
    if (held_buttons != 0) {
        pressed_buttons = D_801379B0;
        if (pressed_buttons & 0x40) {
            func_80063FF8(0x515);
            func_80406720((u8 *) menu - 0x20);
            func_804083FC(((S_80406368_0 *)menu)->unk_20, 0);
            return;
        } else if (pressed_buttons & 0x20) {
            func_80063FF8(0x514);
            if (((S_80406368_0 *)menu)->unk_48 == 0) {
                func_80406358(menu);
                needs_refresh = 1;
            } else {
                func_804062F4(menu);
            }
        } else if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                (*(s32 *)((u8 *)menu + 0x30)) = 0;
                if (D_801379B0 & 0x1000) {
                    nav_result = -1;
                } else if (D_801379B0 & 0x4000) {
                    nav_result = 1;
                }
            } else {
                repeat_ticks = ((S_80406368_0 *)menu)->unk_30;
                if (repeat_ticks >= 13) {
                    (*(s32 *)((u8 *)menu + 0x30)) = repeat_ticks - 4;
                    if (D_801379A8 & 0x1000) {
                        nav_result = -1;
                    } else if (D_801379A8 & 0x4000) {
                        nav_result = 1;
                    }
                } else {
                    ((S_80406368_0 *)menu)->unk_30 = repeat_ticks + 1;
                }
            }
        } else if (held_buttons & 0xA000) {
            if (held_buttons & 0x2000) {
                ((S_80406368_0 *)menu)->unk_48 = 1;
            } else {
                ((S_80406368_0 *)menu)->unk_48 = 0;
            }
            needs_refresh = 1;
        }

        if (nav_result != 0) {
            func_80063FF8(0x502);
            if (((S_80406368_0 *)menu)->unk_48 == 1) {
                ((S_80406368_0 *)menu)->unk_28 = func_80058FF0(((S_80406368_0 *)menu)->unk_28, nav_result, 5);
            } else {
                ((S_80406368_0 *)menu)->unk_44 = func_80058FF0(((S_80406368_0 *)menu)->unk_44, nav_result, 4);
            }
            func_80405AE8(menu);
        }
    }

    nav_result = func_804016D0();
    func_804018FC();
    if (nav_result != 0) {
        if (nav_result != 1) {
            func_80406720((u8 *) menu - 0x20);
            func_804083FC(((S_80406368_0 *)menu)->unk_20, 0);
        }
    }
    if (needs_refresh != 0) {
        func_80405AE8(menu);
    }
}
