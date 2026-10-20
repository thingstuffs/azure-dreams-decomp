#include "common.h"


typedef struct {
    s32 flag;
    u16 status;
    u16 pad6;
} S_80083D08;

extern S_80083D08 sprite_resource_slots[6];
extern void *D_80080A90;
extern s32 get_resource_block_index_from_address(void *a0);
extern void *func_80047AB0(void *a0, s32 a1, s32 a2, s32 a3, void *a4);
extern void *register_and_upload_three_slot_sprite_resource(s32 a0, void *a1);

/* Records an object's slot and type, with a separate handler for type 0x38. */
void *register_and_upload_sprite_resource(s32 object_type, void *object)
{
    void *lookup_object;
    void **resource_table;
    void **resources;
    s32 slot;
    s32 special_type = 0x38;

    if (object_type != special_type) {
        lookup_object = object;
        resource_table = &D_80080A90;
        resources = resource_table;
        slot = get_resource_block_index_from_address(lookup_object);
        (*(sprite_resource_slots + slot)).flag = (s32)object;
        (*(&sprite_resource_slots[slot])).pad6 = (u16)object_type;
        return func_80047AB0(object, slot + 5,
                             ((slot * 3) + 0x1D2) << 6,
                             0xD, resources[0]);
    }
    return register_and_upload_three_slot_sprite_resource(special_type, object);
}
