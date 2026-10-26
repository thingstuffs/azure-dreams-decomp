#include "town/scene.h"
extern u8 D_8001BBB4[];
extern u8 D_8001F5AD[];
extern u8 D_8001C354[];
extern void *apply_entry_position(void *, void *, void *, s32);
extern s32 func_80019DA0(void *, void *, s32);

void *select_square_entry_or_alternate(SquareSceneEntry *entry, s32 unused, s32 selection) {
    void *records = D_8001BBB4;
    void *result;
    void *selected;
    result = apply_entry_position(records, D_8001C354, entry, selection);
    if (func_80019DA0(records, entry, selection) == 0) {
        selected = result;
    } else {
        selected = D_8001F5AD;
    }
    return selected;
}
