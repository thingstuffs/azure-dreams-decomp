#include "common.h"

typedef struct S_818C32F4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818C32F4_0;   /* temp_v0 in func_818C32F4 */

typedef struct S_818C32F4_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
} S_818C32F4_1;   /* temp_v0_2 in func_818C32F4 */

typedef struct S_818C32F4_2 {
    u8 pad_00[0xC];
    union { struct { s32 v; } at00; struct { u8 v; } at00u; struct { u8 pad[0x1]; u8 v; } at01; struct { u8 pad[0x2]; u8 v; } at02; } unk_0C;   /* overlapping accesses */
    u16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x4];
    u16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
} S_818C32F4_2;   /* temp_s0 in func_818C32F4 */

typedef struct S_818C32F4_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xA];
    u16 unk_1A;
} S_818C32F4_3;   /* template_arg in func_818C32F4 */

typedef struct S_818C32F4_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C32F4_4;   /* arg1 in func_818C32F4 */

typedef struct S_818C32F4_5 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_818C32F4_5;   /* temp_v1 in func_818C32F4 */



extern void func_80024C28() __attribute__((noreturn));
extern s32 func_8003DB94();
extern void *func_8003FC64();
extern s32 func_8004491C();
extern u8 D_80024A08[9];
extern u8 D_80025B38[9];
extern u8 D_80045C34[9];

/* Creates an object with the supplied identifier, data, and visual template. */
s32 func_818C32F4(s32 *object_id, S_818C32F4_4 *source_data, void *visual_template) {
    S_818C32F4_3 *template_visual = visual_template;
    register s32 object_result ASM_REG("$2");   /* MATCH pin: retail keeps a computation the compiler would drop */
    s32 copy_word_0;
    s32 copy_word_1;
    s32 copy_word_2;
    s32 copy_word_3;
    u16 angle;
    void *init_data;
    S_818C32F4_2 *visual;
    void *object;
    S_818C32F4_1 *object_state;
    S_818C32F4_5 *object_data;

    object = func_8003FC64(0x212);
    ASM_KEEP(template_visual);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    if (object != 0) {
        ((S_818C32F4_0 *)object)->unk_10 = D_80024A08;
        ((S_818C32F4_0 *)object)->unk_20 = *object_id;
        object_state = (u8 *)object + 0x20;
        object_state->unk_04 = 0;
        object_state->unk_06 = 0;
        visual = ((S_818C32F4_0 *)object)->unk_0C;
        visual->unk_0C.at00.v = template_visual->unk_0C;
        if ((u8)visual->unk_0C.at00.v != 0) {
            visual->unk_0C.at00u.v = 0xC0;
        }
        if (visual->unk_0C.at01.v != 0) {
            visual->unk_0C.at01.v = 0xC0;
        }
        if (visual->unk_0C.at02.v != 0) {
            visual->unk_0C.at02.v = 0xC0;
        }
        visual->unk_14 = visual->unk_14 | 0xC;
        visual->unk_10 = visual->unk_10 | 0x60;
        func_8003DB94(visual, D_80025B38, 0);
        init_data = D_80045C34;
        angle = template_visual->unk_1A;
        visual->unk_1E = 0x1400;
        visual->unk_1C = 0x1400;
        visual->unk_1A = angle;
        func_8004491C(object, init_data);
        object_data = ((S_818C32F4_0 *)object)->unk_08;
        ASM_KEEP(object_data);   /* MATCH pin: keeps a statement from moving across a call/branch */
        object_result = (s32)object;
        ASM_KEEP(object_result);   /* MATCH pin: retail keeps a computation the compiler would drop */
        copy_word_0 = source_data->unk_00;
        copy_word_1 = source_data->unk_04;
        copy_word_2 = source_data->unk_08;
        copy_word_3 = source_data->unk_0C;
        object_data->unk_00 = copy_word_0;
        object_data->unk_04 = copy_word_1;
        object_data->unk_08 = copy_word_2;
        object_data->unk_0C = copy_word_3;
        copy_word_0 = source_data->unk_10;
        copy_word_1 = source_data->unk_14;
        object_data->unk_10 = copy_word_0;
        object_data->unk_14 = copy_word_1;
        func_80024C28(copy_word_0, copy_word_1, copy_word_2, copy_word_3);
    }
    return 0;
}
