#include "common.h"
#include "records/Rec_D_80016000.h"




typedef struct S_806F18F8_1 {
    u8 pad_00[0x1C];
    volatile void * unk_1C;
    void * unk_20;
} S_806F18F8_1;   /* state in func_806F18F8 */


typedef struct S_806F18F8_3 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_806F18F8_3;   /* ((S_806F18F8_1 *)state)->unk_1C in func_806F18F8 */

typedef struct S_806F18F8_4 {
    u8 pad_00[0x208];
    M2C_UNK (*unk_208)(M2C_UNK);
} S_806F18F8_4;   /* ((S_806F18F8_1 *)state)->unk_20 in func_806F18F8 */

typedef struct S_806F18F8_5 {
    u8 pad_00[0x20];
    void * unk_20;
} S_806F18F8_5;   /* ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v in func_806F18F8 */

typedef struct S_806F18F8_6 {
    u8 pad_00[0x228];
    M2C_UNK (*unk_228)(s32 *);
} S_806F18F8_6;   /* ((S_806F18F8_5 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20 in func_806F18F8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK D_80016000;


void func_806F18F8(void) {
    s32 record[6];
    S_806F18F8_1 *state;

    state = ((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v;
    record[0] = ((S_806F18F8_3 *)(state->unk_1C))->unk_04;
    record[1] = ((S_806F18F8_3 *)(state->unk_1C))->unk_04;
    record[2] = 0;
    ((S_806F18F8_4 *)(state->unk_20))->unk_208(0);
    ((S_806F18F8_6 *)(((S_806F18F8_5 *)(((Rec_D_80016000 *)(&D_80016000))->unk_00.at00_pv.v))->unk_20))->unk_228(record);
}

/* MECHANISM: The six-word sibling array forces the 0x30 frame; s0 holds D_80016000's high page.
   Reloading the bottom state from &D_80016000 itself avoids the seed's stray full-address addiu.
   That preserves the load-delay nop and places move a0,zero in the first jalr delay slot. */
