#include "common.h"

extern void func_800C46A8(void *object, s32 value, s32 update_value);
extern void initialize_object_entries(void *state, s32 output, void *entries);
extern u8 object_index_slots[][8];
extern s32 D_800C5FDC[];
extern s32 D_800D5590[];

/* Clears the object's table flag, updates the object, and installs D_800C5FDC. */
void install_update_after_flag_clear(void *object, s32 unusedArgument, s32 updateValue) {
    void *updateObject;
    s32 stagedUpdateValue;

    object_index_slots[*((s32 *)object + 0x18)][0] = 0;
    func_800C46A8(object, unusedArgument, updateValue);
    updateObject = object;
    stagedUpdateValue = updateValue;
    initialize_object_entries(updateObject, stagedUpdateValue, D_800D5590);
    *((s32 **)object + 0x15) = D_800C5FDC;
}
