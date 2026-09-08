#include "common.h"

extern s32 func_80042900(void *entity, s32 arg1);
extern s32 func_8009A350(s32 arg0, s32 arg1, s32 arg2, u16 *arg3);

/* Checks entity eligibility using status flags and the linked entity's position. */
s32 func_800A41F0(void *entity) {
    u16 tile_flags;
    void *linked_entity;
    s32 check_result;

    if ((*(u8 *)((u8 *)entity + 0x28) + *(s16 *)((u8 *)entity + 0x64)) > 0) {
        if (*(s32 *)((u8 *)entity + 0x1C) & 0x2000) {
            linked_entity = *(void **)((u8 *)entity - 0x14);
            func_8009A350(*(u8 *)((u8 *)linked_entity + 0x24) - 1,
                          *(u8 *)((u8 *)linked_entity + 0x25), 0, &tile_flags);
            if (tile_flags & 2) {
                return 0;
            }
        }
        if (!(*(s32 *)((u8 *)entity + 0x1C) & 0x290000)) {
            check_result = func_80042900(entity, 0x1B) << 16;
            return check_result == 0;
        }
        return 0;
    }
    return 0;
}
