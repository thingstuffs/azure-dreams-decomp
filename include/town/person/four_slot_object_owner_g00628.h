#ifndef TOWN_PERSON_FOUR_SLOT_OBJECT_OWNER_G00628_H
#define TOWN_PERSON_FOUR_SLOT_OBJECT_OWNER_G00628_H
/* Four slot object owner. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:town/engine@3755C, CL:town/func_800B7604, CL:town/func_800B771C. */

#include "common.h"
#include "town/shop/storage_menu.h"
#include "shared/item_menu.h"



typedef struct StorageDisplayBody {
    s32 unk00;
    u8 pad04[4];
    s32 open_step;
    u8 pad0c[4];
    s32 unk10;
    FrameState cursor;
    void *unk20;
    u8 pad24[0x1C];
    DisplayPositionWords vector;
    StorageDisplayLinks links;
    u8 pad58[4];
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
void advance_storage_open_ramp(StorageDisplayBody *object);

/* Functions defined in this translation unit. */
void update_storage_cursor_and_fade_indicators(StorageDisplayBody *object);
void initialize_four_slot_object(StorageMenuObject *obj);
void bind_storage_display_object(StorageMenuObject *object, ObjectNodeHeader *owner);
void initialize_four_slot_object_owner(StorageMenuObject *object, ObjectNodeHeader *owner);

#endif
