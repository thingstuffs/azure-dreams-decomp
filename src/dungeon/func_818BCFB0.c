#include "common.h"

typedef struct S_818BCFB0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818BCFB0_0;   /* obj in func_818BCFB0 */

typedef struct S_818BCFB0_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    s8 unk_0E;
} S_818BCFB0_1;   /* init_state in func_818BCFB0 */

typedef struct S_818BCFB0_2 {
    u8 pad_00[0x1C];
    s16 unk_1C;
    s16 unk_1E;
} S_818BCFB0_2;   /* state in func_818BCFB0 */

typedef struct S_818BCFB0_3 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_818BCFB0_3;   /* temp_a3 in func_818BCFB0 */



typedef struct {
    s32 word[6];
} Copy24;

extern void func_800248A0(void) __attribute__((noreturn));
extern void *func_8003FC64();
extern s32 func_8004491C();
extern u8 D_80024088[];
extern u8 D_800241CC[];

s32 func_818BCFB0(s32 *arg0, void *arg1, s16 arg2)
{
    s32 var_a2;
    S_818BCFB0_3 *temp_a3;
    void *obj;
    void *state;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        ((S_818BCFB0_0 *)obj)->unk_10 = D_80024088;
        func_8004491C(obj, D_800241CC);

        {
            S_818BCFB0_1 *init_state;
            s32 init_value;

            init_value = 0x7DCF;
            ((S_818BCFB0_0 *)obj)->unk_20 = *arg0;
            init_state = (u8 *)obj + 0x20;
            init_state->unk_04 = 0;
            init_state->unk_06 = 0;
            init_state->unk_08 = 0;
            init_state->unk_0A = arg2;
            init_state->unk_0C = init_value;
            init_state->unk_0E = 0;
        }

        state = ((S_818BCFB0_0 *)obj)->unk_0C;
        ((S_818BCFB0_2 *)state)->unk_1E = 0x1000;
        ((S_818BCFB0_2 *)state)->unk_1C = 0x1000;

        temp_a3 = ((S_818BCFB0_0 *)obj)->unk_08;
        var_a2 = arg2 * 3;
        *(Copy24 *)temp_a3 = *(Copy24 *)arg1;

        if (var_a2 < 0) {
            var_a2 += 3;
        }
        {
            register s32 result ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
            register s32 field ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            register s32 scaled ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

            result = (s32)obj;
            ASM_KEEP(result);   /* MATCH pin: retail basic-block layout depends on it */
            field = temp_a3->unk_0A;
            scaled = var_a2 >> 2;
            field += scaled;
            temp_a3->unk_0A = field;
            func_800248A0();
        }
    }
    return 0;
}
