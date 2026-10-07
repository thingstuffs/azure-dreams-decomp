#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Scale both position components by 64 and add the 0x220 offset. */
void func_80016E5C(void) {
    TownPositionState *first_position;
    TownPositionState *second_position;

    first_position = D_80016000->unk_1C;
    first_position->x = (s32) ((first_position->x << 6) + 0x220);
    second_position = D_80016000->unk_1C;
    second_position->y = (s32) ((second_position->y << 6) + 0x220);
}
