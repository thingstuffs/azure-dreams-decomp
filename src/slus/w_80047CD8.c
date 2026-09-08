#include "common.h"

extern void *func_80047A44(s32 a0);
extern s32 func_80047BC0(s32 arg0);
extern s32 func_80047C8C(s32 a0);
extern void func_80047C00(void);

/* Allocate an unregistered entity's slot, retrying after cleanup if needed; return NULL if already registered. */
void *func_80047CD8(s16 entity_index)
{
    s32 slot_index;
    s32 no_slot = -1;

    slot_index = func_80047BC0(entity_index);
    if (slot_index == no_slot) {
        slot_index = func_80047C8C(entity_index);
        if (slot_index == no_slot) {
            func_80047C00();
            slot_index = func_80047C8C(entity_index);
        }
        return func_80047A44(slot_index);
    }
    return 0;
}
