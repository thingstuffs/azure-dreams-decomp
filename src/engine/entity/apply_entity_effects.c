#include "shared/actor_property_flags.h"
#include "shared/actor_status_flags.h"
#include "shared/actor_status_ids.h"
#include "common.h"
#include "engine/entity.h"

#define S32(o, p) (*(s32 *)((u8 *)(p) + (o)))


/* Apply entity effects to scale, stats, and status flags. */
void apply_entity_effects(void *entity)
{
    ActorRecord *actor = entity;
    s32 effect_flags;
    s32 boosted_stat;

    {
        s32 scale;
        s32 scale_flags;

        actor->turn_speed = 0x100;
        scale_flags = actor->status_flags;
        scale = 0x10;
        actor->unk_87 = scale;
        if (scale_flags & 1) {
            s32 base_scale;
            u8 read_scale;

            base_scale = (u16)actor->turn_speed;
            read_scale = (u32)S32(0x84, actor) >> 24;
            actor->turn_speed = base_scale * 2;
            read_scale *= 2;
            actor->unk_87 = read_scale;
        }
    }

    {

        boosted_stat = get_entity_effect_value(actor, STATUS_SPEED);
        boosted_stat = (s16)boosted_stat;
        if (boosted_stat > 0) {
            actor->turn_speed = (u16)actor->turn_speed * 2;
            actor->unk_87 = actor->unk_87 * 2;
        } else if (boosted_stat < 0) {
            actor->turn_speed = (s32)((u16)actor->turn_speed << 16) >> 17;
            actor->unk_87 = actor->unk_87 >> 1;
        }
    }

    if (actor->status_flags & 2) {
        boosted_stat = actor->level_max_hp * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        actor->max_hp = boosted_stat;
    } else {
        actor->max_hp = actor->level_max_hp;
    }

    if (actor->status_flags & 4) {
        boosted_stat = actor->level_max_mp * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        actor->max_mp = boosted_stat;
    } else {
        actor->max_mp = actor->level_max_mp;
    }

    if (actor->status_flags & 8) {
        boosted_stat = actor->attack * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        actor->base_attack = boosted_stat;
    } else {
        actor->base_attack = actor->attack;
    }

    if (actor->status_flags & 0x10) {
        boosted_stat = actor->defense * 2;
        if (boosted_stat >= 0x100) {
            boosted_stat = 0xFF;
        }
        actor->base_defense = boosted_stat;
    } else {
        actor->base_defense = actor->defense;
    }

    {
        s32 slot_index = 2;
        u8 *slot;

        do {
            slot = (u8 *)actor + slot_index * 3;
            if (slot[8] != 0) {
                if (actor->status_flags & 0x80) {
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

    if (actor->status_flags & 0x04000000) {
        actor->flags14 |= ACTOR_RESIST_CONFUSION;
        actor->flags1C &= ~ACTOR_CONFUSED;
    }

    if (actor->status_flags & 0x02000000) {
        actor->flags14 |= ACTOR_RESIST_SLEEP;
        actor->flags1C &= ~ACTOR_ASLEEP;
    } else {
        actor->flags14 &= ~ACTOR_RESIST_SLEEP;
    }

    if (actor->status_flags & 0x08000000) {
        actor->flags14 |= ACTOR_RESIST_BLIND;
        actor->flags1C &= ~ACTOR_BLIND;
    } else {
        actor->flags14 &= ~ACTOR_RESIST_BLIND;
    }

    if (actor->status_flags & 0x10000000) {
        actor->flags14 |= ACTOR_RESIST_PARALYSIS;
        actor->flags1C &= ~ACTOR_PARALYZED;
    } else {
        actor->flags14 &= ~ACTOR_RESIST_PARALYSIS;
    }

    if (actor->status_flags & 0x20000000) {
        actor->flags14 |= ACTOR_RESIST_POISON;
        actor->flags1C &= ~ACTOR_POISONED;
    } else {
        actor->flags14 &= ~ACTOR_RESIST_POISON;
    }

    if (actor->status_flags & 0x40000000) {
        actor->flags14 |= ACTOR_RESIST_MAGIC_BIND;
        actor->flags1C &= ~ACTOR_MAGIC_BOUND;
    } else {
        actor->flags14 &= ~ACTOR_RESIST_MAGIC_BIND;
    }

    if (actor->status_flags & 0x200000) {
        actor->flags1C |= ACTOR_ANGRY;
        actor->flags14 &= ~0x1000;
    }

    effect_flags = actor->status_flags;
    if ((effect_flags & 0x800000) && ((u32)(actor->species - 3) < 0x2B) && (actor->carried_item.unk_00 != 4)) {
        actor->status_flags = effect_flags & 0xFF7FFFFF;
    }
}
