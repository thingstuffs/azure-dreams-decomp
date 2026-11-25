#include "slus.h"
#include "dungeon/menu_cache_familiar_prompt.h"
#include "engine/entity.h"
#include "dungeon/menu_cache_stats.h"
#include "town/shop/display_element_layout_g00630.h"

/* Position both display entries and attach the supplied content to the second. */
ItemMenuPart **layout_cached_display_pair(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *content)
{
    entries[0]->position->x = -0x38;
    entries[0]->position->y = 8;
    entries[0]->handler = D_80077FBC;
    entries[1]->position->x = -0x38;
    entries[1]->position->y = 8;
    entries[1]->handler = content;
    return entries;
}

/* Position the status icons and select the badge for the displayed actor. */
void layout_status_icons(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *content)
{
    entries[0]->position->x = -0x38;
    entries[0]->position->y = 8;
    entries[0]->handler = D_80077FBC;
    entries[1]->position->x = -0x38;
    entries[1]->position->y = 8;
    entries[1]->handler = content;
    entries[2]->position->x = -0x10;
    entries[2]->position->y = 0x16;
    entries[2]->handler = (void *)(unsigned long)(u32)lookup_patterned_display_icon(get_enabled_record_flag_priority(actor));
    entries[20]->position->x = -1;
    entries[20]->position->y = 23;
    entries[20]->handler = get_assigned_familiar_marker(get_menu_actor_index(actor));
}
