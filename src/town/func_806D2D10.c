#include "common.h"

extern void func_80016CCC();
extern void func_80016D20();
extern s32 func_80016D78();

// Updates the target based on the source's state, then updates the source.
void func_80016510(s16 sourceId, s16 targetId) {
    if (func_80016D78(sourceId) != 0) {
        func_80016CCC(targetId);
    } else {
        func_80016D20(targetId);
    }
    func_80016CCC(sourceId);
}
