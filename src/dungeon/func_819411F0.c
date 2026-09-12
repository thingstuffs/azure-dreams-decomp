#include "common.h"
#include "m2c_compat.h"

typedef struct {
    s32 words[3];
} __attribute__((packed)) Packed12;

void *func_8003FC64();
M2C_UNK func_8004491C();
extern M2C_UNK D_800249A0;
extern M2C_UNK D_80045340;


typedef struct S_800249F0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800249F0_0;   /* temp_s0 in func_800249F0 */

typedef struct S_800249F0_1 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    volatile u16 unk_14;
} S_800249F0_1;   /* temp_a3 in func_800249F0 */

typedef struct S_800249F0_2_pre {
    void * unk_00;
    u8 pad_04[0x14];
} S_800249F0_2_pre;   /* the 0x18 bytes before arg0 in func_800249F0, addressed as arg0[-1] */

typedef struct S_800249F0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800249F0_3;   /* temp_a0 in func_800249F0 */

typedef struct S_800249F0_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800249F0_4;   /* temp_v1 in func_800249F0 */

typedef struct S_800249F0_5 {
    u8 pad_00[0x8];
    void * unk_08;
    s8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800249F0_5;   /* temp_a3_2 in func_800249F0 */

/* Create an object with copied position and packed data, and initialize its rendering state. */
void *func_800249F0(void *source, s32 unused_1, s32 unused_2, void *packed_data, s32 render_param, s32 render_x, s32 render_y, s32 render_mode) {
    u16 flags;
    u16 flags_copy;
    register s32 render_param_copy ASM_REG("$2");
    S_800249F0_3 *position;
    register void *render_state ASM_REG("$7");
    register void *render_data ASM_REG("$7");
    S_800249F0_0 *state;
    void *object;
    S_800249F0_4 *source_position;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        state->unk_2A = 0x3C;
        (*(M2C_UNK **)((u8 *)object + 0x10)) = &D_800249A0;
        func_8004491C(object, &D_80045340);
        render_state = (*(void **)((u8 *)object + 0xC));
        flags = ((S_800249F0_1 *)render_state)->unk_14 | 0xC;
        ((S_800249F0_1 *)render_state)->unk_14 = flags;
        ASM_CLOBBER("$3");
        flags_copy = flags;
        ASM_KEEP(flags_copy);
        render_param_copy = render_param;
        ((S_800249F0_1 *)render_state)->unk_14 = (u16) (flags_copy | 0x80);
        ASM_KEEP(render_param_copy);
        ((S_800249F0_1 *)render_state)->unk_10 = (s16) (render_param_copy << 5);
        source_position = ((S_800249F0_2_pre *)source)[-1].unk_00;
        position = (*(void **)((u8 *)object + 8));
        position->unk_00 = (s32) source_position->unk_00;
        position->unk_04 = (s32) source_position->unk_04;
        position->unk_08 = (s32) source_position->unk_08;
        render_data = (*(void **)((u8 *)object + 0xC));
        ((S_800249F0_5 *)render_data)->unk_1C = (s16) render_x;
        ((S_800249F0_5 *)render_data)->unk_1E = (s16) render_y;
        ((S_800249F0_5 *)render_data)->unk_0E = 0x80;
        ((S_800249F0_5 *)render_data)->unk_0D = 0x80;
        ((S_800249F0_5 *)render_data)->unk_0C = (s8) render_mode;
        (*(Packed12 *)((u8 *)object + 0x92)) = *(Packed12 *)packed_data;
        ((S_800249F0_5 *)render_data)->unk_08 = (void *) (object + 0x92);
        return state;
    } else {
        return NULL;
    }
}
