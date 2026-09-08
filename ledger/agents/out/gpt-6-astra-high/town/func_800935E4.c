#include "common.h"
#include "records/Rec_func_80090C68_arg0.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((u8 *)(expr) + (offset)))

extern void func_80090A74(void *, void *, s32);
extern void func_80093D18(void *arg0, void *arg1, s32 arg2);
extern s32 func_80094B0C(void *arg0);
extern void func_8009550C(void *arg0);
extern void func_80099754(void *arg0);
extern s32 D_80083160[3];


/* Run follow-up updates if the record value is unchanged and flag 0x80 is set. */
void func_80090D44(void *record, void *context, s32 update_arg) {
    s32 saved_value;
    s32 *state_words;

    state_words = D_80083160;
    saved_value = ((Rec_func_80090C68_arg0 *)record)->unk_00;
    func_80090A74(record, context, update_arg);
    if ((saved_value == ((Rec_func_80090C68_arg0 *)record)->unk_00) &&
        (state_words[2] & 0x80)) {
        func_80099754(context);
        func_8009550C(context);
        if (func_80094B0C((u8 *)record - 0x20) != 0) {
            func_80093D18(record, context, update_arg);
        }
    }
}
