#ifndef TOWN_PERSON_FOUR_SLOT_OBJECT_OWNER_G00628_H
#define TOWN_PERSON_FOUR_SLOT_OBJECT_OWNER_G00628_H
/* Four slot object owner (G00628). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@3755C, CL:town/func_800B7604, CL:town/func_800B771C. */

#include "common.h"
#include "m2c_compat.h"

typedef struct SlotB {
    s8 pad[8];
    s16 unk08;
} SlotB;

typedef struct SlotA {
    void *unk00;
    SlotB *unk04;
} SlotA;

typedef struct Obj {
    u8 pad20[0x20];
    void *unk20;
    u8 pad5c[0x38];
    SlotA **unk5c;
} Obj;

typedef struct S_800B4E7C_0 {
    s32 * unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_800B4E7C_0;

struct Obj;

extern u8 item_menu_slot_handler_address[];
extern void func_800B3558(void *);
extern void func_800B474C(void *);
extern void func_800B47BC(void *);
extern void initialize_storage_cursor(void *);
extern void func_800B4908(void *);
extern void func_800B49A8(void *);
extern void func_800B4A60(void *);
extern void update_storage_display(void *);
/* arg0 in set_record_value_and_data_pointer; pointer addresses record offset 0x10 */
/* cfail-repair: tf7-phase1-cache-v3 */
extern M2C_UNK D_800B4C38;
extern void initialize_storage_display_links();

/* Functions defined in this translation unit. */
void initialize_four_slot_object(Obj *obj);
void set_record_value_and_data_pointer(void *field_ptr, s32 base_value);
void initialize_four_slot_object_owner(u8 *owner, s32 base_value);

#endif
