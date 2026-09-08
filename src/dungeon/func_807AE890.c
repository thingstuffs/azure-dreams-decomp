#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80045340[];
extern u32 D_80083208[3];
extern u8 D_800DEAE0[];
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();                /* extern */
void func_8003DB94();                    /* extern */
s32 func_800BCB04();               /* extern */
extern M2C_UNK D_800F6070;

typedef struct S_800F6090_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800F6090_0;   /* temp_v0 in func_800F6090 */

typedef struct S_800F6090_1 {
    u8 pad_00[0xC];
    u32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    s16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800F6090_1;   /* temp_s0 in func_800F6090 */

typedef struct S_800F6090_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_800F6090_2;   /* temp_s0_2 in func_800F6090 */

/* Creates and initializes an object at the given coordinates with adjusted height. */
void func_800F6090(s16 x, s16 y) {
    S_800F6090_1 *render_state;
    S_800F6090_2 *position;
    S_800F6090_0 *object;
    u32 render_config;

    object = func_8003FC64(0x16);
    if (object != NULL) {
        object->unk_10 = &D_800F6070;
        func_8004491C(object, D_80045340);
        render_state = object->unk_0C;
        render_config = (u32) *D_80083208;
        render_state->unk_1E = 0x1000;
        render_state->unk_1C = 0x1000;
        render_state->unk_0C = render_config;
        func_8003DB94(render_state, D_800DEAE0, 0);
        render_state->unk_10 = 0x20;
        render_state->unk_14 = 0xC;
        position = object->unk_08;
        position->unk_02 = x;
        position->unk_06 = y;
        position->unk_0A = (s16) (func_800BCB04(x & 0xFFFF, y & 0xFFFF, -0x400) - 8);
    }
}
