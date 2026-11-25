#ifndef DUNGEON_MENU_CACHE_STATS_H
#define DUNGEON_MENU_CACHE_STATS_H

#include "shared/entity.h"
#include "shared/item_menu.h"
#include "shared/sprite_part_command.h"

extern const char health_label[12];
extern const char tamer_label[12];
/* BYTES: the three prefixes declared with word alignment are copied whole; with the alignment known the copy
 * uses aligned word loads, and without it build_actor_status_line grows by eight bytes of unaligned loads. */
extern const char cached_status_prefix[8] __attribute__((aligned(4)));
extern const char cached_status_break[];
extern const char *cached_status_label[2];
extern const char cached_status_separator[];
extern const char cached_gauge_prefix[8] __attribute__((aligned(4)));
extern const char cached_full_gauge_marker[4];
extern const char cached_half_gauge_marker[4];
extern const char cached_gauge_suffix[4];
extern const char cached_equipment_prefix[8];
extern const char cached_equipment_separator[4];
extern const char cached_comparison_prefix[4];
extern const char cached_comparison_marker_separator[4];
extern const char cached_comparison_attack_separator[4];
extern const char cached_comparison_defense_separator[8];
extern const char cached_comparison_base_separator[4];
extern const char cached_stat_prefix[8] __attribute__((aligned(4)));
extern const char cached_stat_suffix[8];
extern const char cached_stat_line_break[4];
extern const char cached_stat_separator[8];
extern const char cached_stat_column_labels[24];
extern const char cached_status_line_break[4];
extern const char cached_hp_mp_break[4];
extern SpritePartCommand cached_opening_status_templates[4];

ItemMenuPart **layout_cached_display_pair(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *content);
void build_actor_status_line(ActorRecord *actor, ItemMenuPart **parts);
char *format_cached_gauge_text(char *output, ActorRecord *actor);
char *format_cached_equipment_bonuses(char *output, ActorRecord *actor);
char *format_cached_attack_defense(char *output, ActorRecord *actor);
void draw_cached_actor_stats(ActorRecord *actor, ItemMenuPart **panels);

struct ShopFirstCallbackObject;

s32 get_menu_actor_index(void *actor);
s32 normalize_monster_status_species_code(s32 value);
void draw_formatted_monster_status_text(void *actor, ItemMenuPart **parts);
void forward_display_entry_update(void *actor, ItemMenuPart **parts);
ItemMenuPart *link_cached_monster_display_entries(ItemMenuPart **parts);
void initialize_actor_status_display(ActorRecord *actor, ItemMenuPart **parts, SpritePartCommand *content);

void layout_status_icons(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *content);
void draw_party_actor_stats(ActorRecord *actor, ItemMenuPart **panels);
void initialize_party_display(ActorRecord *actor, ItemMenuPart **entries, SpritePartCommand *content);
ItemMenuPart *join_status_display_entries(ItemMenuPart **entries, struct ShopFirstCallbackObject *state);
void build_status_display(struct ShopFirstCallbackObject *state);
void reset_status_parts(struct ShopFirstCallbackObject *state);
void advance_status_opening(struct ShopFirstCallbackObject *state);
void layout_cached_opening_icons(ItemMenuPart **parts, s32 display_mode);
void release_status_entries(ItemMenuPart **entries);
struct MenuEntryObject;
void initialize_status_state(struct ShopFirstCallbackObject *state, ActorRecord *actor, s32 slot_index);
void change_status_display_target(struct MenuEntryObject *object, ActorRecord *actor, s16 slot_index);

#endif
