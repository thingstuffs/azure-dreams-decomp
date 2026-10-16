/* Relinked copy of town/func_808781C8 (func_808781C8.c); retail differs only at relocation sites. */
#include "common.h"

typedef struct {
    u16 field_0;
    u16 field_2;
} TownPair;

extern u16 D_00003F5A[];
extern TownPair D_00003F88[];

extern s32 func_80003668(s32 index);
extern void func_800036D8(s32 index, s32 value);
extern s32 func_800037B8(void);
extern void func_80003BCC(u16 value);
extern void func_80003C1C(s32 value);
extern s32 func_80003C70(u16 value);

/* Advance the shop entry at `index`: start its 0x1F9 step when eligible, otherwise just clear it. */
s32 func_80003720(s32 index) {
    if (func_80003C70(D_00003F5A[0]) == 0 &&
        func_80003C70(0x1F9) != 0) {
        if (func_80003668(index) != 0) {
            func_80003BCC(D_00003F88[index].field_0);
            func_80003C1C(0x1F9);
            return func_800037B8();
        }
        func_800036D8(index, 0);
        return index;
    }
    func_800036D8(index, 0);
    return index;
}
