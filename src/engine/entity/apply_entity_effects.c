#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "engine/entity.h"

#define U8(o, p)  (*(u8 *)((u8 *)(p) + (o)))
#define S8(o, p)  (*(s8 *)((u8 *)(p) + (o)))
#define U16(o, p) (*(u16 *)((u8 *)(p) + (o)))
#define S32(o, p) (*(s32 *)((u8 *)(p) + (o)))

extern s16 get_entity_effect_value(void *, s32);

/* Apply entity effects to scale, stats, and status flags. */
void apply_entity_effects(void *entity)
{
    s32 effect_flags;
    s32 boosted_stat;

    {
        s32 scale;
        s32 scale_flags;

        U16(0x6E, entity) = 0x100;
        scale_flags = S32(0x54, entity);
        scale = 0x10;
        U8(0x87, entity) = scale;
        if (scale_flags & 1) {
            s32 base_scale;
            u8 read_scale;

            base_scale = U16(0x6E, entity);
            read_scale = (u32)S32(0x84, entity) >> 24;
            U16(0x6E, entity) = base_scale * 2;
            read_scale *= 2;
            U8(0x87, entity) = read_scale;
        }
    }

    {

        boosted_stat = get_entity_effect_value(entity, STATUS_SPEED);
        boosted_stat = (s16)boosted_stat;
        if (boosted_stat > 0) {
            U16(0x6E, entity) = U16(0x6E, entity) * 2;
            U8(0x87, entity) = U8(0x87, entity) * 2;
        } else if (boosted_stat < 0) {
            U16(0x6E, entity) = (s32)(U16(0x6E, entity) << 16) >> 17;
            U8(0x87, entity) = U8(0x87, entity) >> 1;
        }
    }

    if (S32(0x54, entity) & 2) {
        boosted_stat = U8(5, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x29, entity) = boosted_stat;
    } else {
        U8(0x29, entity) = U8(5, entity);
    }

    if (S32(0x54, entity) & 4) {
        boosted_stat = U8(4, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x66, entity) = boosted_stat;
    } else {
        U8(0x66, entity) = U8(4, entity);
    }

    if (S32(0x54, entity) & 8) {
        boosted_stat = U8(0, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x68, entity) = boosted_stat;
    } else {
        U8(0x68, entity) = U8(0, entity);
    }

    if (S32(0x54, entity) & 0x10) {
        boosted_stat = U8(1, entity) * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        U8(0x69, entity) = boosted_stat;
    } else {
        U8(0x69, entity) = U8(1, entity);
    }

    {
        s32 slot_index = 2;
        u8 *slot;

        do {
            slot = (u8 *)entity + slot_index * 3;
            if (slot[8] != 0) {
                if (S32(0x54, entity) & 0x80) {
                    boosted_stat = slot[0xA] * 2;
                    if (boosted_stat >= 0x64) {
                        boosted_stat = 0x63;
                    }
                    slot[9] = boosted_stat;
                } else {
                    slot[9] = slot[0xA];
                }
            }
            slot_index--;
        } while (slot_index >= 0);
    }

    if (S32(0x54, entity) & 0x04000000) {
        S32(0x14, entity) |= ACTOR_RESIST_CONFUSION;
        S32(0x1C, entity) &= ~ACTOR_CONFUSED;
    }

    if (S32(0x54, entity) & 0x02000000) {
        S32(0x14, entity) |= ACTOR_RESIST_SLEEP;
        S32(0x1C, entity) &= ~ACTOR_ASLEEP;
    } else {
        S32(0x14, entity) &= ~ACTOR_RESIST_SLEEP;
    }

    if (S32(0x54, entity) & 0x08000000) {
        S32(0x14, entity) |= ACTOR_RESIST_BLIND;
        S32(0x1C, entity) &= ~ACTOR_BLIND;
    } else {
        S32(0x14, entity) &= ~ACTOR_RESIST_BLIND;
    }

    if (S32(0x54, entity) & 0x10000000) {
        S32(0x14, entity) |= ACTOR_RESIST_PARALYSIS;
        S32(0x1C, entity) &= ~ACTOR_PARALYZED;
    } else {
        S32(0x14, entity) &= ~ACTOR_RESIST_PARALYSIS;
    }

    if (S32(0x54, entity) & 0x20000000) {
        S32(0x14, entity) |= ACTOR_RESIST_POISON;
        S32(0x1C, entity) &= ~ACTOR_POISONED;
    } else {
        S32(0x14, entity) &= ~ACTOR_RESIST_POISON;
    }

    if (S32(0x54, entity) & 0x40000000) {
        S32(0x14, entity) |= ACTOR_RESIST_MAGIC_BIND;
        S32(0x1C, entity) &= ~ACTOR_MAGIC_BOUND;
    } else {
        S32(0x14, entity) &= ~ACTOR_RESIST_MAGIC_BIND;
    }

    if (S32(0x54, entity) & 0x200000) {
        S32(0x1C, entity) |= ACTOR_ANGRY;
        S32(0x14, entity) &= ~0x1000;
    }

    effect_flags = S32(0x54, entity);
    if ((effect_flags & 0x800000) && ((u32)(U8(0x13, entity) - 3) < 0x2B) && (U8(0x48, entity) != 4)) {
        S32(0x54, entity) = effect_flags & 0xFF7FFFFF;
    }
}
