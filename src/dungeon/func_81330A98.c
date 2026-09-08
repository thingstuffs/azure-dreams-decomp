#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_80167A98_arg1.h"
#include "records/Rec_func_80167A98_arg0.h"

M2C_UNK func_8003DB94();  /* extern */
void *func_8003FC64();                       /* extern */
M2C_UNK func_8004491C();           /* extern */
typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad[0x5A];
} PositionTableEntry;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_800DEDB0;
extern M2C_UNK D_800DEE38;
extern M2C_UNK D_80167A2C;
extern PositionTableEntry D_80175DD8[];

typedef struct S_80167A98_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_80167A98_0;   /* temp_v0 in func_80167A98 */

typedef struct S_80167A98_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0x1];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80167A98_1;   /* temp_s0 in func_80167A98 */

typedef struct S_80167A98_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80167A98_2;   /* temp_a1 in func_80167A98 */



void func_80167A98(Rec_func_80167A98_arg0 *arg0, Rec_func_80167A98_arg1 *arg1) {
    S_80167A98_2 *temp_a1;
    S_80167A98_1 *temp_s0;
    S_80167A98_0 *temp_v0;

    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = &D_80167A2C;
        func_8004491C(temp_v0, &D_80045340);
        temp_s0 = temp_v0->unk_0C;
        temp_s0->unk_10 = 0x20;
        temp_s0->unk_06 = 0;
        temp_s0->unk_14 = (u16) (temp_s0->unk_14 | 0xC);
        temp_a1 = temp_v0->unk_08;
        temp_a1->unk_00 = arg1->unk_00 + (D_80175DD8[arg0->unk_1C].x << 0x11);
        temp_a1->unk_04 = arg1->unk_04 + (D_80175DD8[arg0->unk_1C].y << 0x11);
        temp_a1->unk_08 = arg1->unk_08 + (D_80175DD8[arg0->unk_1C].z << 0x11);
        temp_s0 = temp_v0->unk_0C;
        temp_s0->unk_1E = 0x1000;
        temp_s0->unk_1C = 0x1000;
        temp_s0->unk_0E = 0x80;
        temp_s0->unk_0D = 0x80;
        temp_s0->unk_0C = 0x80;
        if (arg0->unk_1C == 0) {
            func_8003DB94(temp_s0, &D_800DE870, 0);
        }
        if (arg0->unk_1C == 1) {
            func_8003DB94(temp_s0, &D_800DEE38, 0);
        }
        if (arg0->unk_1C == 2) {
            func_8003DB94(temp_s0, &D_800DEDB0, 0);
        }
    }
}
/* MECHANISM: One reassigned temp_s0 spans both object-load regions, naturally forcing
   retail's 0x28 frame and s0-s3 hold set. A 0x60 signed-halfword table restores the
   index/load sequence, and u8 fields preserve the 0x80 materialization. */
