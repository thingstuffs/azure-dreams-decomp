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

/* summary: dispatches to D_8007179C[obj->unk1C](parent, arg) where arg is
   derived from D_800717B4[obj->unk1C] and obj->unk20 / func_800213AC() */
void func_8004FF20(S_8004FF20 *a0) {
    s32 a1 = 0;

    if (D_800717B4[a0->unk1C] != 0) {
        a1 = a0->unk20;
        if (a1 == 2) {
            s32 v0 = func_800213AC();
            v0 = v0 ^ 2;
            a1 = (u32)v0 < 1;
        }
    }

    D_8007179C[a0->unk1C]((u8 *)a0 - 0x20, a1);
}
