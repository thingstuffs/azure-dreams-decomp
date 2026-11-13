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
#include "town/shop/floating_number_widget_g00612.h"
extern DisplayPositionWords display_vector_defaults;

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
