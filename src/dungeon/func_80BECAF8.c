#include "modules/dungeon_resource16_slot0.h"

void func_801722F8(void *state, s32 unused, s32 source, s32 target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = ((s32 *)func_80171014);
            if (dungeonStatus.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (dungeonStatus.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
