#include "dungeon/menu_cache_familiar_prompt.h"

static const u8 cached_familiar_slot_highlights[4][2] = {
    {1, 0}, {0, 1}, {0, 0}, {0, 0},
};

void shade_familiar_slot(ItemMenuPart *part, s32 highlight)
{
    u8 shade = highlight ? 0x80 : 0x50;
    ItemMenuPartPosition *position = part->position;

    position->color.c.b = shade;
    position->color.c.g = shade;
    position->color.c.r = shade;
}

void shade_familiar_assignment_slots(ItemMenuPart **parts, s32 slot)
{
    shade_familiar_slot(parts[21], cached_familiar_slot_highlights[slot][0]);
    shade_familiar_slot(parts[22], cached_familiar_slot_highlights[slot][1]);
}

s32 select_familiar_assignment_slot(ActorRecord *actor, s32 requested_slot, s32 available_mask)
{
    s32 slot = get_menu_actor_index(actor);

    if (slot == 2) {
        s32 active_mask = get_menu_actor_mask();

        slot = 0;
        if (available_mask == 3) {
            slot = 1;
            if (active_mask != 1) {
                slot = 0;
                if (active_mask == 0) {
                    slot = requested_slot;
                }
            }
        }
    }
    return slot;
}
