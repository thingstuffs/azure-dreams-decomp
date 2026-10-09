#include "common.h"
#include "shared/dungeon_status.h"

extern s32 func_800A4ACC();
extern s32 func_800AB1C0();
extern s32 func_800AD594();
extern s32 func_800AD9B4();

extern void func_80171138(void *, void *, void *, void *);

/* Select the bank actor callback when the resident checks succeed. */
void func_8017239C(void *state, s32 unused, s32 source, s32 target) {
    if (func_800AB1C0() != 0) {
        func_800AD594(target, 4);
        func_800A4ACC(target);
        if ((func_800AD9B4(source, target) << 16) > 0) {
            *(void (**)(void *, void *, void *, void *))((u8 *)state + 0x8C) = func_80171138;
            if (dungeonStatus.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (dungeonStatus.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
