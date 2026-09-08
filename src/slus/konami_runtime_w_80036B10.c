#include "common.h"

#include "common.h"
#include "records/Rec_D_80081FDC.h"
#include "records/Rec_func_80036210_arg0.h"

typedef struct S_80036B10_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    void (*unk_10)(void);
    u8 pad_14[0xC];
    void * unk_20;
} S_80036B10_0;   /* temp_v0 in func_80036B10 */

typedef struct S_80036B10_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    u8 pad_0C[0x38];
    s32 * unk_44;
    s8 unk_48;
    u8 pad_49[0x1];
    s16 unk_4A;
} S_80036B10_1;   /* temp_s1 in func_80036B10 */


typedef struct S_80036B10_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_80036B10_3;   /* temp_s6 in func_80036B10 */



typedef struct S_80036B10_4 {
    u8 pad_00[0x20];
    void * unk_20;
} S_80036B10_4;   /* temp_v0 in func_80036B10 */


typedef struct S_80036B10_6 {
    u8 pad_00[0x10];
    s32 unk_10;
    s32 unk_14;
} S_80036B10_6;   /* ((S_80036B10_4 *)temp_v0)->unk_20 in func_80036B10 */

typedef struct S_80036B10_7 {
    u8 pad_00[0x80];
    M2C_UNK * unk_80;
} S_80036B10_7;   /* ((Rec_func_80036210_arg0 *)arg2)->unk_74.as_pm in func_80036B10 */

typedef struct S_80036B10_8 {
    u8 pad_00[0x2];
    u8 unk_02;
} S_80036B10_8;   /* ((S_80036B10_7 *)(((Rec_func_80036210_arg0 *)arg2)->unk_74.as_pm))->unk_80 in func_80036B10 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80033C1C();
M2C_UNK func_800350B0();
void *func_8003FF2C();
M2C_UNK func_8004491C();
M2C_UNK func_8003DB94();
extern M2C_UNK D_8006A934;
extern M2C_UNK D_80073DC4;
extern M2C_UNK D_80082BC0;
extern void func_80033D54(void);
extern void func_80036C44(void);

/* Creates a task and initializes its source record, state, and rendering data. */
void func_80036B10(s32 task_arg, Rec_D_80081FDC *record, s32 *source, s16 state_value, s32 setup_arg) {
    S_80036B10_1 *state;
    S_80036B10_3 *render_data;
    void *task;
    s16 *variant_table;

    task = func_8003FF2C(0x11, task_arg, 0x49, &D_80082BC0);
    ((S_80036B10_0 *)task)->unk_10 = func_80036C44;
    func_8004491C(task, &func_80033D54);
    state = task + 0x20;
    render_data = ((S_80036B10_0 *)task)->unk_0C;
    state->unk_44 = source;
    state->unk_48 = 1;
    state->unk_4A = state_value;
    func_80033C1C(record, *source);
    ((S_80036B10_0 *)task)->unk_20 = record;
    record->unk_60 = 6;
    ((S_80036B10_6 *)(((S_80036B10_4 *)task)->unk_20))->unk_10 = 0x10C;
    variant_table = (s16 *)&D_8006A934;
    ((S_80036B10_6 *)(((S_80036B10_4 *)task)->unk_20))->unk_14 =
        variant_table[((S_80036B10_8 *)(((S_80036B10_7 *)(((Rec_func_80036210_arg0 *)source)->unk_74.as_pm))->unk_80))->unk_02];
    state->unk_04 = 0;
    state->unk_08 = 0;
    func_800350B0(setup_arg, state);
    render_data->unk_0C = 0x808080;
    func_8003DB94(render_data, &D_80073DC4, 0);
}
