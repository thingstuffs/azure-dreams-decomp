#include "modules/dungeon_ovl_191e87c.h"

s32 func_8002407C(Row_818FE800_Target *target, s32 level) {
    s32 random;
    s32 value;
    s32 aux;
    s32 half;
    s32 counter;
    s32 level_low;

    if (func_8009D218(target, 1) != 0) {
        return;
    }
    random = func_800A6D30() & 0xFFFF;
    if (target->field3 != 0) {
        counter = random % target->field3;
    } else {
        counter = 0;
    }
    level_low = level & 0xFF;
    if (counter < (level_low << 5) || level_low == 0xFF) {
        if (target->field26 >= 2) {
            half = ((s32)target->field26 + 1) >> 1;
            target->field26 -= half;
            value = func_800990FC();
            aux = value;
            value = func_8009929C(8, aux);
            value = func_80099734(target, value);
            value = func_80099194(&D_800E2096, value);
            func_80099290(value);
            func_800A5720(aux);
            func_800B4C7C(0x53, target, half, 1);
            return;
        }
    }
    func_80099844(target, &D_800E20BC);
    func_800B4C7C(0x53, target, -1, 1);
}
