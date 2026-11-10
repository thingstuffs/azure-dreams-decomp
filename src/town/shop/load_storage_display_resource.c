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
extern DisplayPositionWords display_vector_defaults;

s32 load_storage_display_resource(StorageWork *work, s32 resource) {
    s32 success = 0;
    ItemMenuPart **parts = (ItemMenuPart **)realloc_field_0_buffer(&work->buffer, resource, 12);
    work->parts = parts;
    if (parts != 0) {
        work->vector.unk0 = display_vector_defaults.unk0;
        work->vector.unk4 = display_vector_defaults.unk4;
        work->vector.unk8 = display_vector_defaults.unk8;
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(parts, &work->vector, 24);
        success = 1;
    }
    return success;
}
