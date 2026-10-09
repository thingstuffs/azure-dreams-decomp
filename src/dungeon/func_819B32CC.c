#include "common.h"
#include "shared/object_node.h"
#include "shared/object_flags.h"

/* The object an effect belongs to: bit 0x8000 of its +0x52 flag word marks it. */
typedef struct EffectOwner {
    u8 pad_00[0x52];
    u16 flags;
} EffectOwner;

/* The effect's own record; the 0x20-byte ObjectNodeHeader sits right before it. */
typedef struct EffectRecord {
    EffectOwner *owner;
} EffectRecord;

/* The sprite entry func_800478B8 updates; +0x14 carries the status bits tested below. */
typedef struct SpriteEntry {
    u8 pad_00[0x14];
    u16 status;
} SpriteEntry;

extern s32 func_800478B8();

/* Retail 819B32CC (func_80024ACC): marks the owner, and once the sprite reaches status 0x6000 marks the
 * effect's own header and the global object flags too. */
void func_80024ACC(EffectRecord *effect, void *unused, SpriteEntry *sprite) {
    EffectOwner *owner = effect->owner;

    owner->flags |= 0x8000;
    func_800478B8(sprite);
    if (sprite->status & 0x6000) {
        ((ObjectNodeHeader *)effect - 1)->flags |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
