#ifndef TOWN_SHOP_ENTRY_QUEUE_G00564_H
#define TOWN_SHOP_ENTRY_QUEUE_G00564_H
/* Entry queue declarations (G00564). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/func_800A2B1C, CL:town/func_800A2CA4, CL:town/func_800A2D54, PD:town/engine:80100AA0. */

#include "common.h"
#include "m2c_compat.h"

typedef union {
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
    } bytes;
    u32 word;
} TownRecord;

/* extern */
typedef struct S_800A0504_0 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0504_0;

s32 create_an_position_initializes_graphics_state();

extern TownRecord shop_record_queue[20];

/* Functions defined in this translation unit. */
void clear_entry_table(void);
void handle_inserts_first_free_slot_discarding_first_full(TownRecord *record);
s32 *get_address_global_80100_aa_0(void);
void handle_shift_entries_left_until_free_entry_limit_clear_tail(void);
void run_the_follow_up_action_has_eligible_type_passes_check(s32 check_value);

#endif
