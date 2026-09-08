#include "common.h"

typedef struct DungeonGateState {
    u16 unk0;
    u16 flags;
    u8 pad4[4];
    s16 active;
} DungeonGateState;

typedef struct DungeonOwner {
    u8 pad0[0x58];
    void *field58;
} DungeonOwner;

extern DungeonGateState D_80083460;
extern DungeonOwner *D_800814A8;

extern s32 func_8009A180(void *, void *);
extern s16 func_800ADE74(void *, void *, void *, s16, s16, s32);

/* Process an entity and clear its high flag when relinking it into the active list. */
s16 func_800ADDA0(void *context, void *position, void *entity,
                  s16 near_range, s16 far_range, s32 state_out_addr) {
    register u16 entity_flags;
    s16 result = func_800ADE74(context, position, entity, near_range, far_range, state_out_addr);

    if (result && (result != 2) && (result != 3) &&
        ((D_80083460.active != 0) ||
         ((D_80083460.flags & 0x2808) != 0)) &&
        ((s16)func_8009A180(entity,
                           (u8 *)D_800814A8->field58 + 0x20) != 0)) {
        register s16 failure = -1;

        entity_flags = *(u16 *)((u8 *)entity + 0x46);
        entity_flags &= 0x7FFF;
        *(u16 *)((u8 *)entity + 0x46) = entity_flags;
        return failure;
    }
    return result;
}

