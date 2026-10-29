#include "town/shop.h"
#include "shared/object_flags.h"
#include "engine/item.h"
#include "engine/node.h"
#include "engine/resource.h"
#include "engine/text.h"
#include "engine/texture.h"
#include "engine/util.h"
#include "slus.h"
#include "town.h"
#include "town/person.h"
#include "town/shop/object.h"
#include "town/shop/state.h"
extern u8 shop_cursor_template[];
extern u8 D_80071244[];
extern void func_800B5020(void *work);
extern void forward_source_data_to_component(void *object);
extern void update_control_indicators_and_flags(void *object);
extern void forward_record_fields_to_page_loader(void *loader, void *object);
extern s32 display_block_defaults[4];
extern DisplayPositionWords display_vector_defaults;
extern int dungeon_menu_tag(void *forwarded_ptr, int unused_arg, void *second_ptr);
extern ItemMenuPart *func_800B4C94(ItemMenuPart **parts);

void initialize_storage_display_links(StorageDisplayLinks *state, StorageDisplayBlock *primary, StorageVector *secondary) {
    s32 *defaults = display_block_defaults;
    DisplayPositionWords *vector = &display_vector_defaults;
    s32 head;
    s32 offset = -60;
    primary->words[0] = display_block_defaults[0];
    primary->words[1] = defaults[1];
    primary->words[2] = defaults[2];
    head = display_vector_defaults.unk0;
    primary->words[3] = defaults[3];
    secondary->words.unk0 = head;
    secondary->words.unk4 = vector->unk4;
    secondary->words.unk8 = vector->unk8;
    state->display = &primary->display;
    state->position = secondary;
    state->unused = 0;
    state->display->x = offset;
    state->display->y = offset;
    state->display->depth = 0x228;
    state->display->ramp = 0;
    state->position->position.z = 0x30;
    state->display->mode = 4;
}
