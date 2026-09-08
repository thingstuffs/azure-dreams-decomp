#include "common.h"
#include "records/Rec_func_800B0C68_arg0.h"



typedef s32 M2C_UNK;


typedef struct S_800B1188_2 {
    u8 pad_00[0x10];
    void * unk_10;
    u8 pad_14[0x10];
    void * unk_24;
    u8 pad_28[0x10];
    void * unk_38;
    u8 pad_3C[0x10];
    void * unk_4C;
    u8 pad_50[0x10];
    void * unk_60;
} S_800B1188_2;   /* (temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32) in func_800B1188 */

typedef struct S_800B1188_3 {
    M2C_UNK ** unk_00;
    void ** unk_04;
    s32 unk_08;
    M2C_UNK ** unk_0C;
} S_800B1188_3;   /* ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv in func_800B1188 */

typedef struct S_800B1188_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_4;   /* ((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_10 in func_800B1188 */

typedef struct S_800B1188_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_5;   /* ((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_24 in func_800B1188 */

typedef struct S_800B1188_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_6;   /* ((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_38 in func_800B1188 */

typedef struct S_800B1188_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_7;   /* ((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_4C in func_800B1188 */

typedef struct S_800B1188_8 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_8;   /* ((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_60 in func_800B1188 */

typedef struct S_800B1188_9 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B1188_9;   /* ((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_04 in func_800B1188 */

typedef struct S_800B1188_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_10;   /* ((S_800B1188_4 *)(((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_10))->unk_04 in func_800B1188 */

typedef struct S_800B1188_11 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_11;   /* ((S_800B1188_5 *)(((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_24))->unk_04 in func_800B1188 */

typedef struct S_800B1188_12 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_12;   /* ((S_800B1188_6 *)(((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_38))->unk_04 in func_800B1188 */

typedef struct S_800B1188_13 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_13;   /* ((S_800B1188_7 *)(((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_4C))->unk_04 in func_800B1188 */

typedef struct S_800B1188_14 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B1188_14;   /* ((S_800B1188_8 *)(((S_800B1188_2 *)((temp_a0_2 + ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_s32)))->unk_60))->unk_04 in func_800B1188 */

typedef struct S_800B1188_15 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B1188_15;   /* ((S_800B1188_9 *)(((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_04))->unk_04 in func_800B1188 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8004CBFC();
extern M2C_UNK func_800B08D4();
extern M2C_UNK func_800B0C68();
extern M2C_UNK func_800B0D0C();
extern M2C_UNK func_800B0FD4();
extern M2C_UNK D_800788E0;
extern M2C_UNK D_800792DC;
extern M2C_UNK D_800D15F4;


/* Initialize UI resources and position five rows of display elements. */
void func_800B1188(void *ui) {
    s32 lower_y;
    s32 left_y;
    s32 right_y;
    s32 row_offset;
    s32 row;
    void *header;

    *((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_00 = &D_800788E0;
    header = ui + 0x34;
    *((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_04 = header;
    ((S_800B1188_15 *)(((S_800B1188_9 *)(((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_04))->unk_04))->unk_0A = 0x2F;
    func_800B08D4(header);
    func_800B0C68(ui);
    func_8004CBFC(ui + 0x28, &D_800792DC, ((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_08);
    row = 4;
    lower_y = 0xC8;
    right_y = 0x55;
    left_y = 0x58;
    *((S_800B1188_3 *)(((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_pv))->unk_0C = &D_800D15F4;
    do {
        row_offset = row * 4;
        ((S_800B1188_10 *)(((S_800B1188_4 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_10))->unk_04))->unk_08 = -0x50;
        ((S_800B1188_10 *)(((S_800B1188_4 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_10))->unk_04))->unk_0A = left_y;
        ((S_800B1188_11 *)(((S_800B1188_5 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_24))->unk_04))->unk_08 = 0x56;
        ((S_800B1188_11 *)(((S_800B1188_5 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_24))->unk_04))->unk_0A = right_y;
        ((S_800B1188_12 *)(((S_800B1188_6 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_38))->unk_04))->unk_08 = 0x3C;
        ((S_800B1188_12 *)(((S_800B1188_6 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_38))->unk_04))->unk_0A = lower_y;
        ((S_800B1188_13 *)(((S_800B1188_7 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_4C))->unk_04))->unk_08 = 0x8C;
        ((S_800B1188_13 *)(((S_800B1188_7 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_4C))->unk_04))->unk_0A = lower_y;
        ((S_800B1188_14 *)(((S_800B1188_8 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_60))->unk_04))->unk_08 = 0x34;
        row -= 1;
        left_y -= 0x10;
        right_y -= 0x10;
        ((S_800B1188_14 *)(((S_800B1188_8 *)(((S_800B1188_2 *)((row_offset + ((Rec_func_800B0C68_arg0 *)ui)->unk_CC.as_s32)))->unk_60))->unk_04))->unk_0A = lower_y;
        lower_y -= 0x10;
    } while (row >= 0);
    func_800B0D0C(ui, lower_y, row, left_y);
    func_800B0FD4(ui);
}
