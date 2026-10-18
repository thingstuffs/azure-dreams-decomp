#include "modules/dungeon_ovl_197e800.h"
#include "common.h"




#ifndef NULL
#define NULL 0
#endif


extern s32 D_800273B0;
extern M2C_UNK D_800CEEFC;











/* Allocates and initializes objects at the supplied position across nine slots. */
void *allocate_nine_position_objects(void *position)
{
    S_81961A04_1 *source_pos;
    s32 slot;
    s32 *object_handler;
    s32 *control_handler;
    s32 last_slot;
    void *object;
    s16 slot_offset;
    s16 control_value;
    u16 control_scale;
    u16 pos_x;
    u16 pos_y;
    u16 pos_z;
    S_81961A04_4 *control;
    S_81961A04_3 *state;
    S_81961A04_2 *positions;

    source_pos = position;
    slot = 0;
    object_handler = interpolate_target_and_finish_transition;
    control_handler = &D_800273B0;
    last_slot = 8;
    do {
        object = func_8003FC64(2);
        if (object != NULL) {
            ((S_81961A04_0 *)object)->unk_10 = object_handler;
            func_8004491C(object, &D_800CEEFC);
            positions = ((S_81961A04_0 *)object)->unk_08;
            pos_x = source_pos->unk_02;
            state = object + 0x20;
            positions->unk_02 = pos_x;
            positions->unk_0E = pos_x;
            state->unk_38 = pos_x;
            pos_y = source_pos->unk_06;
            positions->unk_06 = pos_y;
            positions->unk_12 = pos_y;
            state->unk_3A = pos_y;
            pos_z = source_pos->unk_0A;
            positions->unk_0A = pos_z;
            positions->unk_16 = pos_z;
            state->unk_3C = pos_z;
            control = ((S_81961A04_0 *)object)->unk_0C;
            control->unk_08 = control_handler;
            if (slot != last_slot) {
                control->unk_1E = 0x200U;
            } else {
                control->unk_1E = 0x800U;
            }
            slot_offset = (last_slot - slot) * 4;
            control_value = -0x80 - slot_offset;
            control_scale = control->unk_1E;
            control->unk_0C = (s8)control_value;
            control->unk_1C = control_scale;
            state->unk_54 = slot;
            if (slot == last_slot) {
                state->unk_54 = 7;
            }
            state->unk_4C = last_slot;
        }
        slot += 1;
    } while (slot < 9);
    return object;
}
