#include "common.h"

extern void func_800B67A4(void *owner, void *instance_data, void *instance1, s32 x, s32 y_arg, s32 z_arg);
extern void clear_linked_entry_state(void *object);
extern void initialize_monster_status_state(void *record, s32 context, s32 type_id);

/* Initialize an object's position, internal links, and resource state. */
void initialize_entry_object(void *object, s32 entityId, s32 resourceIndex, s32 positionX, s32 positionY, s32 positionZ) {
    func_800B67A4((u8 *)object + 0x88, (u8 *)object + 0x60, (u8 *)object + 0x70, positionX, positionY, positionZ);
    clear_linked_entry_state(object);
    initialize_monster_status_state(object, entityId, resourceIndex);
}
