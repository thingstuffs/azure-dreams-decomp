#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C52D0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800C52D0_6;   /* temp_a0 in func_800C52D0 */

typedef struct S_800C52D0_7 {
    u8 pad_00[0x3];
    s8 unk_03;
} S_800C52D0_7;   /* ((S_800C52D0_6 *)temp_a0)->unk_08 in func_800C52D0 */




extern const s32 D_800D5138;
extern s32 D_800D513C;

typedef struct S_800C52D0_0 {
    u8 pad_00[0x9C];
    void * unk_9C;
} S_800C52D0_0;   /* arg0 in func_800C52D0 */

typedef struct S_800C52D0_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800C52D0_1;   /* temp_v0 in func_800C52D0 */

typedef struct S_800C52D0_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800C52D0_2;   /* arg1 in func_800C52D0 */

typedef struct S_800C52D0_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800C52D0_3;   /* temp_a3 in func_800C52D0 */

typedef struct S_800C52D0_4 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800C52D0_4;   /* temp_a0 in func_800C52D0 */

typedef struct S_800C52D0_5 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_800C52D0_5;   /* arg2 in func_800C52D0 */

void func_800C52D0(S_800C52D0_0 *arg0, S_800C52D0_2 *arg1, S_800C52D0_5 *arg2) {
    s32 var_a0;
    S_800C52D0_4 *temp_a0;
    S_800C52D0_3 *temp_a3;
    S_800C52D0_1 *temp_v0;

    temp_v0 = arg0->unk_9C;
    temp_a3 = temp_v0->unk_08;
    temp_a0 = temp_v0->unk_0C;
    arg1->unk_04 = (s32) temp_a3->unk_04;
    arg1->unk_00 = (s32) (temp_a3->unk_00 + (temp_a0->unk_1C * D_800D5138));
    var_a0 = ((S_800C52D0_7 *)(((S_800C52D0_6 *)temp_a0)->unk_08))->unk_03 * temp_a0->unk_1E;
    if (var_a0 < 0) {
        var_a0 += 0xFFF;
    }
    arg1->unk_08 = (s32) (temp_a3->unk_08 + ((var_a0 >> 0xC) * D_800D513C));
    arg2->unk_1A = (u16) (arg2->unk_1A - 0x20);
}
/* MECHANISM: The function remains a frameless leaf with all ABI arguments in caller-saved registers.
   Declaring D_800D5138 const lets its lui/lw pair cross the first output store without a false alias.
   The signed-byte multiply, negative rounding branch, and halfword tail preserve retail widths and CFG. */
