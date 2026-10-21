#ifndef TOWN_SHOP_MONSTER_STATUS_OPENING_G00633_H
#define TOWN_SHOP_MONSTER_STATUS_OPENING_G00633_H
/* Advance monster status opening and display spacing (G00633): shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B8E20, CL:town/func_800B8E78. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/widget_views.h"

typedef struct S_800B65D8_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B65D8_4;

typedef struct S_800B65D8_0 {
    u8 pad_00[0x50];
    void * unk_50;
} S_800B65D8_0;

typedef struct S_800B65D8_1 {
    s32 unk_00;
    void * unk_04;
} S_800B65D8_1;

typedef struct S_800B65D8_3 {
    u8 pad_00[0x5C];
    s32 * unk_5C;
} S_800B65D8_3;

s32 select_display_spacing_table_entry();
/* extern */
int read_display_spacing_word(int);
/* extern */
s32 read_display_spacing_byte();
/* extern */
void set_monster_status_panel_height();
/* extern */
extern u8 D_80089344[];
extern void process_object_data_by_mode(void *object);
extern s32 D_800B6578[];

/* Functions defined in this translation unit. */
void update_mode_display_spacing(S_800B65D8_3 *base, s32 display_mode);
void advance_monster_status_opening(void *object);

#endif
