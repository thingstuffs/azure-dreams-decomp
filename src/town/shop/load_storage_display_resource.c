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

s32 load_storage_display_resource(StorageWork *work, s32 resource) {
    s32 success = 0;
    s32 handle = realloc_field_0_buffer(&work->buffer, resource, 12);
    work->handle = handle;
    if (handle != 0) {
        work->vector.unk0 = display_vector_defaults.unk0;
        work->vector.unk4 = display_vector_defaults.unk4;
        work->vector.unk8 = display_vector_defaults.unk8;
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(handle, &work->vector, 24);
        success = 1;
    }
    return success;
}
