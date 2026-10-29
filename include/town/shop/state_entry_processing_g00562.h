#ifndef TOWN_SHOP_STATE_ENTRY_PROCESSING_G00562_H
#define TOWN_SHOP_STATE_ENTRY_PROCESSING_G00562_H
/* State entry processing declarations (G00562). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2608, CL:town/func_800A265C, CL:town/func_800A2724. */

#include "common.h"
#include "m2c_compat.h"

typedef struct S_80041E28_Dst S_80041E28_Dst;

typedef struct S_80041E28_Src S_80041E28_Src;

/* extern */
typedef struct S_800422DC_Other S_800422DC_Other;

typedef struct S_800422DC_Self S_800422DC_Self;

void restore_actor_stats_from_snapshot(S_80041E28_Dst *dst, S_80041E28_Src *src);
void build_entity_slot_snapshot(S_800422DC_Self *snapshot, S_800422DC_Other *source);
/* extern */
void reset_person_object_entries(void *);
/* extern */
extern s32 town_actor_scratch;
extern void set_resident_bitmap_bit(s32 bit_id);
extern s32 town_record_capacities[];
extern s16 paired_scene_flag_ids[];
extern void *town_item_list;

/* Functions defined in this translation unit. */
void load_a_shared_buffer_process_write_back(s32 record_ref);
void process_entries_in_state_n_19_triggers_associated_sounds(void);
void process_table_entries_referenced_objects_type_hex_13(void);
void process_state_entries_and_referenced_objects(void);

#endif
