#include "common.h"

typedef struct {
    s32 unk0;
    s16 value;
    u8 pad[6];
} Entry;

extern s32 func_800198D0(u32);
extern u8 *D_80019BBC[];
extern Entry D_80016470[];
extern u8 D_80016520[];

s32 func_800176D4(void)
{
    s32 original;
    s32 index;
    Entry *entries;
    u8 *order;
    u8 *item;

    original = D_80019BBC[0][4];
    index = original + 1;
    if (index != original) {
        entries = D_80016470;
        order = D_80016520;
        item = &order[index];
        do {
            if (*item == 0) {
                item = order;
                index = 0;
            }
            if (func_800198D0(entries[*item].value) != 0) {
                break;
            }
            index++;
            item++;
        } while (index != original);
    }
    D_80019BBC[0][4] = index;
    return D_80016520[index];
}
