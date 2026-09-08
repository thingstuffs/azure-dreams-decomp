#include "common.h"

typedef struct S_8001CDA0_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_8001CDA0_3;   /* arg0 in func_8001CDA0 */

typedef struct S_8001CDA0_4 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
    s16 unk_0C;
    u8 pad_0E[0x1];
    s8 unk_0F;
} S_8001CDA0_4;   /* ((S_8001CDA0_3 *)arg0)->unk_04 in func_8001CDA0 */




#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 D_8002D690[];
extern s32 D_8002D694[];
extern s32 D_8002D698[];
extern s32 D_8002D69C[];
extern s32 D_8002D6A0[];
extern s32 D_8002D6A4[];
extern s32 D_8002D6A8[];

typedef struct S_8001CDA0_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_8001CDA0_0;   /* arg1 in func_8001CDA0 */

typedef struct S_8001CDA0_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8001CDA0_1;   /* arg2 in func_8001CDA0 */

typedef struct S_8001CDA0_2 {
    s32 unk_00;
    void * unk_04;
    void * unk_08;
} S_8001CDA0_2;   /* arg0 in func_8001CDA0 */

/* Initialize an entry from defaults and set its row position. */
void func_8001CDA0(S_8001CDA0_2 *entry, S_8001CDA0_0 *placement, S_8001CDA0_1 *settings, s32 row_index) {
    s32 settings_header;

    placement->unk_00 = D_8002D690[0];
    settings_header = D_8002D6A0[0];
    placement->unk_04 = D_8002D694[0];
    placement->unk_08 = D_8002D698[0];
    placement->unk_0C = D_8002D69C[0];
    settings->unk_00 = settings_header;
    settings->unk_04 = D_8002D6A4[0];
    settings->unk_08 = D_8002D6A8[0];
    entry->unk_04 = placement;
    entry->unk_08 = settings;
    entry->unk_00 = 0;
    ((S_8001CDA0_4 *)(((S_8001CDA0_3 *)entry)->unk_04))->unk_08 = -0xA0;
    ((S_8001CDA0_4 *)(((S_8001CDA0_3 *)entry)->unk_04))->unk_0A = (s16) ((row_index * 0x18) - 0x78);
    ((S_8001CDA0_4 *)(((S_8001CDA0_3 *)entry)->unk_04))->unk_0C = 0x200;
    ((S_8001CDA0_4 *)(((S_8001CDA0_3 *)entry)->unk_04))->unk_0F = 4;
}
