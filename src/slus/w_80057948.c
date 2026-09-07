#include "common.h"

#include "common.h"

typedef struct {
    u8 pad00[6];
    u16 field06;
    u8 pad08[2];
    u16 field0A;
    u8 pad0C[0x1A - 0x0C];
    s16 field1A;
    u8 field1C;
    u8 field1D;
    u8 pad1E[0x78 - 0x1E];
} S_80085458;

extern s32 D_80073734[];
extern s32 D_80073740[];
extern S_80085458 D_80085458[];

extern s32 func_80056D44();
extern s32 func_8005E97C();

#ifdef NON_MATCHING
#define ACTIVE_COUNT D_80073734[0]
#else
#define ACTIVE_COUNT (*(s32 *)0x80073734)
#endif

void func_80057948(s32 arg0, s32 arg1) {
    S_80085458 *record;
    s32 *value;
    s32 current;
    s32 i;
    s32 masked1;
    register s32 accumulated ASM_REG("$18");   /* MATCH pin: slus-diff */
    s32 masked0;

    i = 0;
    accumulated = 0;
    if (ACTIVE_COUNT > 0) {
        masked0 = arg0 & 0xFF;
        masked1 = arg1 & 0xFF;
        value = D_80073740;
        record = D_80085458;
        do {
            if ((masked0 == record->field06) &&
                (masked1 == record->field0A)) {
                if (record->field1D == 0) {
                    func_80056D44(i, record);
                    current = *value;
                    accumulated |= current;
                    func_8005E97C(0, current);
                    record->field1A = 0;
                } else {
                    record->field1C |= 0x80;
                }
            }
            value++;
            record++;
        } while (++i < ACTIVE_COUNT);
    }
    if (accumulated != 0) {
        func_8005E97C(0, accumulated);
    }
}
