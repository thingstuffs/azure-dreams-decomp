#ifndef TOWN_SHOP_STAT_DISPLAY_H
#define TOWN_SHOP_STAT_DISPLAY_H
struct ActorRecord;
/* Format compared object statistics and populate display rows. */

#include "common.h"
#include "shared/dungeon_item_entries.h"
#include "shared/item_menu.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/widget_views.h"
#include "engine/item.h"

typedef struct {
    s32 word;
    s8 tail;
} __attribute__((packed)) Text5;

typedef struct {
    s8 x;
    s8 y;
    s8 z;
} Vec3s;

extern PlayerRecord *primary_actor_record;
extern Text5 D_800892DC;
extern u8 D_800892E8[];
extern u8 D_800892EC[];
/* extern */
extern char D_800892D8[];
extern Vec3s D_800892F0;
extern char stat_text_format_separator[];
extern char D_800892F8[];
extern char D_800892FC[];
extern s32 D_80089308[2];
extern u8 D_80089310[];
extern u8 D_80089318[];
extern u8 D_8008931C[];
extern u8 D_80089324[];
#include "sdk/bzero.h"
void set_display_entry_text_and_position(ItemMenuPart *, s32, s32, s16, s32);

/* Unified declarations, checked against definitions and every merged caller. */
extern char *strcat(char *dst, const char *src);
extern char *func_8004E5A0(s32 value, u16 width, char *dst);
extern char *func_8004E634(u32 value, char *dst);
void set_storage_entry_text(ItemMenuPart *entry, char *text, s32 style, s16 x, s32 y);
extern u8 D_80089304[];

/* Functions defined in this translation unit. */
void *format_gauge_text(void *output, void *object);
s32 compare_values_to_display_code(s32 left, s32 right);
void *format_compared_stat_pairs(void *text, ActorRecord *stats);
void format_and_display_entity_stats(struct ActorRecord *stats, ItemMenuPart **panels);
void collect_selected_record_values(s32 *output, ActorRecord *record);
u8 *format_optional_signed_value(DungeonItemEntry *input, u8 *text);
void populate_display_rows(struct ActorRecord *actor, ItemMenuPart **display);

#endif
