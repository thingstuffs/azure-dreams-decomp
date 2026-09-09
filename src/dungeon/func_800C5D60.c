#include "common.h"
#include "m2c_compat.h"

typedef struct S_800CB4C0_6 {
    u8 pad_00[0x8];
    void * unk_08;
} S_800CB4C0_6;   /* arg0 in func_800CB4C0 */

typedef struct S_800CB4C0_7 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CB4C0_7;   /* ((S_800CB4C0_6 *)arg0)->unk_08 in func_800CB4C0 */




M2C_UNK func_8003DB94();  /* extern */
void *func_8003FD64();               /* extern */
M2C_UNK func_8004491C();           /* extern */
extern M2C_UNK D_80045340;
extern M2C_UNK D_800CB374;
extern M2C_UNK D_800E02CC;

typedef struct S_800CB4C0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800CB4C0_0;   /* temp_v0 in func_800CB4C0 */

typedef struct S_800CB4C0_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800CB4C0_1;   /* temp_s0 in func_800CB4C0 */

typedef struct S_800CB4C0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800CB4C0_2;   /* arg0 in func_800CB4C0 */

typedef struct S_800CB4C0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800CB4C0_3;   /* temp_v1 in func_800CB4C0 */

typedef struct S_800CB4C0_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
} S_800CB4C0_4;   /* temp_v0_3 in func_800CB4C0 */

typedef struct S_800CB4C0_5 {
    u8 pad_00[0x96];
    s16 unk_96;
    u8 pad_98[0x10];
    void * unk_A8;
    u8 pad_AC[0x8];
    s16 unk_B4;
} S_800CB4C0_5;   /* temp_v0_2 in func_800CB4C0 */

/* Creates an object with shared or copied source coordinates and initializes its display state. */
void *func_800CB4C0(void *source, s16 copy_position) {
    s32 display_value;
    S_800CB4C0_1 *display;
    void *object;
    S_800CB4C0_5 *state;
    S_800CB4C0_4 *source_display;
    S_800CB4C0_3 *position;

    object = func_8003FD64(0x100, source);
    if (object != NULL) {
        ((S_800CB4C0_0 *)object)->unk_10 = &D_800CB374;
        func_8004491C(object, &D_80045340);
        display = ((S_800CB4C0_0 *)object)->unk_0C;
        func_8003DB94(display, &D_800E02CC, 0);
        display->unk_1E = 0x1400;
        display->unk_1C = 0x1400;
        display->unk_10 = 0x20;
        display->unk_14 = (u16) (display->unk_14 | 0xC);
        if ((copy_position << 0x10) == 0) {
            ((S_800CB4C0_0 *)object)->unk_08 = ((S_800CB4C0_2 *)source)->unk_08;
        } else {
            position = ((S_800CB4C0_0 *)object)->unk_08;
            position->unk_02 = (u16) ((S_800CB4C0_7 *)(((S_800CB4C0_6 *)source)->unk_08))->unk_02;
            position->unk_06 = (u16) ((S_800CB4C0_7 *)(((S_800CB4C0_6 *)source)->unk_08))->unk_06;
            position->unk_0A = (u16) ((S_800CB4C0_7 *)(((S_800CB4C0_6 *)source)->unk_08))->unk_0A;
            source_display = ((S_800CB4C0_2 *)source)->unk_0C;
            display_value = source_display->unk_0C;
            display->unk_10 = 0x60;
            display->unk_0C = display_value;
        }

        display->unk_06 = -1;
        state = object + 0x20;
        state->unk_A8 = source;
        state->unk_B4 = copy_position;
        state->unk_96 = 8;
    }
    return object;
}
