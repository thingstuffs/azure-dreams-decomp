#ifndef TOWN_EVENT_ITEM_QUERY_CHECKS_G01145_H
#define TOWN_EVENT_ITEM_QUERY_CHECKS_G01145_H
/* item query checks g01145. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01145 - CL:town/func_800AC118, CL:town/func_800AC164, CL:town/func_800AC198, CL:town/func_800AC210, CL:town/func_800AC278, CL:town/func_800AC2D8, CL:town/func_800AC37C, CL:town/func_800AC3CC (+1 more). */

/* inferred-strong G00588: item_query_checks_g00588; joins CL:town/func_800AC118,CL:town/func_800AC164,CL:town/func_800AC198,CL:town/func_800AC210,PD:town/engine:800D1054; no crossing cuts. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC118, CL:town/func_800AC164, CL:town/func_800AC198, CL:town/func_800AC210, PD:town/engine:800D1054. */
/* inferred-strong G00588: item_query_checks_g00588; shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800AC118, CL:town/func_800AC164, CL:town/func_800AC198, CL:town/func_800AC210, PD:town/engine:800D1054. */
#include "common.h"
#include "m2c_compat.h"
#include "engine/object/test_resident_bitmap_bit_api.h"                         /* extern */
#include "script_symbols.h"
#include "engine/object/test_resident_bitmap_bit_api.h"

#define FIELD_U8(p, off) (*(u8 *)((u8 *)(p) + (off)))
#ifndef NULL
#define NULL 0
#endif

typedef struct S_800A9C18_0 {
    u8 pad_00[0x35C4];
    u8 unk_35C4;
} S_800A9C18_0;

/* Singly-linked list node headed by D_80081498 (shared shape with
   func_80040418/remove_marked_active_nodes/find_active_list_node/mark_active_nodes_by_callback): next ptr @0x0,
   a 32-bit id/value field @0x10, and a 16-bit flags field @0x1E. */
typedef struct S_80081498 {
    struct S_80081498 *next; /* 0x00 */
    u8 pad4[0x10 - 0x4];
    s32 field_10;             /* 0x10 */
    u8 pad14[0x1E - 0x14];
    u16 field_1E;             /* 0x1E */
} S_80081498;

typedef struct S_800A9D00_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
} S_800A9D00_0;

typedef struct S_800A9D00_1 {
    u8 pad_00[0x2C];
    void * unk_2C;
} S_800A9D00_1;

/* base in retry_sound_for_linked_item_and_remove_carry_item */
typedef struct S_800A9D00_2 {
    u8 pad_00[0x4C];
    u16 unk_4C;
} S_800A9D00_2;

extern s16 D_800D1054[];
extern s16 D_800D1064[];
extern s32 get_item_sell_money(void *entry);
extern s8 D_800D1074[];
extern s32 D_800D1080[];
extern u8 D_8006BC7A;
extern s32 *D_800D1038[];
extern s32 map_scene_selector_alias;
extern struct {
    S_80081498 *head;
    int pad[2];
} active_node_list_head;
/* ((S_800A9D00_1 *)base)->unk_2C in retry_sound_for_linked_item_and_remove_carry_item */
extern s32 get_linked_carry_item_data();
extern s32 plt_carry_item_del_ext();
extern s32 retry_sound_sequence_when_ready();
extern s8 scene_object_payload_alias[0x30];
extern u8 D_8006C894[];
extern u8 D_8006C8F7[];
extern u8 D_8006C982[];
extern u8 D_8006C9E4[];
extern u8 D_800C25C0[];
extern u8 message_motion_type_a[];
extern u8 message_motion_type_b[];
extern void *D_80100E38[];

/* Functions defined in this translation unit. */
s32 find_sentinel_table_value_index(s32 target_value);
s32 test_selected_resident_flag(s32 table_index);
s32 get_query_result_for_check_type(s32 check_type);
s32 check_slot_threshold_or_fallback(s32 slot);
s32 classify_item_check_result(s32 input);
s32 classify_listed_entry_type(u8 *entry);
s32 filter_entry_by_kind(s32 unused, u8 *entry);
s32 get_group_record_table_entry(s32 group_id, void *record);
void initialize_actor_sprite_and_animation(s32 entry_index);
s32 is_expected_movie_state(void);
void test_resident_bit_11fa(void);
void test_resident_bit_11fb(void);
void *find_unflagged_node_by_key(s32 target_key);
void retry_sound_for_linked_item_and_remove_carry_item(void);
void *select_response_for_source_and_target(void *source, void *target);

#endif
