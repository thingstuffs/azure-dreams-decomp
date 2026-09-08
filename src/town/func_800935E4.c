#include "common.h"
#include "records/Rec_func_80090C68_arg0.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((u8 *)(expr) + (offset)))

extern void func_80090A74(void);
extern void func_80093D18(void *arg0, void *arg1, s32 arg2);
extern s32 func_80094B0C(void *arg0);
extern void func_8009550C(void *arg0);
extern void func_80099754(void *arg0);
extern s32 D_80083160[3];


void func_80090D44(void *arg0, void *arg1, s32 arg2) {
    s32 temp_s0;
    s32 *global;

    global = D_80083160;
    temp_s0 = ((Rec_func_80090C68_arg0 *)arg0)->unk_00;
    func_80090A74();
    if ((temp_s0 == ((Rec_func_80090C68_arg0 *)arg0)->unk_00) &&
        (global[2] & 0x80)) {
        func_80099754(arg1);
        func_8009550C(arg1);
        if (func_80094B0C((u8 *)arg0 - 0x20) != 0) {
            func_80093D18(arg0, arg1, arg2);
        }
    }
}
