#include "common.h"
#include "m2c_compat.h"

typedef struct S_800C4F6C_5 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800C4F6C_5;   /* arg0 in func_800C4F6C */

typedef struct S_800C4F6C_6 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_800C4F6C_6;   /* ((S_800C4F6C_5 *)arg0)->unk_80 in func_800C4F6C */


typedef struct S_800C4F6C_0 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800C4F6C_0;   /* arg1 in func_800C4F6C */

typedef struct S_800C4F6C_1 {
    M2C_UNK * unk_00;
} S_800C4F6C_1;   /* arg0 in func_800C4F6C; pointer addresses record offset 0x10 */

typedef struct S_800C4F6C_2 {
    u8 pad_00[0x10];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800C4F6C_2;   /* arg2 in func_800C4F6C */

typedef struct S_800C4F6C_3 {
    s32 unk_00;
} S_800C4F6C_3;   /* D_80083780 in func_800C4F6C */

typedef struct S_800C4F6C_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    s32 unk_08;
} S_800C4F6C_4;   /* temp_a1 in func_800C4F6C */


M2C_UNK func_800A47A8();                     /* extern */
M2C_UNK func_800A48B0();            /* extern */
M2C_UNK func_800C3050(); /* extern */
M2C_UNK func_800C5214();                      /* extern */
extern u8 D_80083780[];
extern M2C_UNK D_800C5064;
extern M2C_UNK D_800D50DC;
extern M2C_UNK D_800D50F0;
extern M2C_UNK D_800D50F8;
extern M2C_UNK D_800D5120;
extern M2C_UNK D_800D5124;
extern M2C_UNK D_80100D98;

/* Initialize object resources and display state, then copy its position to shared state. */
void func_800C4F6C(void *object, S_800C4F6C_0 *position, S_800C4F6C_2 *display_state) {
    s32 *shared_position;

    func_800C3050(object, 0x1D, &D_800D5120, &D_800D5124,
                 &D_800D50F0, &D_800D50F8);
    position->unk_08 = 0xFF800000;
    ((S_800C4F6C_6 *)(((S_800C4F6C_5 *)object)->unk_80))->unk_04 = &D_800D50DC;
    ((S_800C4F6C_1 *)((u8 *)object - 0x10))->unk_00 = &D_800C5064;
    display_state->unk_10 = 0;
    display_state->unk_14 = (u16) (display_state->unk_14 | 0xC);
    func_800C5214(object - 0x20);
    func_800A47A8(0);
    func_800A47A8(1);
    display_state->unk_1E = 0x800;
    display_state->unk_1C = 0x800;
    position->unk_04 = 0x04300000;
    ((S_800C4F6C_3 *)D_80083780)->unk_00 = position->unk_00;
    shared_position = (s32 *)D_80083780;
    ((S_800C4F6C_4 *)shared_position)->unk_04 = (s32) position->unk_04;
    ((S_800C4F6C_4 *)shared_position)->unk_08 = (s32) position->unk_08;
    func_800A48B0(&D_80100D98, shared_position);
}
