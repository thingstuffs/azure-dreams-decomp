#ifndef FRONTEND_LIBCARD_OCCUPIED_SLOT_WINDOW_G00386_H
#define FRONTEND_LIBCARD_OCCUPIED_SLOT_WINDOW_G00386_H
/* Occupied slot window; G00386; inferred-strong; CL/PD joins as listed below, no proven or weak cut crossed */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:main/func_800105A0, CL:main/func_80010B18, CL:main/func_80010C44, CL:main/func_80010D64. */

#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

#include "frontend/libcard/display_node.h"

extern void func_8004E5A0(void *a0, s32 a1, void *a2);
extern u8 D_80078FD0[16];
extern s16 D_80027F7C;
extern s16 D_800282B0;
extern void func_80023BE4(void *, s32, s32);

/* Functions defined in this translation unit. */
void card_boot_format_occupied_slot_window(void *slot_owner);
void card_boot_layout_alternate_slot_window(void *context);
void card_boot_populate_slot_window_display(s32 *state);

#endif
