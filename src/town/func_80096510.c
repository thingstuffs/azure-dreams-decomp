#include "common.h"

extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void clear_entity_record_fields(s32 record);

extern u8 D_800834B8[];
extern u8 D_8008FFC0[];
extern u8 D_80093D48[];
extern u8 D_800D0078[];
extern void *D_800FE5D8;

/* Processes the object's header values and updates the global pointers. */
void create_familiar_deployment_effect_with_owner_state(void) {
    void *object;
    void *object_header;
    s32 header_value;

    object = D_800834B8;
    object_header = (u8 *)object - 0x20;
    header_value = *(s32 *)((u8 *)object_header + 0xC);
    clear_entity_record_fields(*(s32 *)((u8 *)object_header + 8));
    call_the_handler_selects_nonzero_entry(D_800D0078, object, header_value);
    *(void **)D_800834B8 = D_8008FFC0;
    D_800FE5D8 = D_80093D48;
}
