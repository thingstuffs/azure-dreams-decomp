#include "common.h"

extern void dungeonUpdateLongActorAction(void);

/* Exact jump_table span; dispatch consumer dungeon/func_80FB176C. */
const u32 D_80170820[12] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x828),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x828),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x828),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x854),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x7D4),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x7D4),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x7D4),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x76C),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x76C),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x854),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x854),
    (u32)((u8 *)dungeonUpdateLongActorAction + 0x818)
};
