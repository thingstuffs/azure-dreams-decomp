#include "common.h"
#include "m2c_compat.h"

typedef struct S_80098544_0 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
    u8 pad_08[0x2];
    union { u16 s; s16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x2A];
    s16 unk_36;
    s16 unk_38;
} S_80098544_0;   /* arg0 in func_80098544 */

typedef struct S_80098544_1 {
    s32 unk_00;
    s32 unk_04;
} S_80098544_1;   /* out in func_80098544 */


M2C_UNK func_80099754();
extern M2C_UNK D_800984AC;

void func_80098544(S_80098544_0 *arg0, void *arg1) {
    S_80098544_1 *out;   /* MATCH pin: load-bearing for the whole function shape */
    s16 remaining;
    register s32 temp_v1 ASM_REG("$3");   /* MATCH pin: keeps a statement from moving across a call/branch */
    u16 temp_v0;
    s32 temp_v2;

    out = arg1;
    ASM_KEEP(out);   /* MATCH pin: load-bearing for the whole function shape */
    temp_v0 = arg0->unk_0A.s - 1;
    arg0->unk_0A.s = temp_v0;
    if ((s16) temp_v0 > 0) {
        temp_v1 = out->unk_00;
        out->unk_00 = (s32) (temp_v1 + ((s32) ((arg0->unk_36 << 0x10) - temp_v1) / (s16) temp_v0));
        temp_v2 = arg0->unk_38;
        temp_v1 = out->unk_04;
        remaining = arg0->unk_0A.u;
        out->unk_04 = (s32) (temp_v1 + ((s32) ((temp_v2 << 0x10) - temp_v1) / remaining));
        return;
    }
    out->unk_00 = (s32) (arg0->unk_36 << 0x10);
    out->unk_04 = (s32) (arg0->unk_38 << 0x10);
    func_80099754(out);
    arg0->unk_04 = &D_800984AC;
}
