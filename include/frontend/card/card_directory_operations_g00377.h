#ifndef FRONTEND_CARD_CARD_DIRECTORY_OPERATIONS_G00377_H
#define FRONTEND_CARD_CARD_DIRECTORY_OPERATIONS_G00377_H
/* Card directory operations; G00377; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_8000EA04, PD:main/image_25c800:80027F18, PD:main/image_25c800:80028570. */

#include "common.h"
#include "modules/main_server_ship.h"

typedef struct {
    s8 pad0[0x18];
    s32 field18;
    s8 pad1[0xC]; /* 0x28 total */
} func_8000E9B8_EntryT;

extern s32 firstfile2(void *, void *);
extern void *nextfile(void *);
extern void VSync(s32);
extern void format(s32);

/* Functions defined in this translation unit. */
s32 count_entries_matching_search_path(void);
s32 card_boot_calc_remaining_8k_blocks(s32 entry_count);
s32 card_boot_has_directory_name_prefix(s32 count, u8 *text);
s32 card_boot_format_card_and_wait(s32 card_slot);
void card_boot_build_slot_path(s32 dest, s32 suffix_index);

#endif
