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

s32 func_800C7F68(Actor *actor) {
    if (*D_800E296C & 0x10000000) {
        return 1;
    }
    if (actor->flags14 & 0x4000) {
        s32 count = 1;
        u8 *slot = *D_800E3D7C + 4;
        do {
            Actor *other = ((Slot *)slot)->other;
            if ((other != 0) && (other->flags54 & 0x20000)) {
                return 1;
            }
            count--;
            slot -= 4;
        } while (count >= 0);
    } else if (actor->flags54 & 0x20000) {
        return 1;
    }
    return 0;
}
