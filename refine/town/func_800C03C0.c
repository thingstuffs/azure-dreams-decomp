#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();    /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;

typedef struct S_800BDB20_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_800BDB20_0;   /* temp_v0 in func_800BDB20 */

typedef struct S_800BDB20_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDB20_1;   /* temp_v1 in func_800BDB20 */

typedef struct S_800BDB20_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDB20_2;   /* arg0 in func_800BDB20 */

typedef struct S_800BDB20_3 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_800BDB20_3;   /* temp_a0 in func_800BDB20 */

/* Creates an object at the given position and initializes its graphics. */
void *func_800BDB20(S_800BDB20_2 *position, s32 object_param, M2C_UNK graphics_id) {
    S_800BDB20_3 *render_data;
    S_800BDB20_0 *object;
    S_800BDB20_1 *object_pos;

    object = func_8003FC64(0x132);
    if (object != NULL) {
        func_8004491C(object, &D_80045340);
        render_data = object->unk_0C;
        object_pos = object->unk_08;
        object->unk_10 = object_param;
        object_pos->unk_00 = (s32) position->unk_00;
        object_pos->unk_04 = (s32) position->unk_04;
        object_pos->unk_08 = (s32) position->unk_08;
        render_data->unk_0C = 0x808080;
        render_data->unk_1E = 0x1000;
        render_data->unk_1C = 0x1000;
        func_8003DB94(render_data, graphics_id, 0);
    }
    return object;
}
