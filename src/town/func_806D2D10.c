#include "common.h"

extern void townSetFlagTestIndexedBit();
extern void func_80016D20();
extern s32 func_80016D78();

/* Updates the target based on the source's state, then updates the source. */
void townUpdateFlagTestTarget(s16 sourceId, s16 targetId) {
    if (func_80016D78(sourceId) != 0) {
        townSetFlagTestIndexedBit(targetId);
    } else {
        func_80016D20(targetId);
    }
    townSetFlagTestIndexedBit(sourceId);
}
