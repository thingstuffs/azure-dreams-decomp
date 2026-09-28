#include "common.h"
#include "shared/game_work.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 field8;
    s32 unkC;
    s32 field10;
} PadState;

typedef struct {
    s32 unk0;
    s32 field4;
    s32 field8;
    s32 unkC;
    s32 field10;
    s32 pad14[23];
    s32 field70;
} MenuState;

extern void func_80026370(s32, s32);
extern s32 func_80026388(s32, s32, s32);
extern s16 SD_Call(s32);

/* Updates the menu selection from directional input with key repeat and a sound. */
void func_8002640C(MenuState *menu) {
    s32 direction = 0;
    s32 buttons;
    s32 repeat_ticks;
    s32 selection;

    if (gameWork.buttons != 0) {
        if (((s32)gameWork.unk_010) & 0xC) {
            menu->field4 = 0;
            buttons = ((s32)gameWork.unk_010);
            if (buttons & 4) {
                direction = -1;
            } else if (buttons & 8) {
                direction = 1;
            }
        } else if (gameWork.buttons & 0xC) {
            repeat_ticks = menu->field4;
            if (repeat_ticks >= 9) {
                menu->field4 = repeat_ticks - 1;
                buttons = gameWork.buttons;
                if (buttons & 4) {
                    direction = -1;
                } else if (buttons & 8) {
                    direction = 1;
                }
            } else {
                menu->field4 = repeat_ticks + 1;
            }
        }

        if (direction != 0) {
            SD_Call(0x502);
            selection = func_80026388(direction, menu->field8, menu->field10);
            menu->field8 = selection;
            func_80026370(menu->field70, selection);
        }
    }
}
