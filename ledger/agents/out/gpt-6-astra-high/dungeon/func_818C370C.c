#include "common.h"
typedef long long s64;



typedef s32 M2C_UNK;

typedef struct {
    s32 words[6];
} Copy24;

typedef struct {
    s32 words[4];
} Copy16;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define MULT_HI(a, b) (0)

extern s32 D_80045C34[3];
void func_80025078() __attribute__((noreturn));
void *func_8003FC64();
M2C_UNK func_8004491C();
s32 func_80069EF8();
extern M2C_UNK D_80024C48;
extern M2C_UNK D_80025AF0;

typedef struct S_818C370C_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_818C370C_0;   /* temp_v0 in func_818C370C */

typedef struct S_818C370C_1 {
    u8 pad_00[0xE];
    s16 unk_0E;
    s16 unk_10;
    s16 unk_12;
    u16 unk_14;
} S_818C370C_1;   /* temp_s2 in func_818C370C */

typedef struct S_818C370C_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_818C370C_2;   /* arg0 in func_818C370C */

typedef struct S_818C370C_3 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x4];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C370C_3;   /* temp_s0 in func_818C370C */

/* Creates an object with randomized state and initializes its rendering and data. */
s32 func_818C370C(S_818C370C_2 *owner, void *source_data) {
    s32 scale;
    s32 variant_random;
    s32 angle_random;
    s32 angle_value;
    s32 angle_quotient;
    s32 data_word4;
    s32 data_word5;
    char color_value;
    S_818C370C_3 *render_data;
    S_818C370C_1 *state;
    void *object;
    void *object_data;
    register s32 object_addr ASM_REG("$2");   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */

    object = func_8003FC64(0x212);
    if (object != 0) {
        state = object + 0x20;
        ((S_818C370C_0 *)object)->unk_10 = &D_80024C48;
        ((S_818C370C_0 *)object)->unk_20 = owner;
        state->unk_0E = 0;
        state->unk_10 = 0;
        variant_random = func_80069EF8();
        state->unk_12 = (s16)(variant_random % 7);
        color_value = 0x80;
        state->unk_14 = owner->unk_14;
        render_data = ((S_818C370C_0 *)object)->unk_0C;
        render_data->unk_0E = color_value;
        render_data->unk_0D = color_value;
        render_data->unk_0C = color_value;
        render_data->unk_12 = 0x7DCF;
        render_data->unk_14 = render_data->unk_14 | 0xC;
        render_data->unk_10 = render_data->unk_10 | 0x20;
        render_data->unk_14 = render_data->unk_14 | 0x100;
        func_8003DB94(render_data, &D_80025AF0, 0);
        angle_random = func_80069EF8();
        angle_value = angle_random;
        ASM_KEEP(angle_random);   /* MATCH pin: load-bearing for the whole function shape */
        angle_quotient = angle_random >> 0xC;
        if (angle_value < 0) {
            angle_quotient = (angle_value + 0xFFF) >> 0xC;
        }
        render_data->unk_1A = angle_value - (angle_quotient << 0xC);
        scale = 0x1400 / (s16)state->unk_14;
        render_data->unk_1E = scale;
        render_data->unk_1C = scale;
        func_8004491C(object, D_80045C34);
        object_data = ((S_818C370C_0 *)object)->unk_08;
        object_addr = (s32)object;
        *(Copy16 *)object_data = *(Copy16 *)source_data;
        ASM_KEEP(object_addr);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        data_word4 = ((Copy24 *)source_data)->words[4];
        data_word5 = ((Copy24 *)source_data)->words[5];
        ((Copy24 *)object_data)->words[4] = data_word4;
        ((Copy24 *)object_data)->words[5] = data_word5;
        func_80025078(data_word4, data_word5);
        return (s32)object;
    }
    return 0;
}
