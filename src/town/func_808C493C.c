/* Relinked copy of town/func_808781C8 (func_808781C8.c); its step flag is 0x107 (twin 0x1F9), otherwise retail differs only at relocation sites. */
#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_00000DA6[];
extern TownPair D_00000DB4[];

extern s32 func_80000884(s32 index);
extern void func_800008F4(s32 index, s32 value);
extern s32 func_800009D4(void);
extern void func_80000B40(u16 value);
extern void func_80000B90(s32 value);
extern s32 func_80000BE4(u16 value);

/* Advance the shop entry at `index`: start its 0x107 step when eligible, otherwise just clear it. */
s32 func_8000093C(s32 index) {
    if (func_80000BE4(D_00000DA6[0]) == 0 &&
        func_80000BE4(0x107) != 0) {
        if (func_80000884(index) != 0) {
            func_80000B40(D_00000DB4[index].field_0);
            func_80000B90(0x107);
            return func_800009D4();
        }
        func_800008F4(index, 0);
        return index;
    }
    func_800008F4(index, 0);
    return index;
}
