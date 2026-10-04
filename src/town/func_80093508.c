#include "common.h"
#include "shared/game_work.h"
#include "records/Rec_func_80090C68_arg0.h"


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80090A74(void *, s32, s32);
extern void func_80093D18();
extern s32 func_80093DD8();
extern s32 func_80094B0C();
extern void func_8009550C();
extern void func_80099754();
/* Updates the record, then handles a flagged action or countdown if its state is unchanged. */
void func_80090C68(void *record, s32 context, s32 update_arg) {
    s32 previous_state;
    GameWork *global_state;
    u16 ticks_left;

    global_state = &gameWork;
    previous_state = ((Rec_func_80090C68_arg0 *)record)->unk_00;
    func_80090A74(record, context, update_arg);
    if (previous_state == ((Rec_func_80090C68_arg0 *)record)->unk_00) {
        if (global_state->buttons & 0x80) {
            func_80099754(context);
            func_8009550C(context);
            if (func_80094B0C(record - 0x20) != 0) {
                func_80093D18(record, context, update_arg);
                return;
            }
        } else {
            ticks_left = ((Rec_func_80090C68_arg0 *)record)->unk_0A - 1;
            ((Rec_func_80090C68_arg0 *)record)->unk_0A = ticks_left;
            if ((ticks_left << 0x10) <= 0) {
                func_80093DD8(record, context, update_arg);
            }
        }
    }
}

