#include "common.h"

extern void func_80019618(s32, s32);
extern void func_80019814(s32, s32);
extern void func_80019928(s32, s32);
extern s32 func_8001A510(s32);
extern s32 func_8001A7F8(void);

/* Menu step: route the pair to the open, mid or closing handler by the 0x798 state. */
s32 func_80016EE8(s32 slot_index, s32 slot_value) {
    if (func_8001A510(0x798) == 0) {
        func_80019618(slot_index, slot_value);
        return 1;
    }

    if (func_8001A7F8() < 0x1A) {
        func_80019814(slot_index, slot_value);
        return;
    }

    func_80019928(slot_index, slot_value);
}
