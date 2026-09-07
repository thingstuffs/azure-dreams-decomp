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

s16 func_8001DD84(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4) {
    s32 var_a2 = arg2 - 1;
    s16 shift = D_80083350[0];
    s16 step;
    u16 var_t1;
    D_800EA000_Record *temp_t0;

    temp_t0 = &D_800EA000[((arg1 << shift) + arg0)];
    arg0 += arg3;
    step = arg4;
    arg1 += step;
    var_t1 = temp_t0->value;
    if (var_a2 > 0) {
        s16 loop_shift = shift;
        do {
            temp_t0 = &D_800EA000[((arg1 << loop_shift) + arg0)];
            if ((s16) temp_t0->value < (s16) var_t1) {
                var_t1 = temp_t0->value;
            }
            arg0 += arg3;
            var_a2 -= 1;
            arg1 += step;
        } while (var_a2 > 0);
    }
    return (s16) var_t1;
}
