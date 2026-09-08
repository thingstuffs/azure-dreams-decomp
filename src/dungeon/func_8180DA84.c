#include "common.h"
#include "records/Rec_D_80082E80.h"

#ifndef NULL
#define NULL 0
#endif


typedef struct {
    s32 words[3];
} TableEntry;

extern s32 func_80026ED0();
extern s32 func_80027368();
extern s32 func_8003DE58();
extern void *func_8003FD64();
extern s32 func_8004491C();

extern s32 D_80026680[3];
extern TableEntry D_80028820[];
extern s32 D_80083498[3];
extern s32 D_800CEEFC[3];
extern u8 D_800DDC40[9];



typedef struct S_80026A84_1 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_80026A84_1;   /* temp_v0 in func_80026A84 */

typedef struct S_80026A84_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_80026A84_2;   /* arg0 in func_80026A84 */

typedef struct S_80026A84_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_80026A84_3;   /* temp_a2 in func_80026A84 */

typedef struct S_80026A84_4 {
    u8 pad_00[0x8];
    TableEntry * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026A84_4;   /* temp_a0 in func_80026A84 */

typedef struct S_80026A84_5 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    u8 pad_0C[0x5A];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
} S_80026A84_5;   /* temp_a3 in func_80026A84 */

typedef struct S_80026A84_6 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_80026A84_6;   /* var_a1 in func_80026A84 */

typedef struct S_80026A84_7 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80026A84_7;   /* arg1 in func_80026A84 */

void *func_80026A84(S_80026A84_2 *arg0, S_80026A84_7 *arg1, s32 arg2, Rec_D_80082E80 *arg3)
{
    u16 position[3];
    s32 *callback;
    TableEntry *var_s2;
    s32 var_s1;
    s32 var_t0;
    u16 temp_v0_2;
    u16 temp_v1;
    register void *temp_a0 ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    S_80026A84_3 *temp_a2;
    S_80026A84_5 *temp_a3;
    void *temp_v0;
    register void *var_a1 ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    void *var_s4;

    var_s4 = NULL;
    position[0] = position[1] = 0;
    if (func_8003DE58(arg3->unk_08, arg3, position, 0) == 0) {
        position[2] = (0 - D_800DDC40[0]) + 0x10;
    }
    callback = D_80026680;
    var_s1 = 0;
    do { var_s2 = D_80028820; } while (0);
    do {
        temp_v0 = func_8003FD64(0x12, D_80083498);
        if (temp_v0 != NULL) {
            ((S_80026A84_1 *)temp_v0)->unk_10 = callback;
            func_8004491C(temp_v0, D_800CEEFC);
            temp_a2 = ((S_80026A84_1 *)temp_v0)->unk_08;
            temp_v0_2 = arg0->unk_02 + position[0];
            temp_a2->unk_02 = temp_v0_2;
            temp_a2->unk_0E = temp_v0_2;
            var_t0 = 0;
            temp_v1 = arg0->unk_06 + position[1];
            temp_a2->unk_06 = temp_v1;
            temp_a2->unk_12 = temp_v1;
            temp_a3 = temp_v0 + 0x20;
            temp_v0_2 = arg0->unk_0A + position[2];
            temp_a2->unk_0A = temp_v0_2;
            temp_a2->unk_16 = temp_v0_2;
            temp_a0 = ((S_80026A84_1 *)temp_v0)->unk_0C;
            var_a1 = temp_a3;
            ((S_80026A84_4 *)temp_a0)->unk_1E = 0x1000;
            ((S_80026A84_4 *)temp_a0)->unk_1C = 0x1000;
            ((S_80026A84_4 *)temp_a0)->unk_08 = var_s2;
            ((S_80026A84_4 *)temp_a0)->unk_14 = ((S_80026A84_4 *)temp_a0)->unk_14 | 0xC;
            ((S_80026A84_1 *)temp_v0)->unk_20 = arg1;
            temp_a3->unk_04 = arg2;
            temp_a3->unk_66 = 0x20;
            temp_a3->unk_6E = var_s1;
            do {
                ((S_80026A84_6 *)var_a1)->unk_24 = temp_a2->unk_02;
                ((S_80026A84_6 *)var_a1)->unk_26 = temp_a2->unk_06;
                var_t0 += 1;
                ((S_80026A84_6 *)var_a1)->unk_28 = temp_a2->unk_0A;
                var_a1 += 8;
            } while (var_t0 < 8);
            temp_a3->unk_08 = var_s4;
            var_s4 = temp_v0;
        }
        var_s1 += 1;
        var_s2 += 1;
    } while (var_s1 < 6);
    func_80026ED0((s16)(arg0->unk_02 + position[0]),
                  (s16)(arg0->unk_06 + position[1]),
                  (s16)(arg0->unk_0A + position[2]), 0x800);
    func_80027368(arg1->unk_02, arg1->unk_06,
                  arg1->unk_0A, arg2);
    return temp_v0;
}
