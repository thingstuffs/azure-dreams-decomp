#include "town/shop.h"
#include "town/shop/position.h"
#include "dungeon/system.h"
#include "sdk/libc.h"
#include "dungeon/menu_cache_stats.h"
#include "shared/record_ptrs.h"

/* The dungeon status line uses the first label. */
const char *cached_status_label[2] = {tamer_label, health_label};

/* Draw the player name followed by the selected actor's status. */
void build_actor_status_line(ActorRecord *actor, ItemMenuPart **parts)
{
    char text[64];

    memcpy(text, cached_status_prefix, 5);
    strcat(text, primary_actor_record->name);
    strcat(text, cached_status_break);
    strcat(text, cached_status_label[0]);
    strcat(text, cached_status_separator);
    strcat(text, (const char *)(unsigned long)(u32)select_status_text(actor));
    /* The text setter receives the string address as a word. */
    set_display_entry_text_and_position(parts[3], (s32)(unsigned long)text, 0, 0x47, 0x88);
}

/* Initialize the party actor display and populate its alternate entry rows. */
void initialize_party_display(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *content)
{
    layout_status_icons(actor, entries, content);
    draw_formatted_monster_status_text(actor, entries);
    draw_party_actor_stats(actor, entries);
    forward_display_entry_update(actor, entries);
}

void initialize_actor_status_display(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *content)
{
    layout_cached_display_pair(actor, entries, content);
    build_actor_status_line(actor, entries);
    draw_cached_actor_stats(actor, entries);
    populate_display_rows(actor, entries);
}
