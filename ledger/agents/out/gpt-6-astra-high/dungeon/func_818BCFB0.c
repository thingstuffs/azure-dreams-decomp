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

/* Create an object, initialize its state, and copy data with a scaled component offset. */
s32 func_818BCFB0(s32 *initial_word, void *source_data, s16 offset)
{
    s32 offset_numerator;
    S_818BCFB0_3 *object_data;
    void *obj;
    void *scale_state;

    obj = func_8003FC64(0x212);
    if (obj != 0) {
        ((S_818BCFB0_0 *)obj)->unk_10 = D_80024088;
        func_8004491C(obj, D_800241CC);

        {
            S_818BCFB0_1 *init_state;
            s32 init_value;

            init_value = 0x7DCF;
            ((S_818BCFB0_0 *)obj)->unk_20 = *initial_word;
            init_state = (u8 *)obj + 0x20;
            init_state->unk_04 = 0;
            init_state->unk_06 = 0;
            init_state->unk_08 = 0;
            init_state->unk_0A = offset;
            init_state->unk_0C = init_value;
            init_state->unk_0E = 0;
        }

        scale_state = ((S_818BCFB0_0 *)obj)->unk_0C;
        ((S_818BCFB0_2 *)scale_state)->unk_1E = 0x1000;
        ((S_818BCFB0_2 *)scale_state)->unk_1C = 0x1000;

        object_data = ((S_818BCFB0_0 *)obj)->unk_08;
        offset_numerator = offset * 3;
        *(Copy24 *)object_data = *(Copy24 *)source_data;

        if (offset_numerator < 0) {
            offset_numerator += 3;
        }
        {
            register s32 object_addr ASM_REG("$2");   /* MATCH pin: retail basic-block layout depends on it */
            register s32 component ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
            register s32 component_offset ASM_REG("$4");   /* MATCH pin: retail register colouring depends on it */

            object_addr = (s32)obj;
            ASM_KEEP(object_addr);   /* MATCH pin: retail basic-block layout depends on it */
            component = object_data->unk_0A;
            component_offset = offset_numerator >> 2;
            component += component_offset;
            object_data->unk_0A = component;
            func_800248A0();
        }
    }
    return 0;
}
