#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CBB68_0 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
} S_800CBB68_0;   /* temp_v0 in func_800CBB68 */

typedef struct S_800CBB68_1 {
    s32 unk_00;
    s32 unk_04;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_08;   /* overlapping accesses */
} S_800CBB68_1;   /* temp_s0 in func_800CBB68 */

typedef struct S_800CBB68_2 {
    u8 pad_00[0x96];
    s8 unk_96;
} S_800CBB68_2;   /* temp_s1 in func_800CBB68 */


extern void *func_8009C390();
extern s16 func_800C2AE8();
extern M2C_UNK func_800CBAE0();

void func_800CBB68(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_s2;
    S_800CBB68_1 *temp_s0;
    S_800CBB68_2 *temp_s1;
    void *temp_v0;

    temp_v0 = func_8009C390(0, 0, 0, 0);
    if (temp_v0 != NULL) {
        temp_s0 = ((S_800CBB68_0 *)temp_v0)->unk_08;
        temp_s2 = ((S_800CBB68_0 *)temp_v0)->unk_0C;
        temp_s1 = (s8 *)temp_v0 + 0x20;
        temp_s0->unk_00 = (s32)(arg1 << 0x10);
        temp_s0->unk_04 = (s32)(arg2 << 0x10);
        temp_s0->unk_08.at00.v = 0xFF000000;
        temp_s0->unk_08.at02.v = func_800C2AE8(temp_s0);
        temp_s1->unk_96 = arg0;
        func_800CBAE0(temp_s1, temp_s0, temp_s2);
    }
}
