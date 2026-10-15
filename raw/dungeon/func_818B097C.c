#include "common.h"

/* Recovered complete gap routine; not registered or assigned to a native module. */
typedef struct { u8 pad00[0x14]; u16 flags; } EffectCounter;
typedef struct { EffectCounter *parent; } EffectOwner;
extern void func_800478B8(EffectCounter *);
extern s32 D_800814A0;
void func_8002417C(EffectOwner *owner, void *unused, EffectCounter *state) {
    owner->parent->flags++;
    func_800478B8(state);
    if (state->flags & 0x6000) {
        *(u16 *)((u8 *)owner - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
