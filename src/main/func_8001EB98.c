#include "common.h"

extern void cardDevkitSetWindowSelectionMarker(void *, s32);
extern void func_80404618(void *, s32);
extern void func_80404668(void *);
extern void func_80405A00(s32, s32);

void cardDevkitRefreshSaveSlotPairHighlights(void *ptr) {
    s32 i;

    for (i = 0; i < 5; i++) {
        if (i == *((s32 *)ptr + 0xB)) {
            func_80404618(((void **)ptr)[i + 1], 1);
        } else if (i == *((s32 *)ptr + 0xA)) {
            cardDevkitSetWindowSelectionMarker(((void **)ptr)[i + 1], 1);
        } else {
            func_80404668(((void **)ptr)[i + 1]);
        }
    }
    func_80405A00(*((s32 *)ptr + 7), *((s32 *)ptr + 0xA));
}
