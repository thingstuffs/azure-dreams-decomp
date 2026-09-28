#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_status.h"

extern void func_8009A028(void *arg0);
extern void func_8009A3D0(s32 arg0, s32 arg1, s32 arg2);
extern void func_800A2FE0(void *arg0);
extern void func_800A32A4(void *arg0);
extern void func_800A56E0(s32 arg0);
extern void func_800ACF88(void *arg0);


/* Advance the action phase and process the actor when the tile flags are set. */
void func_80173234(u8 *action, s32 unused, u8 *tile, u8 *actor)
{
    s32 status_flags;
    s32 actor_flags;
    s32 strength;
    s32 x;
    s32 y;
    u8 phase;

    phase = action[0x9B];
    if (phase != 0) {
        if (phase != 1) {
            return;
        }
        goto active;
    }

    if (dungeonStatus.unk_0A == 0) {
        status_flags = *(s32 *)(actor + 0x14);
        if (status_flags & 0x4000) {
            if (!(status_flags & 0x20000000)) {
                func_800ACF88(actor);
            }
        }

        action[0x9B]++;
        func_800A56E0(0x805);

active:
        if (*(u16 *)(tile + 0x14) & 0xE000) {
            if (((s32)dungeonStatus.unk_10) == (s32)(actor - 0x20)) {
                *(s32 *)&dungeonStatus.unk_10 &= 0x7FFFFFFF;
            }

            func_800A2FE0(actor);
            func_800A32A4(actor);

            actor_flags = *(s32 *)(actor + 0x1C);
            x = tile[0x24];
            y = tile[0x25];
            strength = 0x3000;
            if (actor_flags & 0x2000) {
                strength = 0x300;
            }
            func_8009A3D0(x, y, strength);
            func_8009A028(actor);

            *(u16 *)(actor - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }
}
