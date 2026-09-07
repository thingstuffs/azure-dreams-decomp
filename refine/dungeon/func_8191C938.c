#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) \
    (*(type_ptr)((u8 *)(expr) + (offset)))
#ifndef NULL
#define NULL 0
#endif

extern void func_8002426C() __attribute__((noreturn));
extern s32 func_8003DB94(void *, void *, s16);
extern void *func_8003FC64(u32);
extern s32 func_8004491C(void *, void *);
extern s32 rand(void);
extern u8 D_80024048[];
extern u8 D_80045340[];
extern u8 D_800DED70[];

typedef struct CopyBlock {
    s32 word[6];
} CopyBlock;

typedef struct S_8191C938_0 {
    u8 pad_00[0x8];
    CopyBlock * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_8191C938_0;   /* temp_v0 in func_8191C938 */

typedef struct S_8191C938_1 {
    u8 pad_00[0x4];
    s16 unk_04;
    s16 unk_06;
    s16 unk_08;
    s16 unk_0A;
} S_8191C938_1;   /* temp_s0 in func_8191C938 */

typedef struct S_8191C938_2 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x1];
    u16 unk_10;
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_8191C938_2;   /* temp_s0_2 in func_8191C938 */

typedef struct S_8191C938_3 {
    u8 pad_00[0x16];
    u16 unk_16;
    u8 pad_18[0x8];
    CopyBlock * unk_20;
} S_8191C938_3;   /* arg0 in func_8191C938 */

typedef struct S_8191C938_4 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8191C938_4;   /* temp_a0 in func_8191C938 */

/* Allocate and initialize an object with randomized state and data copied from its source. */
void *func_8191C938(S_8191C938_3 *source)
{
    s32 random_value;
    CopyBlock *object_block;
    S_8191C938_1 *state;
    S_8191C938_2 *render_data;
    void *object;
    CopyBlock *source_block;
    void *result;
    register u16 word_override;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        state = object + 0x20;
        ((S_8191C938_0 *)object)->unk_10 = D_80024048;
        ((S_8191C938_0 *)object)->unk_20 = source;
        state->unk_04 = 0;
        state->unk_06 = 6;
        random_value = rand();
        state->unk_08 = random_value % 0x1000;
        state->unk_0A = 0x10;
        render_data = ((S_8191C938_0 *)object)->unk_0C;
        render_data->unk_0D = 0x80;
        render_data->unk_0C = 0x80;
        render_data->unk_0E = 0;
        render_data->unk_12 = 0x7DCF;
        render_data->unk_14 |= 0xC;
        render_data->unk_10 |= 0x20;
        render_data->unk_14 |= 0x100;
        func_8003DB94(render_data, D_800DED70, 0);
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        func_8004491C(object, D_80045340);
        object_block = ((S_8191C938_0 *)object)->unk_08;
        source_block = source->unk_20;
        *object_block = *source_block;
        word_override = source->unk_16;
        ASM_KEEP(word_override);   /* MATCH pin: retail keeps a computation the compiler would drop */
        result = object;
        ASM_KEEP(result);   /* MATCH pin: retail keeps a computation the compiler would drop */
        ((S_8191C938_4 *)object_block)->unk_0A = word_override;
        func_8002426C(object_block);
        return object;
    }
    result = NULL;
    return result;
}
