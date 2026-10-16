#include "modules/dungeon_ovl_7f469800_p01.h"

/* Update position and part state, then mark the object used unless its part is exempt. */
void func_80171A38(void *object, T_80171A38_S_80171A38_4 *position, T_80171A38_S_80171A38_3 *part_state)
{
    T_80171A38_S_80171A38_1 *record;
    T_80171A38_S_80171A38_2 *part;
    T_80171A38_S_80171A38_5 *base_position;
    u16 part_value;
    T_80171A38_Vec3s position_delta;

    record = (u8 *)((T_80171A38_S_80171A38_0 *)object)->unk_20 - 0x20;
    if ((record->unk_1E & 0x8000) == 0) {
        part = record->unk_0C;
        part_value = part->unk_06;
        base_position = record->unk_08;
        part_state->unk_06 = part_value + 1;

        if (part->unk_04 == 0) {
            part_state->unk_1E = 0x400;
            part_state->unk_1C = 0x400;
        }
        if (part->unk_04 == 1) {
            part_state->unk_1E = 0x700;
            part_state->unk_1C = 0x700;
        }
        if (part->unk_04 == 2) {
            part_state->unk_1E = 0xa00;
            part_state->unk_1C = 0xa00;
        }
        if (part->unk_04 == 3) {
            part_state->unk_1E = 0x700;
            part_state->unk_1C = 0x700;
        }
        if (part->unk_04 == 4) {
            part_state->unk_1E = 0x400;
            part_state->unk_1C = 0x400;
        }

        position->unk_02 = base_position->unk_02;
        position->unk_06 = base_position->unk_06;
        position->unk_0A = base_position->unk_0A;

        if (func_8003DE58(
                ((T_80171A38_S_80171A38_6 *)(record->unk_0C))->unk_08,
                record->unk_0C, &position_delta, 0) != 0) {
            position->unk_02 += position_delta.x;
            position->unk_06 += position_delta.y;
            position->unk_0A += position_delta.z;
        }

        if (part->unk_2C == D_80175E54 ||
            part->unk_2C == D_80175E5C ||
            part->unk_2C == D_80175E64) {
            return;
        }
    }

    ((T_80171A38_S_80171A38_0_pre *)object)[-1].unk_00 |= 0x8000;
    objectFlagBlock.flags |= 0x8000;
}
