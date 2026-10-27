#include "dungeon/menu_cache.h"

s32 get_menu_actor_index(void *actor)
{
    if (actor == primary_actor_record->actor.unk_AC.address) {
        return 0;
    }
    if (actor == primary_actor_record->actor.unk_B0.address) {
        return 1;
    }
    if (primary_actor_record->menu_alternate[0] != 0) {
        if (actor == primary_actor_record->menu_alternate[0]) {
            return 0;
        }
    }
    if (primary_actor_record->menu_alternate[1] != 0) {
        if (actor == primary_actor_record->menu_alternate[1]) {
            return 1;
        }
    }
    return 2;
}

void *get_menu_actor(s32 index)
{
    void *actor;
    if (index == 2) {
        actor = primary_actor_record;
    } else {
        actor = (&primary_actor_record->actor.unk_AC.address)[index];
    }
    return actor;
}

s32 get_menu_actor_mask(void)
{
    s32 mask = primary_actor_record->actor.unk_AC.address != 0;
    if (primary_actor_record->actor.unk_B0.address != 0) {
        mask |= 2;
    }
    return mask;
}

s32 list_menu_actor_records(void **records, s32 include_primary)
{
    s32 count = 0;
    if (include_primary) {
        records[0] = primary_actor_record;
        count = 1;
    }
    if (primary_actor_record->actor.unk_B0.address != 0) {
        records[count] = primary_actor_record->actor.unk_B0.address;
        count++;
    }
    if (primary_actor_record->actor.unk_AC.address != 0) {
        records[count] = primary_actor_record->actor.unk_AC.address;
        count++;
    }
    return count;
}

s32 list_menu_actor_records_with_primary(void **records)
{
    return list_menu_actor_records(records, 1);
}

s32 list_menu_linked_actor_records(void **records)
{
    return list_menu_actor_records(records, 0);
}
