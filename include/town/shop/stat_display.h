#ifndef TOWN_SHOP_STAT_DISPLAY_H
#define TOWN_SHOP_STAT_DISPLAY_H
/* Format compared object statistics and populate display rows. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "shared/record_ptrs.h"
#include "shared/widget_views.h"

typedef struct {
    s32 word;
    s8 tail;
} __attribute__((packed)) Text5;

typedef struct {
    s8 x;
    s8 y;
    s8 z;
} Vec3s;

typedef struct {
    u8 pad0[2];
    s8 value;
} Input;

typedef struct S_800B59A4_3 {
    u8 pad_00[0x30];
    void * unk_30;
} S_800B59A4_3;

typedef struct S_800B59A4_4 {
    s32 unk_00;
    void * unk_04;
} S_800B59A4_4;

typedef struct S_800B59A4_5 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B59A4_5;

struct S_800B5264_0;

typedef struct S_800B59A4_0 {
    u8 pad_00[0x18];
    s32 unk_18;
    u8 pad_1C[0x8];
    s32 unk_24;
} S_800B59A4_0;

typedef struct S_800B59A4_1 {
    u8 unk_00;
    u8 unk_01;
} S_800B59A4_1;

extern s32 calc_gauge_fill(void *);
extern Text5 D_800892DC;
extern u8 D_800892E8[];
extern u8 D_800892EC[];
/* extern */
extern char D_800892D8[];
extern Vec3s D_800892F0;
extern char stat_text_format_separator[];
extern char D_800892F8[];
extern char D_800892FC[];
extern u8 *remap_flagged_string_bytes(u8 *text);
extern s32 D_80089308[2];
extern u8 D_80089310[];
extern u8 D_80089318[];
extern u8 D_8008931C[];
extern u8 D_80089324[];
s32 lookup_item_category_mapped_value(s32, s32);
s32 select_item_data();
#include "sdk/bzero.h"
void set_display_entry_text_and_position(struct S_800B5264_0 *, s32, s32, s16, s32);

/* Unified declarations, checked against definitions and every merged caller. */
extern char *strcat(char *dst, const char *src);
extern char *func_8004E5A0(s32 value, u16 width, char *dst);
extern char *func_8004E634(u32 value, char *dst);
extern void func_800B53BC(s32 entry, const void *text, s32 style, s32 x, s32 y);
extern u8 D_80089304[];

/* Functions defined in this translation unit. */
void *format_object_value_marker(void *output, void *object);
s32 compare_values_to_display_code(s32 left, s32 right);
void *format_compared_stat_pairs(void *text, ActorRecord *stats);
void format_and_display_entity_stats(void *stats, void *panels);
void collect_selected_record_values(s32 *output, EntityRec *record);
u8 *format_optional_signed_value(Input *input, u8 *text);
void populate_display_rows(s32 source_id, void *display);

#endif
