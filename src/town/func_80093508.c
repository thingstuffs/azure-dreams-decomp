#include "common.h"
#include "records/Rec_func_80090C68_arg0.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80090A74(void *, M2C_UNK, M2C_UNK);
extern M2C_UNK func_80093D18();
extern M2C_UNK func_80093DD8();
extern s32 func_80094B0C();
extern M2C_UNK func_8009550C();
extern M2C_UNK func_80099754();
typedef struct {
    s32 unk0;
    s32 unk4;
    s32 flags;
} D_80083160_t;

extern D_80083160_t D_80083160;

/* Updates the record, then handles a flagged action or countdown if its state is unchanged. */
void func_80090C68(void *record, M2C_UNK context, M2C_UNK update_arg) {
    s32 previous_state;
    D_80083160_t *global_state;
    u16 ticks_left;

    global_state = &D_80083160;
    previous_state = ((Rec_func_80090C68_arg0 *)record)->unk_00;
    func_80090A74(record, context, update_arg);
    if (previous_state == ((Rec_func_80090C68_arg0 *)record)->unk_00) {
        if (global_state->flags & 0x80) {
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

