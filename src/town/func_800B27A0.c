#include "common.h"

typedef struct S_800AFF00_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800AFF00_0;   /* arg1 in func_800AFF00 */

typedef struct S_800AFF00_1 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_800AFF00_1;   /* src1 in func_800AFF00 */

typedef struct S_800AFF00_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800AFF00_2;   /* arg2 in func_800AFF00 */

typedef struct S_800AFF00_3 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800AFF00_3;   /* src2 in func_800AFF00 */

typedef struct S_800AFF00_4 {
    s32 unk_00;
    void * unk_04;
    void * unk_08;
} S_800AFF00_4;   /* arg0 in func_800AFF00 */

typedef struct S_800AFF00_5 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AFF00_5;   /* dst in func_800AFF00 */

typedef struct S_800AFF00_6 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1];
    u8 unk_0F;
} S_800AFF00_6;   /* ((S_800AFF00_4 *)arg0)->unk_04 in func_800AFF00 */

typedef struct S_800AFF00_7 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800AFF00_7;   /* ((S_800AFF00_4 *)arg0)->unk_08 in func_800AFF00 */



extern s32 D_8002E5D8[4];
extern s32 D_8002E5E8[3];

/* Initialize two linked data blocks from templates and set their default fields. */
void func_800AFF00(S_800AFF00_4 *state, S_800AFF00_0 *primary, S_800AFF00_2 *secondary) {
    s32 *primary_defaults = D_8002E5D8;
    s32 *secondary_defaults = D_8002E5E8;
    s32 secondary_head;
    s32 initial_offset = -60;
    S_800AFF00_5 *primary_fields;

    primary->unk_00 = D_8002E5D8[0];
    primary->unk_04 = ((S_800AFF00_1 *)primary_defaults)->unk_04;
    primary->unk_08 = ((S_800AFF00_1 *)primary_defaults)->unk_08;
    secondary_head = D_8002E5E8[0];
    primary->unk_0C = ((S_800AFF00_1 *)primary_defaults)->unk_0C;
    secondary->unk_00 = secondary_head;
    secondary->unk_04 = ((S_800AFF00_3 *)secondary_defaults)->unk_04;
    secondary->unk_08 = ((S_800AFF00_3 *)secondary_defaults)->unk_08;
    state->unk_04 = primary;
    ASM_UNDEF(primary_fields);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    primary_fields = primary;
    ASM_KEEP(primary_fields);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    state->unk_08 = secondary;
    state->unk_00 = 0;
    primary_fields->unk_08 = initial_offset;
    ((S_800AFF00_6 *)(state->unk_04))->unk_0A = initial_offset;
    ((S_800AFF00_6 *)(state->unk_04))->unk_0C = 0x200;
    ((S_800AFF00_6 *)(state->unk_04))->unk_06 = 0;
    ((S_800AFF00_7 *)(state->unk_08))->unk_08 = 0x30;
    ((S_800AFF00_6 *)(state->unk_04))->unk_0F = 4;
}
