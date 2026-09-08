#include "common.h"
#include "m2c_compat.h"

#define M2C_SYNC() 0

/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_80083350[5];
typedef struct {
    s16 unk0;
    u16 value;
    s16 unk4;
} D_800EA000_Record;
extern D_800EA000_Record D_800EA000[];

/* Returns the minimum signed value along a stepped sequence of grid records. */
s16 func_8001DD84(s32 x, s32 y, s32 count, s16 x_step, s16 y_step) {
    s32 remaining = count - 1;
    s16 row_shift = D_80083350[0];
    s16 row_step;
    u16 min_value;
    D_800EA000_Record *record;

    record = &D_800EA000[((y << row_shift) + x)];
    x += x_step;
    row_step = y_step;
    y += row_step;
    min_value = record->value;
    if (remaining > 0) {
        s16 loop_shift = row_shift;
        do {
            record = &D_800EA000[((y << loop_shift) + x)];
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
