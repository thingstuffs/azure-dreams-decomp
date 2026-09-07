#include "common.h"

typedef struct Actor {
    u8 pad0[0x14];
    s32 flags14;
    u8 pad1[0x3C];
    s32 flags54;
} Actor;

typedef struct Slot {
    u8 pad0[0xAC];
    Actor *other;
} Slot;

extern s32 D_800E296C[3];
extern u8 *D_800E3D7C[];

/* Tests the global override or flag 0x20000 on the actor or its linked actors. */
s32 func_800C7F68(Actor *actor) {
    if (*D_800E296C & 0x10000000) {
        return 1;
    }
    if (actor->flags14 & 0x4000) {
        s32 slot_index = 1;
        u8 *slot_cursor = *D_800E3D7C + 4;
        do {
            Actor *linked_actor = ((Slot *)slot_cursor)->other;
            if ((linked_actor != 0) && (linked_actor->flags54 & 0x20000)) {
                return 1;
            }
            slot_index--;
            slot_cursor -= 4;
        } while (slot_index >= 0);
    } else if (actor->flags54 & 0x20000) {
        return 1;
    }
    return 0;
}
