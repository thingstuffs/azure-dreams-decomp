#include "common.h"
#include "shared/game_work.h"

typedef struct S_800265B8_0 {
    u8 pad_00[0x20];
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
    s32 unk_30;
} S_800265B8_0;   /* menu in func_800265B8 */


extern s32 cardBootDebounceCardStatusEvents(void);
extern void func_80021904(void);
extern void cardBootHighlightSelectedLoadSlot(void *state);
extern void mainRouteSaveSlotValidation(void *context);
extern void func_80026920(void *object);
extern void initCardBootRequestObject(s32 request, s32 mode);
extern s32 advanceIndexWithSingleWrap(s32 index, s32 delta, s32 limit);
extern void SD_Call(s32 flags);

/* Handles menu navigation with button repeat and dispatches the selected action. */
void func_800265B8(u8 *menu)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 repeat_buttons;
    s32 status;
    s32 repeat_ticks;

    held_buttons = gameWork.buttons;
    status = 0;
    if (held_buttons != 0) {
        pressed_buttons = ((s32)gameWork.unk_010);
        if (pressed_buttons & 0x20) {
            SD_Call(0x515);
            func_80026920(menu - 0x20);
            initCardBootRequestObject(((S_800265B8_0 *)menu)->unk_20, ((S_800265B8_0 *)menu)->unk_24);
            return;
        }
        if (pressed_buttons & 0x40) {
            SD_Call(0x503);
            mainRouteSaveSlotValidation(menu);
        } else {
            if (held_buttons & 0x5000) {
                if (pressed_buttons & 0x5000) {
                    ((S_800265B8_0 *)menu)->unk_30 = 0;
                    pressed_buttons = ((s32)gameWork.unk_010);
                    if (pressed_buttons & 0x1000) {
                        status = -1;
                    } else if (pressed_buttons & 0x4000) {
                        status = 1;
                    }
                } else {
                    repeat_ticks = ((S_800265B8_0 *)menu)->unk_30;
                    if (repeat_ticks >= 13) {
                        ((S_800265B8_0 *)menu)->unk_30 = repeat_ticks - 4;
                        repeat_buttons = gameWork.buttons;
                        if (repeat_buttons & 0x1000) {
                            status = -1;
                        } else if (repeat_buttons & 0x4000) {
                            status = 1;
                        }
                    } else {
                        ((S_800265B8_0 *)menu)->unk_30 = repeat_ticks + 1;
                    }
                }
            }
        }
        if (status != 0) {
            SD_Call(0x502);
            ((S_800265B8_0 *)menu)->unk_2C =
                advanceIndexWithSingleWrap(((S_800265B8_0 *)menu)->unk_2C, status, 5);
            cardBootHighlightSelectedLoadSlot(menu);
        }
    }

    status = cardBootDebounceCardStatusEvents();
    func_80021904();
    if (status == 0) {
        return;
    }
    if (status == 1) {
        return;
    }

    func_80026920(menu - 0x20);
    initCardBootRequestObject(((S_800265B8_0 *)menu)->unk_20, ((S_800265B8_0 *)menu)->unk_24);
}
