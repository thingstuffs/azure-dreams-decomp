#include "common.h"

typedef s32 (*func_80018760_fn)(void *);

extern s8 D_80016000[];
extern s32 D_8001BE60;

/* Deducts the computed cost from the available balance if sufficient funds remain. */
s32 func_80018760(void) {
    void *context;
    void *costProvider;
    func_80018760_fn getCost;
    u32 requiredAmount;
    void *updatedContext;
    void *balanceOwner;
    u32 availableAmount;

    context = *(void **)D_80016000;
    costProvider = *(void **)((s8 *)context + 0x20);
    getCost = *(func_80018760_fn *)((s8 *)costProvider + 0x50);
    requiredAmount = (u32) getCost(&D_8001BE60);

    updatedContext = *(void **)D_80016000;
    balanceOwner = *(void **)((s8 *)updatedContext + 0x38);
    availableAmount = *(u32 *)((s8 *)balanceOwner + 0x2D5C);

    if (availableAmount >= requiredAmount) {
        *(u32 *)((s8 *)balanceOwner + 0x2D5C) = availableAmount - requiredAmount;
        return 1;
    }
    return 0;
}
