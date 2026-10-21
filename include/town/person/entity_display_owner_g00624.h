#ifndef TOWN_PERSON_ENTITY_DISPLAY_OWNER_G00624_H
#define TOWN_PERSON_ENTITY_DISPLAY_OWNER_G00624_H
/* Entity display owner (G00624). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800B678C, CL:town/func_800B6858, CL:town/func_800B6980, CL:town/func_800B6A28, CL:town/func_800B6BF0, CL:town/func_800B6C88, CL:town/func_800B6D34. */

#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B3FB8_arg0.h"

typedef struct S_800B4350_1 {
    u8 pad_00[0x5C];
    void * unk_5C;
} S_800B4350_1;

/* arg0 in initialize_dual_child_entries */
typedef struct S_800B4350_2 {
    u8 pad_00[0x78];
    s32 * unk_78;
    s32 * unk_7C;
} S_800B4350_2;

/* ((S_800B4350_1 *)arg0)->unk_5C in initialize_dual_child_entries */
typedef struct S_800B4350_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B4350_3;

/* ((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_78 in initialize_dual_child_entries */
typedef struct S_800B4350_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B4350_4;

/* ((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_7C in initialize_dual_child_entries */
typedef struct S_800B4350_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B4350_5;

/* ((S_800B4350_3 *)(((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_78))->unk_04 in initialize_dual_child_entries */
typedef struct S_800B4350_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B4350_6;

/* ((S_800B4350_4 *)(((S_800B4350_2 *)(((S_800B4350_1 *)arg0)->unk_5C))->unk_7C))->unk_04 in initialize_dual_child_entries */
typedef struct S_800B4350_0 {
    u8 pad_00[0x20];
    s32 unk_20;
} S_800B4350_0;

/* extern */
struct Rec_func_800B3FB8_arg0;

struct S_800B3FB8_2;

/* extern */
struct S_800B4350_0;

typedef struct S_800B4494_0 {
    s32 * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
} S_800B4494_0;

void upload_three_color_gradient_palette(s32 palette_slot, u8 *rgb_start, u8 *rgb_mid, u8 *rgb_end, s32 blend_row, s32 semitrans_end);
void update_four_slot_element_values_and_positions(struct Rec_func_800B3FB8_arg0 *, struct S_800B3FB8_2 *, s32);
/* extern */
void copy_contiguous_display_blocks(void *);
/* extern */
void copy_display_template_blocks();
/* extern */
void func_800B426C(void *);
/* extern */
extern M2C_UNK D_800D1658;
extern M2C_UNK D_800D175C;
/* arg0 in set_record_base_and_data_pointer_alt; pointer addresses record offset 0x10 */
/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800B3E68;
extern void initialize_entity_display_parts();

/* Functions defined in this translation unit. */
void initialize_dual_child_entries(S_800B4350_0 *owner);
void initialize_object_data_blocks_and_entries(Rec_func_800B3FB8_arg0 *object);
void set_record_base_and_data_pointer_alt(void *record_values, s32 base_value);
void initialize_entity_display_owner(u8 *owner, s32 base_value);

#endif
