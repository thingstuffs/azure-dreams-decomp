#include "modules/dungeon_floor_switch_owners.h"

/* Exact jump_table span; dispatch consumer dungeon/func_8028A4AC. */
const u32 D_80016000[13] __attribute__((aligned(4))) = {
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x50),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x5C),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x94),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x114),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0xCC),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104),
    (u32)((u8 *)dungeonChooseRandomRegionFeature + 0x104)
};
