#include "common.h"

/* byte flags array indexed by a state/id field (obj->unk1C) */
extern u8 D_800717B4[];

/* table of callback function pointers indexed by the same state/id field;
   called as fn(parent_ptr, arg) */
typedef void (*Fn_8007179C)(void *, s32);
extern Fn_8007179C D_8007179C[];

extern s32 func_800213AC(void);

typedef struct S_8004FF20 {
    u8 pad00[0x1C];
    s32 unk1C;
    s32 unk20;
} S_8004FF20;

/* Calls the object's state callback with its parent and a flag-dependent argument. */
void func_8004FF20(S_8004FF20 *obj) {
    s32 callback_arg = 0;

    if (D_800717B4[obj->unk1C] != 0) {
        callback_arg = obj->unk20;
        if (callback_arg == 2) {
            s32 query_result = func_800213AC();
            query_result = query_result ^ 2;
            callback_arg = (u32)query_result < 1;
        }
    }

    D_8007179C[obj->unk1C]((u8 *)obj - 0x20, callback_arg);
}
