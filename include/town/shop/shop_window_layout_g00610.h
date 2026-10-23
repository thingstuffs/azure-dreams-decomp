#ifndef TOWN_SHOP_SHOP_WINDOW_LAYOUT_G00610_H
#define TOWN_SHOP_SHOP_WINDOW_LAYOUT_G00610_H
/* Shop window layout declarations (G00610). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B3A28, CL:town/func_800B3C30. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B0C68_arg0.h"
#include "shared/widget_views.h"

typedef struct S_800B1188_2 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x10];
    void * unk_24;
    u8 pad_28[0x10];
    void * unk_38;
    u8 pad_3C[0x10];
    void * unk_4C;
    u8 pad_50[0x10];
    void * unk_60;
} S_800B1188_2;

typedef struct S_800B1188_3 {
    s32 ** unk_00;
    void ** unk_04;
    s32 unk_08;
    s32 ** unk_0C;
} S_800B1188_3;

/* ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv in initialize_shop_window_layout */
typedef struct S_800B1188_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_4;

typedef struct S_800B1188_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_5;

typedef struct S_800B1188_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_6;

typedef struct S_800B1188_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_7;

typedef struct S_800B1188_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_8;

typedef struct S_800B1188_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_9;

/* ((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_04 in initialize_shop_window_layout */
typedef struct S_800B1188_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_10;

typedef struct S_800B1188_11 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_11;

typedef struct S_800B1188_12 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_12;

typedef struct S_800B1188_13 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_13;

typedef struct S_800B1188_14 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_14;

/* ((S_800B1188_9 *)(((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_04))->unk_04 in initialize_shop_window_layout */
struct S8004CBFC_a0;

struct S8004CBFC_a1;

struct Rec_func_800B0C68_arg0;

struct S_800B0FD4_0;

typedef struct S_800B1390_0 {
    s32 *unk_m10;
    u8 pad_m0C[0xC];
} S_800B1390_0;

typedef struct S_800B1390_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    u8 pad_1C[0x4];
    s32 unk_20;
    s32 unk_24;
} S_800B1390_1;

void initialize_scaled_entry_cursor(struct S8004CBFC_a0 *, struct S8004CBFC_a1 *, int *);
void process_shop_record_and_subrecord(s32);
void position_shop_row_widgets(struct Rec_func_800B0C68_arg0 *);
void position_shop_child_elements(struct Rec_func_800B0C68_arg0 *);
void populate_shop_item_rows(struct S_800B0FD4_0 *);
extern M2C_UNK D_800788E0;
struct S8004CBFC_a1; extern struct S8004CBFC_a1 shop_cursor_template;
extern M2C_UNK D_800D15F4;
extern s32 D_800B0824[];
extern void initialize_shop_parts(void *, void *, void *);

/* Functions defined in this translation unit. */
void initialize_shop_window_layout(void *ui);
void initialize_shop_subrecord(void *record_data, s32 value_20, s32 value_08, s32 value_0c, s32 value_10, s32 value_14, s32 value_24, s32 value_18);
void configure_shop_object_and_finalize(void *object, s32 setup_value_1, s32 setup_value_2, s32 setup_value_3, s32 setup_value_4, s32 setup_value_5, s32 setup_value_6, s32 setup_value_7);

#endif
