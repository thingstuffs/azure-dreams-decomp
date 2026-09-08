#include "common.h"
#include "records/Rec_func_80025030_arg0.h"




extern s32 D_80083160[];

extern void func_80053DA8(s32);
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
    s32 *controller;
    s32 update_status;

    held_buttons = D_80083160[2];
    controller = D_80083160;
    selection_step = 0;
    needs_refresh = selection_step;
    if (held_buttons != 0) {
        pressed_buttons = controller[4];
        if (pressed_buttons & 0x20) {
            func_80053DA8(0x515);
            func_80025D34(object - 0x20);
            func_80027AFC(((Rec_func_80025030_arg0 *)object)->unk_20, 0);
            goto epilogue;
        }
        if (pressed_buttons & 0x40) {
            func_80053DA8(0x503);
            if (((Rec_func_80025030_arg0 *)object)->unk_48 == 0) {
                func_8002592C(object);
                needs_refresh = 1;
                goto direction_check;
            }
            func_800258C8(object);
            goto direction_check;
        }
        if (held_buttons & 0x5000) {
            if (pressed_buttons & 0x5000) {
                ((Rec_func_80025030_arg0 *)object)->unk_30 = 0;
                pressed_buttons = controller[4];
                if (pressed_buttons & 0x1000) {
                    selection_step = -1;
                } else if (pressed_buttons & 0x4000) {
                    selection_step = 1;
                }
            } else {
                repeat_ticks = ((Rec_func_80025030_arg0 *)object)->unk_30;
                if (repeat_ticks >= 13) {
                    ((Rec_func_80025030_arg0 *)object)->unk_30 = repeat_ticks - 4;
                    repeat_buttons = controller[2];
                    if (repeat_buttons & 0x1000) {
                        selection_step = -1;
                    } else if (repeat_buttons & 0x4000) {
                        selection_step = 1;
                    }
                } else {
                    ((Rec_func_80025030_arg0 *)object)->unk_30 = repeat_ticks + 1;
                }
            }
            goto direction_check;
        }

        if (held_buttons & 0xA000) {
            if (held_buttons & 0x2000) {
                ((Rec_func_80025030_arg0 *)object)->unk_48 = 1;
                needs_refresh = 1;
                goto direction_check;
            }
            ((Rec_func_80025030_arg0 *)object)->unk_48 = 0;
            needs_refresh = 1;
        }

direction_check:
        if (selection_step != 0) {
            func_80053DA8(0x502);
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
    if (update_status == 0) {
        goto changed_check;
    }
    if (update_status == 1) {
        goto changed_check;
    }

forced_tail:
    func_80025D34(object - 0x20);
    func_80027AFC(((Rec_func_80025030_arg0 *)object)->unk_20, 0);

changed_check:
    if (needs_refresh != 0) {
        func_80025030(object);
    }
epilogue:
    return;
}
