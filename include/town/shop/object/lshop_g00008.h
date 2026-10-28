#ifndef TOWN_SHOP_OBJECT_LSHOP_G00008_H
#define TOWN_SHOP_OBJECT_LSHOP_G00008_H
/* Lshop. Shared declarations. */
/* Original-file evidence: proven (string literals) - group G00008 - J1:town/image_2ab800#g0176, J1:town/image_3ef000#g0101, J1:town/ll34_400000_80016000#g0030, J1:town/ll34_51e000_80016000#g0057, J1:town/ll34_581000_80016000#g0013, J1:town/ll34_594800_80016000#g0051, J1:town/ll34_5ff000_80016000#g0033, J1:town/ll34_617000_80016000#g0038 (+2 more). */

#include "common.h"
#include "shared/town_root.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"

typedef void (*TownCall3)(void *, void *, s32);

typedef void (*TownCall1)(s32);

typedef struct S_80018D14_0 {
    u8 pad_00[0x6000];
    u8 * unk_6000;
} S_80018D14_0;

typedef void TownFatal1(s32) __attribute__((noreturn));

typedef struct Copy4 {
    u8 bytes[4];
} Copy4;

extern u8 D_8001605C[];
extern void clear_bytes(s8 *buffer, s32 length);

/* Shared import declarations; data casts preserve each measured view. */
extern u8 D_80016034[16];

/* Functions defined in this translation unit. */
void clear_shop_object_and_link(u8 *object_ref);
void release_lshop_entry(s32 slotIndex);
void compact_lshop_entry_list(void);
void *find_unused_item_slot(void **slot_list);
void append_town_item(const Copy4 *input);

void func_80018BE4(s32 slot_index);
void func_80018C58(void);

#endif
