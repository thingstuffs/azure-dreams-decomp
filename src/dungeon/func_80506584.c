/* Relink of matched dungeon/func_8028AD84; every changed retail word is a paired relocation. */
#include "modules/dungeon_floor_generate.h"

s16 func_8001DD84(s32 x, s32 y, s32 count, s16 x_step, s16 y_step) {
    s32 remaining = count - 1;
    s16 row_shift = gameWork.map.shiftX;
    s16 row_step;
    u16 min_value;
    floor_generate_isolated_8028AD84_D_800EA000_Record *record;

    record = &((floor_generate_isolated_8028AD84_D_800EA000_Record *)D_800EA000)[((y << row_shift) + x)];
    x += x_step;
    row_step = y_step;
    y += row_step;
    min_value = record->value;
    if (remaining > 0) {
        s16 loop_shift = row_shift;
        do {
            record = &((floor_generate_isolated_8028AD84_D_800EA000_Record *)D_800EA000)[((y << loop_shift) + x)];
            if ((s16) record->value < (s16) min_value) {
                min_value = record->value;
            }
            x += x_step;
            remaining -= 1;
            y += row_step;
        } while (remaining > 0);
    }
    return (s16) min_value;
}
