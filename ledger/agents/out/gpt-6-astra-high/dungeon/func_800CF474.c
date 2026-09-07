#include "common.h"

typedef struct S_800D4BD4_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x14];
    void * unk_24;
} S_800D4BD4_0;   /* state in func_800D4BD4 */

typedef struct S_800D4BD4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800D4BD4_1;   /* arg0 in func_800D4BD4 */

typedef struct S_800D4BD4_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
} S_800D4BD4_2;   /* temp_a0 in func_800D4BD4 */

typedef struct S_800D4BD4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D4BD4_3;   /* temp_v1 in func_800D4BD4 */

typedef struct S_800D4BD4_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800D4BD4_4;   /* arg2 in func_800D4BD4 */

typedef struct S_800D4BD4_5 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    s16 unk_12;
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800D4BD4_5;   /* temp_a0_2 in func_800D4BD4 */

typedef struct S_800D4BD4_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800D4BD4_6;   /* arg1 in func_800D4BD4 */



extern void func_8004491C(void *, void *);
extern void func_8003DB94(void *, void *, s32);
extern s32 D_80045340;
extern s32 D_800DECF8;

/* Initialize object state and rendering data from the source and position. */
void func_800D4BD4(void *object, S_800D4BD4_6 *source, S_800D4BD4_4 *position)
{
    S_800D4BD4_2 *render_config;
    S_800D4BD4_5 *render_data;
    S_800D4BD4_3 *object_position;
    S_800D4BD4_0 *state;
    s32 source_value;
    u16 flags;

    state = (u8 *)object + 0x20;
    state->unk_24 = source;
    func_8004491C(object, &D_80045340);
    render_config = ((S_800D4BD4_1 *)object)->unk_0C;
    render_config->unk_10 = 0x20;
    render_config->unk_14 = render_config->unk_14 | 0xC;
    object_position = ((S_800D4BD4_1 *)object)->unk_08;
    object_position->unk_02 = position->unk_02;
    object_position->unk_06 = position->unk_06;
    object_position->unk_0A = position->unk_0A;
    render_data = ((S_800D4BD4_1 *)object)->unk_0C;
    render_data->unk_1E = 0x800;
    render_data->unk_1C = 0x800;
    state->unk_0C = source->unk_0C;
    source_value = source->unk_0C;
    flags = render_data->unk_14;
    render_data->unk_12 = 0x7DCF;
    flags |= 0x100;
    render_data->unk_0C = source_value;
    render_data->unk_14 = flags;
    func_8003DB94(render_data, &D_800DECF8, 0);
}
