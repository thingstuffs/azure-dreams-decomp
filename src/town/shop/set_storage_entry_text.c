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

void set_storage_entry_text(StorageEntry *entry, s32 text, s32 style, s16 x, s32 y) {
    void *old_text = entry->text;
    if (old_text != 0) {
        flag_object_for_removal(old_text);
        entry->text = 0;
    }
    entry->position->x = x;
    entry->position->y = y;
    entry->text = alloc_parsed_string(text, style);
    entry->position->mode = 1;
}
