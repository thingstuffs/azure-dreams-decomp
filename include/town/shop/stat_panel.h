#ifndef TOWN_SHOP_STAT_PANEL_H
#define TOWN_SHOP_STAT_PANEL_H
#include "town/shop/object.h"
#include "shared/sprite_part_command.h"
#include "shared/entity.h"
/* Initialize display entries and draw entity statistics panels. */

#include "common.h"
#include "shared/runtime_dispatch.h"

typedef struct Func800B8500Inner {
    u8 pad[8];
    s16 field_8;
    s16 field_A;
} Func800B8500Inner;

typedef struct Func800B8500Entry {
    void *value;
    Func800B8500Inner *inner;
} Func800B8500Entry;

void DrawSync(s32);
/* extern */
void LoadImage(void *, s32);
/* extern */
#include "slus/display_resource_cache_keys_data.h"
extern s32 lookup_patterned_display_icon(s32 value);
extern s32 get_enabled_record_flag_priority(s32 value);
extern s32 D_80077FBC[];
/* D_80082E6A: standalone byte global, declared >8B to force %hi/%lo
 * addressing (matches src/w_80047694.c sibling; same symbol, same form). */
/* D_800D1790: declared >8B so a plain value load also uses %hi/%lo. */
extern s32 D_800D1790[2];
extern s32 D_800892C0[3];
extern u8 D_8008933C[];
extern char *func_8004E5A0(s32 value, u16 width, char *dst);
extern s32 monster_get_species_name_text(s32);
extern void set_storage_entry_text(s32, const void *, s32, s32, s32); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void *format_gauge_text(void *, void *);
extern void *format_compared_stat_pairs(void *text, ActorRecord *stats);
extern s32 D_80089308[2];
extern u8 D_80089310[8];
extern u8 D_80089318[8];
extern u8 D_8008931C[8];
extern u8 D_80089324[8];
extern u8 D_80089340[8];

struct S_800B5264_0;
extern char *strcat(char *dst, const char *src);
extern void set_display_entry_text_and_position(struct S_800B5264_0 *entry, s32 text, s32 style, s16 x, s32 y);

/* Functions defined in this translation unit. */
void complete_display_transfer(ShopFirstCallbackObject *state);
void initialize_three_display_entries(s32 source_value, Func800B8500Entry **entries, void *entry_value);
s32 get_monster_status_label(void *entry);
void draw_formatted_monster_status_text(void *entry, void *display);
s32 normalize_monster_status_species_code(s32 value);
void draw_entity_stats_panel(void *entity, void *panel);

#endif
