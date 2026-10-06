#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[6];
    s16 field_0x6;
    u8 pad8[4];
} DungeonState;

extern void func_800A08A0(s32);
extern s32 func_800A6D30(void);
extern s16 D_8008146E;


/* Counts down turns until a monster spawn, then resets the spawn timer. */
void func_800A0DD8(s32 unused0, s32 unused1, s32 unused2, s32 unused3) {
    s16 spawn_turns;

    if (D_8008146E != 0) {
        spawn_turns = dungeonStatus.unk_06 - 1;
        dungeonStatus.unk_06 = spawn_turns;
        if (spawn_turns < 0) {
            dungeonStatus.unk_06 = (func_800A6D30() & 0x1F) | 0x20;
            func_800A08A0(0);
        }
    }
}
