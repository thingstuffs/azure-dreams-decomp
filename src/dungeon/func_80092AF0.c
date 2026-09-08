#include "common.h"

typedef struct {
    u8 pad0[0x50];
    void *unk50;
    u8 pad54[0x32];
    u8 unk86;
} UnkStruct;

/* Return the adjusted value clamped to the range 0 through 99. */
s16 func_80098250(UnkStruct *entity) {
    s16 adjusted_value;

    adjusted_value = entity->unk86;
    if (entity->unk50 != 0) {
        adjusted_value += *(s8 *)((u8 *)entity->unk50 + 2);
    }
    if (adjusted_value < 0) {
        adjusted_value = 0;
    }
    if (adjusted_value >= 100) {
        adjusted_value = 99;
    }
    return adjusted_value;
}
