/* Item menu display resource and its file-private helper. */
#include "common.h"
extern s32 func_80049004(s32 *a0, s32 a1, s32 a2);
extern s32 texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(s32 a0, void *a1, s32 a2);
extern s32 D_8002E5E8[];
#include "shared/object_flags.h"
typedef struct S_800AEFD8_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_800AEFD8_0;
/* object in create_item_menu_child_at_position */

typedef struct S_800AEFD8_1 {
    u8 pad_00[0xD4];
    void * unk_D4;
    void * unk_D8;
} S_800AEFD8_1;
/* payload in create_item_menu_child_at_position */

extern void *func_8003FD64(s32 value, void *parent);
static s32 load_item_menu_display_resource(void *payload, s32 value);
extern void *link_item_menu_display_entries(void *value);
extern void initialize_item_menu_list_display(void *payload, void *parent, s32 resource_id, s32 resource_data,
                          s32 x, s32 y, s32 context);
extern void func_8004491C(void *object, void *callback);
extern void func_8004B248(void *address);
extern void func_8004CAA0(void);
extern void advance_item_menu_object_animation(void);

static s32 load_item_menu_display_resource(void *object, s32 resource_id) {
    s32 success = 0;
    s32 handle = func_80049004((s32 *)((s8 *)object + 0xDC), resource_id, 8);

    *(s32 *)((s8 *)object + 0xD8) = handle;
    if (handle != 0) {
        *(s32 *)((s8 *)object + 0xBC) = D_8002E5E8[0];
        *(s32 *)((s8 *)object + 0xC0) = D_8002E5E8[1];
        *(s32 *)((s8 *)object + 0xC4) = D_8002E5E8[2];
        texture_set_the_field_offset_hex_8_in_each_entry_pointer_array(handle, (s8 *)object + 0xBC, 0x1A);
        success = 1;
    }
    return success;
}

void *create_item_menu_child_at_position(void *parent, s32 x, s32 y, s32 resource_id,
                    s32 resource_data, s32 context)
{
    void *object;
    S_800AEFD8_1 *payload;

    object = func_8003FD64(0, parent);
    if (object != 0) {
        payload = (u8 *)object + 0x20;
        if (load_item_menu_display_resource(payload, 0x1A) != 0) {
            ((S_800AEFD8_0 *)object)->unk_0C = (u8 *)object + 0xE8;
            payload->unk_D4 = link_item_menu_display_entries(payload->unk_D8);
            initialize_item_menu_list_display(payload, parent, resource_id, resource_data, x, y, context);
            func_8004491C(object, func_8004CAA0);
            ((S_800AEFD8_0 *)object)->unk_10 = advance_item_menu_object_animation;
        } else {
            func_8004B248((u8 *)object + 0xFC);
            ((S_800AEFD8_0 *)object)->unk_1E |= 0x8000;
            object_flag_block.flags |= 0x8000;
            object = 0;
        }
    }
    return object;
}
