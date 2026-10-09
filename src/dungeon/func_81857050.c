#include "common.h"
#include "modules/dungeon_native_abi.h"
#include "shared/slus_callbacks.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

typedef struct EffectMotion {
    s32 x, y, z;
    s32 vx, vy, vz;
} EffectMotion;

/* The object an effect belongs to: bit 0x8000 of its +0x52 flag word marks it. */
typedef struct EffectOwner {
    u8 pad_00[0x52];
    u16 flags;
} EffectOwner;

/* The effect's own record; the 0x20-byte ObjectNodeHeader sits right before it. */
typedef struct EffectRecord {
    EffectOwner *owner;
    u8 pad_04[0x44];
    u16 timer;       /* 0x48: frames to wait in state 0 */
    s16 fade_step;   /* 0x4A: brightness removed per frame in state 1 */
    s16 state;       /* 0x4C: 0 = wait, 1 = fade the sprite */
} EffectRecord;

typedef struct SpriteEntry {
    u8 pad_00[4];
    u8 unk_04;
    u8 unk_05;
    u8 pad_06[6];
    u8 red;          /* 0x0C; the word at +0x0C is cleared as one */
    u8 green;
    u8 blue;
    u8 pad_0F;
    u8 pad_10[4];
    u16 status;      /* 0x14: func_800478B8 result bits, 0x6000 = reached */
} SpriteEntry;

/* Retail 81857050 (func_80024850): updates the effect's motion, waits for its timer, then fades its sprite to
 * black and marks the effect (header and global flags) finished. */
void func_80024850(EffectRecord *effect, EffectMotion *motion, SpriteEntry *sprite) {
    EffectOwner *owner = effect->owner;
    s32 z_velocity;
    s16 state;
    u16 timer;
    u8 brightness;

    owner->flags |= 0x8000;

    z_velocity = motion->vz;
    if (z_velocity != 0) {
        z_velocity -= 0x20000;
    }
    motion->vz = z_velocity;
    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;

    state = effect->state;
    switch (state) {
    case 0:
        timer = effect->timer - 1;
        effect->timer = timer;
        if ((s16)timer <= 0) {
            func_8004491C((ObjectNodeHeader *)effect - 1, (s32)func_80045340);
            effect->state += 1;
        }
        break;

    case 1:
        func_800478B8(sprite);
        if (sprite->status & 0x6000) {
            sprite->unk_04 = 0;
            sprite->unk_05 = 0;
        }
        if (sprite->red <= effect->fade_step) {
            *(u32 *)&sprite->red = 0;
            ((ObjectNodeHeader *)effect - 1)->flags |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
            return;
        }
        brightness = sprite->blue - effect->fade_step;
        sprite->blue = brightness;
        sprite->green = brightness;
        sprite->red = brightness;
        break;
    }
}
