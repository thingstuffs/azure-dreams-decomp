#include "modules/dungeon_ovl_1852800.h"
#include "common.h"
#include "shared/object_flags.h"

typedef struct StructInner {
    s8 pad0[0x52];
    u16 unk52;
} StructInner;

typedef struct StructA0 {
    StructInner *inner;
} StructA0;

typedef struct StructA2 {
    u8 pad0[0x14];
    u16 unk14;
    u8 pad16[0x1C - 0x14 - 2];
    u16 unk1C;
    u16 unk1E;
} StructA2;

extern void func_800478B8(void *state);

/* Decreases paired state values by 0x80, invokes the state handler, and sets flags. */
void func_80024860(StructA0 *owner, void *unused, StructA2 *state) {
    u16 adjusted_value;

    adjusted_value = state->unk1E - 0x80;
    state->unk1E = adjusted_value;
    state->unk1C = adjusted_value;
    owner->inner->unk52 |= 0x8000;
    func_800478B8(state);
    if (state->unk14 & 0x6000) {
        ((u16 *)owner)[-1] |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
