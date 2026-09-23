#include "common.h"

extern void func_800250E8(void *arg0, s32 arg1);
extern void func_800230A4(void *arg0, s32 arg1);

extern u8 D_8002593C[];
extern u8 D_80024FAC[];
extern u8 D_80025584[];

/* Select an entry handler and update the owning object's callback. */
void func_8002570C(void *state) {
#ifndef NON_MATCHING
    extern s32 D_80083E98[];
    s32 entry_id = *(s32 *)((u8 *)state + 0x28);

    if (D_80083E98[entry_id * 32] != 0) {
        *(s32 *)((u8 *)state + 0x2C) = entry_id;
        func_800250E8(state, entry_id);
        *(s32 **)((u8 *)state - 0x10) = (s32 *)D_80025584;
    } else {
        *(s32 **)((u8 *)state + 0x34) = (s32 *)D_8002593C;
        func_800230A4((u8 *)state - 0x20, entry_id);
        *(s32 **)((u8 *)state - 0x10) = (s32 *)D_80024FAC;
    }
#else
    extern s32 D_80083E98[];
    s32 entry_id = *(s32 *)((u8 *)state + 0x28);

    if (D_80083E98[entry_id * 32] != 0) {
        *(s32 *)((u8 *)state + 0x2C) = entry_id;
        func_800250E8(state, entry_id);
    } else {
        *(s32 **)((u8 *)state + 0x34) = &D_8002593C;
        func_800230A4((u8 *)state - 0x20, entry_id);
    }
    *(s32 **)((u8 *)state - 0x10) = &D_80024FAC;
#endif
}
