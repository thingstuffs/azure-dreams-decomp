#include "common.h"

extern s32 func_800CE4E8();
extern s32 D_800E296C;

/* Checks the entity at its linked coordinates unless a global override is set. */
s32 func_800CE6F0(void *entity) {
    void *position_record;

    if (D_800E296C & 0xC0000000) {
        return 1;
    }
    position_record = *(void **)((u8 *)entity - 0x14);
    return func_800CE4E8(
        *(u8 *)((u8 *)position_record + 0x24),
        *(u8 *)((u8 *)position_record + 0x25),
        *(s16 *)((u8 *)entity + 0x88),
        entity,
        1) != 0;
}
