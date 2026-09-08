#include "common.h"
#include "m2c_compat.h"

extern void *func_8003FC64(s32 a0);
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80046398;

typedef struct S_800BDBD0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_800BDBD0_0;   /* temp_v0 in func_800BDBD0 */

typedef struct S_800BDBD0_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800BDBD0_1;   /* temp_v1 in func_800BDBD0 */

typedef struct S_800BDBD0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDBD0_2;   /* temp_v1_2 in func_800BDBD0 */

typedef struct S_800BDBD0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BDBD0_3;   /* arg0 in func_800BDBD0 */

/* Creates an object at the supplied position and initializes its visual properties. */
void *func_800BDBD0(S_800BDBD0_3 *source_pos, s32 object_data, s32 angle, s32 visual_data) {
    S_800BDBD0_0 *object;
    S_800BDBD0_1 *visual;
    S_800BDBD0_2 *position;

    object = func_8003FC64(0x136);
    if (object != NULL) {
        func_8004491C(object, &D_80046398);
        visual = object->unk_0C;
        object->unk_10 = object_data;
        visual->unk_1A = (s16) angle;
        visual->unk_1C = 0x1000;
        visual->unk_1E = 0x1000;
        visual->unk_20 = 0x1000;
        visual->unk_0C = 0x808080;
        visual->unk_08 = visual_data;
        position = object->unk_08;
        position->unk_00 = source_pos->unk_00;
        position->unk_04 = source_pos->unk_04;
        position->unk_08 = source_pos->unk_08;
    }
    return object;
}
