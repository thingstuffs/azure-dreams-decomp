#include "common.h"
#include "town/scene/effect.h"
#include "town/scene/score_sprite_data.h"
#include "town/devkit/old_minigame_imports.h"


typedef void (*Callback)(void);

extern void advance_three_component_motion();


typedef struct SpawnMotion {
    u8 pad_00[0x2];
    s16 x;
    u8 pad_04[0x2];
    s16 y;
    u8 pad_08[0x2];
    s16 z;
    s32 velocity_x;
    u8 pad_10[0x4];
    s32 velocity_z;
} SpawnMotion;   /* motion in spawn_scattered_seed_effect */

typedef struct SpawnSeed {
    u8 pad_00[0x2];
    u16 x;
    u8 pad_04[0x2];
    u16 y;
    u8 pad_08[0x2];
    u16 z;
    s32 velocity_x;
} SpawnSeed;   /* seed in spawn_scattered_seed_effect */

/* Spawn a 0x136 effect scattered +-20 around the seed, with a randomised vertical kick. */
void spawn_scattered_seed_effect(SpawnSeed *seed) {
    void *sprite;
    SpawnMotion *motion;
    void *slot;

    slot = func_800373DC(0x136);
    if (slot != 0) {
        (*(Callback *)((u8 *)slot + 0x10)) = advance_three_component_motion;
        func_8003BC18(slot, score_sprite_draw_callback_address);
        motion = (*(void * *)((u8 *)slot + 8));
        sprite = (*(void * *)((u8 *)slot + 0xC));
        motion->x =
            (seed->x + (func_80071494() % 40)) - 0x14;
        motion->y =
            (seed->y + (func_80071494() % 40)) - 0x14;
        motion->z =
            (seed->z + (func_80071494() % 40)) - 0x14;
        motion->velocity_x = seed->velocity_x;
        motion->velocity_z =
            ((func_80071494() & 0x1FF) - 0x100) * 0x400;
        (*(s16 *)((u8 *)slot + 0x2E)) = 3;
        (*(s16 *)((u8 *)sprite + 0x1E)) = 0x1000;
        (*(s16 *)((u8 *)sprite + 0x1C)) = 0x1000;
        (*(Callback *)((u8 *)sprite + 8)) = func_8028E170;
        (*(s8 *)((u8 *)sprite + 4)) = 0;
        (*(s8 *)((u8 *)sprite + 5)) = 0;
        (*(s32 *)((u8 *)sprite + 0xC)) = 0x808080;
        (*(u16 *)((u8 *)sprite + 0x14)) |= 0xC;
    }
}
