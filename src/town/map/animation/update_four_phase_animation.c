#include "common.h"
#include "town/map/animation.h"
#include "shared/object_flags.h"
#include "shared/object_links.h"
#include "town/menu.h"

   /* the 0x2 bytes before arg0 in update_four_phase_animation, addressed as arg0[-1] */

/* Updates a four-phase animation and clears its activity flag on completion. */
void update_four_phase_animation(TownMapPhaseObject *entity, void *context) {
    s8 *activity_flag;
    s32 phase;
    s32 phase_ticks;
    s32 quarter_ticks;
    s8 radius_bias;

    if (classify_object_against_bounds(entity, context) != 0) {
        activity_flag = entity->activity;
        if (activity_flag != 0) {
            *activity_flag = 0;
        }
        ((ObjectRetirementFlags *)entity)[-1].flags |= 0x8000;
        object_flag_block.flags = object_flag_block.flags | OBJECT_REMOVE_PENDING;
        return;
    }

    phase_ticks = entity->ticks.u + 1;
    phase = entity->phase.s;
    entity->ticks.u = phase_ticks;
    switch (phase) {
    case 0:
        quarter_ticks = (s16)phase_ticks / 4;
        entity->unk_66 = quarter_ticks * 3;
        radius_bias = (s16)entity->ticks.u / 2;
        entity->radius_bias = radius_bias;
        if (entity->ticks.s < 0x40) {
            break;
        }
        entity->ticks.u = 0;
        entity->phase.u++;
        break;
    case 1:
    {
        s32 inner_phase_ticks;

        inner_phase_ticks = (s16)phase_ticks / 4;
        entity->unk_66 = 0x30 - inner_phase_ticks * 3;
        entity->radius_bias = 0x20;
        if (entity->ticks.s >= 0x40) {
            entity->ticks.u = 0;
            entity->phase.u++;
        }
        break;
    }
    case 2:
    {
        s32 half_ticks;

        quarter_ticks = (s16)phase_ticks / 4;
        entity->unk_66 = quarter_ticks * 3;
        half_ticks = (s16)entity->ticks.u / 2;
        radius_bias = 0x20 - half_ticks;
        entity->radius_bias = radius_bias;
        if (entity->ticks.s < 0x40) {
            break;
        }
        entity->ticks.u = 0;
        entity->phase.u++;
        break;
    }
    case 3:
    {
        s32 inner_phase_ticks;

        inner_phase_ticks = (s16)phase_ticks / 4;
        entity->unk_66 = 0x30 - inner_phase_ticks * 3;
        entity->radius_bias = 0;
        if (entity->ticks.s < 0x40) {
            break;
        }
        entity->ticks.u = 0;
        entity->phase.s = 0;
        break;
    }
    default:
        break;
    }
}
