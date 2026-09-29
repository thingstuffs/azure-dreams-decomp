#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_80025030_arg0.h"





extern void SD_Call(s32);
extern void func_80025D34(void *);
extern void func_80027AFC(s32, s32);
extern void func_8002592C(void *);
extern void func_800258C8(void *);
extern s32 func_80049DE8(s32, s32, s32);
extern void func_80025030(void *);
extern s32 func_8002168C(void);
extern void func_80021904(void);

/* Handle menu selection, directional repeat, and closing from controller input and update status. */
void func_8002593C(u8 *object)
{
    s32 held_buttons;
    s32 pressed_buttons;
    s32 repeat_buttons;
    s32 selection_step;
    s32 repeat_ticks;
    s32 needs_refresh;
    s32 update_status;

    held_buttons = gameWork.buttons;
    selection_step = 0;
    needs_refresh = selection_step;
    if (held_buttons != 0) {
        pressed_buttons = ((s32)gameWork.unk_010);
        if (pressed_buttons & 0x20) {
            SD_Call(0x515);
            func_80025D34(object - 0x20);
            func_80027AFC(((Rec_func_80025030_arg0 *)object)->unk_20, 0);
            return;
        }
        if (pressed_buttons & 0x40) {
            SD_Call(0x503);
            if (((Rec_func_80025030_arg0 *)object)->unk_48 == 0) {
                func_8002592C(object);
                needs_refresh = 1;
            } else {
                func_800258C8(object);
            }
        } else if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                ((Rec_func_80025030_arg0 *)object)->unk_30 = 0;
                pressed_buttons = ((s32)gameWork.unk_010);
                if (pressed_buttons & 0x1000) {
                    selection_step = -1;
                } else if (pressed_buttons & 0x4000) {
                    selection_step = 1;
                }
            } else {
                repeat_ticks = ((Rec_func_80025030_arg0 *)object)->unk_30;
                if (repeat_ticks >= 13) {
                    ((Rec_func_80025030_arg0 *)object)->unk_30 = repeat_ticks - 4;
                    repeat_buttons = gameWork.buttons;
                    if (repeat_buttons & 0x1000) {
                        selection_step = -1;
                    } else if (repeat_buttons & 0x4000) {
                        selection_step = 1;
                    }
                } else {
                    ((Rec_func_80025030_arg0 *)object)->unk_30 = repeat_ticks + 1;
                }
            }
        } else if (held_buttons & 0xA000) {
            if (held_buttons & 0x2000) {
                ((Rec_func_80025030_arg0 *)object)->unk_48 = 1;
            } else {
                ((Rec_func_80025030_arg0 *)object)->unk_48 = 0;
            }
            needs_refresh = 1;
        }

        if (selection_step != 0) {
            SD_Call(0x502);
            if (((Rec_func_80025030_arg0 *)object)->unk_48 == 1) {
                ((Rec_func_80025030_arg0 *)object)->unk_28 =
                    func_80049DE8(((Rec_func_80025030_arg0 *)object)->unk_28, selection_step, 5);
            } else {
                ((Rec_func_80025030_arg0 *)object)->unk_44 =
                    func_80049DE8(((Rec_func_80025030_arg0 *)object)->unk_44, selection_step, 3);
            }
            func_80025030(object);
        }
    }

    update_status = func_8002168C();
    func_80021904();
    if (update_status != 0) {
        if (update_status != 1) {
            func_80025D34(object - 0x20);
            func_80027AFC(((Rec_func_80025030_arg0 *)object)->unk_20, 0);
        }
    }

    if (needs_refresh != 0) {
        func_80025030(object);
    }
    return;
}
