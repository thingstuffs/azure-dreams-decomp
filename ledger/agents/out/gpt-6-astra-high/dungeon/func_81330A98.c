#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad[0x5A];
} PositionTableEntry;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_800DEDB0;
extern M2C_UNK D_800DEE38;
extern M2C_UNK D_80167A2C;
extern PositionTableEntry D_80175DD8[];

typedef struct S_80167A98_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80167A98_0;   /* temp_v0 in func_80167A98 */

typedef struct S_80167A98_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80167A98_1;   /* temp_s0 in func_80167A98 */

typedef struct S_80167A98_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167A98_2;   /* temp_a1 in func_80167A98 */

typedef struct S_80167A98_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167A98_3;   /* arg1 in func_80167A98 */

typedef struct S_80167A98_4 {
    u8 pad_00[0x1C];
    s16 unk_1C;
} S_80167A98_4;   /* arg0 in func_80167A98 */

/* Creates a visual object with a source-indexed position offset and appearance. */
void func_80167A98(S_80167A98_4 *source, S_80167A98_3 *origin) {
    S_80167A98_2 *position;
    S_80167A98_1 *render_state;
    S_80167A98_0 *object;

    object = func_8003FC64(0x212);
    if (object != NULL) {
        object->unk_10 = &D_80167A2C;
        func_8004491C(object, &D_80045340);
        render_state = object->unk_0C;
        render_state->unk_10 = 0x20;
        render_state->unk_06 = 0;
        render_state->unk_14 = (u16) (render_state->unk_14 | 0xC);
        position = object->unk_08;
        position->unk_00 = origin->unk_00 + (D_80175DD8[source->unk_1C].x << 0x11);
        position->unk_04 = origin->unk_04 + (D_80175DD8[source->unk_1C].y << 0x11);
        position->unk_08 = origin->unk_08 + (D_80175DD8[source->unk_1C].z << 0x11);
        render_state = object->unk_0C;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_0E = 0x80;
        render_state->unk_0D = 0x80;
        render_state->unk_0C = 0x80;
        if (source->unk_1C == 0) {
            func_8003DB94(render_state, &D_800DE870, 0);
        }
        if (source->unk_1C == 1) {
            func_8003DB94(render_state, &D_800DEE38, 0);
        }
        if (source->unk_1C == 2) {
            func_8003DB94(render_state, &D_800DEDB0, 0);
        }
    }
}
