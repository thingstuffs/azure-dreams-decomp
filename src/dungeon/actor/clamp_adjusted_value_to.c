#include "common.h"
#include "shared/entity.h"

typedef struct {
    u8 pad0[0x50];
    void *unk50;
    u8 pad54[0x32];
    u8 unk86;
} UnkStruct;

/* Return the adjusted value clamped to the range 0 through 99. */
s16 clamp_adjusted_value_0_to_99(ActorRecord *entity) {
    s16 adjusted_value;

    adjusted_value = entity->unk_86;
    if (entity->unk_50.address != 0) {
        adjusted_value += *(s8 *)((u8 *)entity->unk_50.address + 2);
    }
    if (adjusted_value < 0) {
        adjusted_value = 0;
    }
    if (adjusted_value >= 100) {
        adjusted_value = 99;
    }
    return adjusted_value;
}
