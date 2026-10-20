#include "common.h"

extern void call_the_handler_selects_nonzero_entry(void *entries, void *record, s32 handler_param);
extern void clear_entity_record_fields(s32 record);

extern u8 D_800834B8[];
extern u8 D_80097D2C[];
extern u8 D_8009ACFC[];
extern u8 D_800D0078[];
extern s32 D_800D0620;

/* Initializes the global object and resets its state pointers and flag. */
void initialize_global_player_object(void)
{
    void *object;
    void *object_header;
    s32 init_value;

    object = D_800834B8;
    object_header = (u8 *)object - 0x20;
    init_value = *(s32 *)((u8 *)object_header + 0xC);
    clear_entity_record_fields(*(s32 *)((u8 *)object_header + 8));
    call_the_handler_selects_nonzero_entry(D_800D0078, object, init_value);
    D_800D0620 = 0;
    *(void **)D_800834B8 = D_80097D2C;
    *(void **)((u8 *)object + 4) = D_8009ACFC;
}
