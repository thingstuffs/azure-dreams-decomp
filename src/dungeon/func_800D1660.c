#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800D6DC0_arg1.h"

/* cfail-repair: tf7-phase1-cache-v3 */
extern u8 D_80083498[];
extern s16 D_80083228[5];
void *func_8003FD64(s32, void *);       /* extern */
void func_8004491C(void *, void *, void *, void *); /* extern */
s32 func_800644B8(s32);                           /* extern */
s32 func_80064584(s32);                           /* extern */
void func_80047784(void *, u8, s32);              /* extern */
extern M2C_UNK D_800D67B0;
extern M2C_UNK D_800D6C18[2];
extern M2C_UNK D_800E23D8;

typedef struct {
    s32 w0;
    s32 w1;
    s32 w2;
    s32 w3;
} CopyQuad;

typedef struct {
    u8 pad[8];
    void *field8;
    void *fieldc;
    void *field10;
} AllocBlock;

typedef struct S_800D6DC0_0 {
    u8 pad_00[0xC];
    s16 unk_0C;
    s16 unk_0E;
    s16 unk_10;
    u8 pad_12[0x2];
    void * unk_14;
    u8 pad_18[0x2C];
    s16 unk_44;
    s16 unk_46;
    s16 unk_48;
    s16 unk_4A;
    s16 unk_4C;
    s16 unk_4E;
    s16 unk_50;
    s16 unk_52;
    s16 unk_54;
    s16 unk_56;
    s16 unk_58;
    s16 unk_5A;
} S_800D6DC0_0;   /* temp_s2 in func_800D6DC0 */

typedef struct S_800D6DC0_1 {
    u8 pad_00[0xC];
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
    u8 pad_20[0xC];
    M2C_UNK * unk_2C;
} S_800D6DC0_1;   /* temp_s3 in func_800D6DC0 */

typedef struct S_800D6DC0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0xA];
    s16 unk_16;
} S_800D6DC0_2;   /* temp_s0 in func_800D6DC0 */


typedef struct S_800D6DC0_4 {
    u8 pad_00[0x2A];
    s16 unk_2A;
} S_800D6DC0_4;   /* arg3 in func_800D6DC0 */

void func_800D6DC0(void *arg0, Rec_func_800D6DC0_arg1 *arg1, void *arg2, S_800D6DC0_4 *arg3) {
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_t0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 var_s5;
    s32 var_s4;
    S_800D6DC0_2 *temp_s0;
    S_800D6DC0_0 *temp_s2;
    S_800D6DC0_1 *temp_s3;
    void *temp_v0;
    void *var_a2;
    void *var_a3;
    u8 *page;
    s32 scale = 3;

    var_s4 = 0;
    page = (u8 *)&D_800E23D8;
    var_s5 = 0x200;
    do {
        temp_v0 = func_8003FD64(0x112, D_80083498);
        temp_s2 = temp_v0 + 0x20;
        if (temp_v0 != NULL) {
            var_a3 = arg2;
            temp_s2->unk_0C = 0x1E;
            temp_s2->unk_0E = 0x1E;
            temp_s2->unk_14 = arg1;
            temp_s2->unk_10 = var_s4;
            temp_s3 = ((AllocBlock *)temp_v0)->fieldc;
            ((AllocBlock *)temp_v0)->field10 = &D_800D6C18;
            temp_t0 = (s32)((u8 *)var_a3 + 0x30);
            var_a2 = temp_s3;
            do {
                *(CopyQuad *)var_a2 = *(CopyQuad *)var_a3;
                var_a3 += 0x10;
                var_a2 += 0x10;
            } while (var_a3 != (void *)temp_t0);
            temp_s3->unk_10 = 0x20;
            temp_s3->unk_14 = (u16) (temp_s3->unk_14 | 0xC);
            func_8004491C(temp_v0, &D_800D67B0, var_a2, var_a3);
            temp_s0 = ((AllocBlock *)temp_v0)->field8;
            temp_s0->unk_02 = (u16) arg1->unk_02;
            temp_s1 = var_s4 << 9;
            temp_s0->unk_06 = (u16) arg1->unk_06;
            temp_s0->unk_0A = (s16) (arg1->unk_0A + 0x28);
            temp_s3->unk_1E = 0x1000;
            temp_s3->unk_1C = 0x1000;
            temp_s3->unk_0E = 0xFA;
            temp_s3->unk_0D = 0xFA;
            temp_s3->unk_0C = 0xFA;
            temp_v0_2 = (s32) (scale * func_80064584(temp_s1)) >> 0xC;
            temp_s2->unk_48 = (s16) temp_v0_2;
            temp_s2->unk_44 = (s16) temp_v0_2;
            temp_v0_3 = (s32) (scale * func_80064584(var_s5)) >> 0xC;
            temp_s2->unk_4A = (s16) temp_v0_3;
            temp_s2->unk_46 = (s16) temp_v0_3;
            temp_v0_4 = (s32) (scale * func_800644B8(temp_s1)) >> 0xC;
            temp_s2->unk_50 = (s16) temp_v0_4;
            temp_s2->unk_4C = (s16) temp_v0_4;
            temp_lo = scale * func_800644B8(var_s5);
            temp_s2->unk_5A = 0;
            temp_s2->unk_58 = 0;
            temp_s2->unk_56 = 0;
            temp_s2->unk_54 = 0;
            temp_v0_5 = temp_lo >> 0xC;
            temp_s2->unk_52 = (s16) temp_v0_5;
            temp_s2->unk_4E = (s16) temp_v0_5;
            temp_s0->unk_16 = 0;
            temp_s3->unk_2C = page;
            func_80047784(temp_s3, *((u8 *) (((((s32) (*D_80083228 + arg3->unk_2A + 0x100) >> 9) & 7) + (s32) page))), 0);
        }
        var_s4 += 1;
        var_s5 += 0x200;
    } while (var_s4 < 8);
    return;
}
