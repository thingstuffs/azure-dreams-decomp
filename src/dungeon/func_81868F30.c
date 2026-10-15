#include "modules/dungeon_ovl_188898c.h"

void func_80024730(void *state_ref, void *unused, void *effect) {
    u16 scale;
    u8 brightness;
    void *state;

    state = *(void **)state_ref;
    *(u16 *)((u8 *)state + 0x14) = *(u16 *)((u8 *)state + 0x14) + 1;
    scale = *(u16 *)((u8 *)effect + 0x1E) - 0x400;
    brightness = *(u8 *)((u8 *)effect + 0xE) + 4;
    *(u16 *)((u8 *)effect + 0x1E) = scale;
    *(u16 *)((u8 *)effect + 0x1C) = scale;
    *(u8 *)((u8 *)effect + 0xE) = brightness;
    *(u8 *)((u8 *)effect + 0xD) = brightness;
    *(u8 *)((u8 *)effect + 0xC) = brightness;
    func_800478B8(effect);
    if (*(u16 *)((u8 *)effect + 0x14) & 0x6000) {
        *(s8 *)((u8 *)*(void **)state_ref + 0x16) = 1;
        *(u16 *)((u8 *)state_ref - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
