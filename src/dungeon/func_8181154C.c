#include "modules/dungeon_ovl_1831370.h"

void clear_object_buffer_and_state(s32 objectAddress)
{
    ovl_1831370_8181154C_S_8002654C_0 *objectState;

    objectState = (void *)(objectAddress + 0x20);
    memset(objectState->unk_14, 0,
           (D_800294F8[objectState->unk_10] * 2) | 1);
    inventory_set_object_entry_address(objectState->unk_70, objectState->unk_14);
    objectState->unk_08 = 0;
    set_indexed_object_field(objectState->unk_70, 0);
}
