#ifndef TOWN_PERSON_FOUR_SLOT_OBJECT_OWNER_G00628_H
#define TOWN_PERSON_FOUR_SLOT_OBJECT_OWNER_G00628_H
/* Four slot object owner. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@3755C, CL:town/func_800B7604, CL:town/func_800B771C. */

#include "common.h"
#include "m2c_compat.h"
#include "shared/item_menu.h"



typedef struct StorageDisplayBody {
    s32 unk00;
    u8 pad04[0xC];
    s32 unk10;
    u8 pad14[0xC];
    void *unk20;
    u8 pad24[0x1C];
    DisplayPositionWords vector;
    u8 pad4c[0x10];
    ItemMenuPart **parts;
    s32 unk60;
} StorageDisplayBody;


struct StorageDisplayBody;

extern u8 item_menu_slot_handler_address[];
extern void func_800B3558(void *);
extern void func_800B474C(void *);
extern void func_800B47BC(void *);
extern void func_800B4908(void *);
extern void func_800B49A8(void *);
extern void func_800B4A60(void *);
/* arg0 in set_record_value_and_data_pointer; pointer addresses record offset 0x10 */
extern M2C_UNK D_800B4C38;

/* Functions defined in this translation unit. */
void initialize_four_slot_object(StorageDisplayBody *obj);
void set_record_value_and_data_pointer(void *field_ptr, s32 base_value);
void initialize_four_slot_object_owner(u8 *owner, s32 base_value);

#endif
