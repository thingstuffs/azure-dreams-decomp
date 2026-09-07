#include "common.h"

typedef struct {
    s8 pad0[0x18];
    s32 field18;
    s8 pad1[0xC];
} Entry;

extern Entry D_80409290[];

s32 func_8001AA50(s32 arg0) {
    s32 sp0[2];
    register s32 i ASM_REG("$6");   /* a2 */
    register s32 sum ASM_REG("$3"); /* v1 */
    register Entry *p ASM_REG("$5"); /* a1 */
    register s32 t ASM_REG("$2");   /* v0 */
    register s32 val ASM_REG("$2");

    i = 0;
    ASM_KEEP(i);
    sum = 0;
    if (arg0 > 0) {
        p = D_80409290;
        do {
            val = p->field18;
            i += 1;
            sum += val;
            p += 1;
        } while (i < arg0);
    }
    t = sum;
    if (sum < 0) {
        t = sum + 0x1FFF;
    }
    return 0xF - (t >> 0xD);
}
