#include "common.h"
#include "m2c_compat.h"

extern void func_80017670(s32);
extern void *D_80016000;
extern M2C_UNK D_8001601C;
extern M2C_UNK D_8001605E;
extern M2C_UNK D_800162A4;
extern M2C_UNK *D_80017760;

typedef struct S_8077DC0C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
    u8 pad_20[0x20];
    s32 unk_40;
} S_8077DC0C_0;   /* state in func_8077DC0C */

typedef struct S_8077DC0C_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8077DC0C_1;   /* dispatch_base in func_8077DC0C */

/* Flip the current slot's toggle byte, point the dispatcher at the matching handler and raise two events. */
void func_8077DC0C(void) {
    u8 *toggle;
    S_8077DC0C_0 *state;
    s32 event;
    S_8077DC0C_1 *dispatch_base;
    S_8077DC0C_1 *dispatch_base_2;

    state = D_80016000;
    D_80017760 = &D_800162A4;
    toggle = state->unk_40 + (state->unk_08 * 8);
    if (*toggle != 0) {
        dispatch_base_2 = state->unk_1C;
        dispatch_base_2->unk_40 = &D_8001605E;
    } else {
        dispatch_base = state->unk_1C;
        dispatch_base->unk_40 = &D_8001601C;
    }
    event = 0x7E;
    *toggle = (*toggle + 1) & 1;
    func_80017670(event);
    func_80017670(0x7F);
}
