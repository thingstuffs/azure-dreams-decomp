/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

void *func_800196A8(void *, s32);                /* extern */
extern s8 D_8001DCCC[];

typedef struct {
    s32 unk0;
    void *unk4;
    s32 *unk8;
    s8 *unkC;
} Func8032EEE4Record;

Func8032EEE4Record *func_800196E4(void *arg0, Func8032EEE4Record *arg1) {
    s32 temp_s1;
    s32 *temp_a0;
    Func8032EEE4Record *temp_v0;

    temp_s1 = arg1->unk0 & 0x3FFF0000;
    temp_v0 = (Func8032EEE4Record *) func_800196A8(arg0, temp_s1);
    if (temp_v0->unk4 == NULL) {
        s32 temp_v1;
        register s32 temp_v0_base ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
        temp_a0 = arg1->unk8;
        ASM_KEEP(temp_a0);   /* MATCH pin: retail schedule: same instructions, different order without it */
        temp_v1 = (s32) arg1->unkC;
        temp_v0_base = D_8001DCCC;
        temp_v1 = temp_v1 - temp_v0_base;
        temp_v1 = temp_v1 + 4;
        *temp_a0 = temp_v1;
        temp_v0_base = (s32) arg1->unk8;
        ASM_KEEP(temp_v0_base);   /* MATCH pin: retail basic-block layout depends on it */
        temp_v0->unk4 = (void *) temp_v0_base;
        temp_v0->unk0 = temp_s1;
        temp_v0->unkC = 0;
    }
    return temp_v0;
}
