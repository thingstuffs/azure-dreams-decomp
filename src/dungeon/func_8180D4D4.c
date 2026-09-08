#include "common.h"
#include "m2c_compat.h"

typedef struct S_800264D4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    void * unk_20;
} S_800264D4_0;   /* temp_v0 in func_800264D4 */

typedef struct S_800264D4_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800264D4_1;   /* arg0 in func_800264D4 */

typedef struct S_800264D4_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} S_800264D4_2;   /* temp_a1 in func_800264D4 */

typedef struct S_800264D4_3 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_800264D4_3;   /* temp_a0 in func_800264D4 */

typedef struct S_800264D4_4 {
    u8 pad_00[0x4];
    s32 unk_04;
    void * unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
    s32 unk_18;
    s32 unk_1C;
    s32 unk_20;
    u8 pad_24[0x42];
    s16 unk_66;
    u8 pad_68[0x6];
    s16 unk_6E;
    u8 pad_70[0x2];
    s16 unk_72;
} S_800264D4_4;   /* temp_a0_2 in func_800264D4 */

typedef struct S_800264D4_5 {
    u8 pad_00[0x24];
    u16 unk_24;
    u16 unk_26;
    u16 unk_28;
} S_800264D4_5;   /* var_v1 in func_800264D4 */


typedef struct {
    u8 unk00[8];
    void *addr;
    u8 unk0c[4];
    s16 unk10;
    s16 unk12;
    u16 flags;
    u8 unk16[6];
    s16 unk1c;
    s16 unk1e;
} NodeA;

extern u8 D_80083498[];
extern u8 D_80028808;
extern u8 D_800260DC[];
extern u8 D_800CEF54[];

void *func_8003FD64(s32, void *);
M2C_UNK func_8004491C(void *, void *);

void *func_800264D4(S_800264D4_1 *arg0, s32 arg1, s16 arg2, s16 arg3) {
    s32 var_s1;
    s32 index;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 var_a2;
    u16 temp_v0_2;
    u16 temp_v0_3;
    u16 temp_v0_4;
    register u16 temp_v0_8 ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    S_800264D4_3 *temp_a0;
    S_800264D4_4 *temp_a0_2;
    S_800264D4_2 *temp_a1;
    void *temp_v0;
    void *var_s4;
    void *var_v1;
    u8 *page_base;

    var_s4 = NULL;
    var_s1 = 0;
    page_base = &D_800260DC[0];
    index = (arg2 << 0x10) >> 16;
loop_1:
    temp_v0 = func_8003FD64(0x12, D_80083498);
    if (temp_v0 != NULL) {
        ((S_800264D4_0 *)temp_v0)->unk_10 = page_base;
        func_8004491C(temp_v0, &D_800CEF54);
        temp_a1 = ((S_800264D4_0 *)temp_v0)->unk_08;
        temp_v0_2 = arg0->unk_02;
        temp_a1->unk_00.at02.v = temp_v0_2;
        temp_a1->unk_0E = temp_v0_2;
        temp_v0_3 = arg0->unk_06;
        temp_a1->unk_04.at02.v = temp_v0_3;
        temp_a1->unk_12 = temp_v0_3;
        temp_v0_4 = arg0->unk_0A;
        temp_a1->unk_08.at02.v = temp_v0_4;
        temp_a1->unk_16 = temp_v0_4;
        temp_a0 = ((S_800264D4_0 *)temp_v0)->unk_0C;
        temp_v0_8 = temp_a0->unk_14;
        temp_a0->unk_08 = (void *) ((index * 0xC) + &D_80028808);
        temp_a0->unk_1E = 0x1000;
        temp_a0->unk_1C = 0x1000;
        temp_a0->unk_10 = 0x60;
        temp_a0->unk_14 = (u16) (temp_v0_8 | 0xC);
        temp_a0_2 = temp_v0 + 0x20;
        temp_a0_2->unk_04 = arg1;
        ((S_800264D4_0 *)temp_v0)->unk_20 = arg0;
        temp_a0_2->unk_66 = 0x20;
        temp_a0_2->unk_6E = var_s1;
        temp_v0_5 = temp_a1->unk_00.at00.v;
        temp_a0_2->unk_18 = temp_v0_5;
        temp_a0_2->unk_0C = temp_v0_5;
        temp_v0_6 = temp_a1->unk_04.at00.v;
        var_a2 = 0;
        temp_a0_2->unk_1C = temp_v0_6;
        temp_a0_2->unk_10 = temp_v0_6;
        var_v1 = temp_a0_2;
        temp_v0_7 = temp_a1->unk_08.at00.v;
        temp_a0_2->unk_20 = temp_v0_7;
        temp_a0_2->unk_14 = temp_v0_7;
        do {
            ((S_800264D4_5 *)var_v1)->unk_24 = (u16) temp_a1->unk_00.at02.v;
            ((S_800264D4_5 *)var_v1)->unk_26 = (u16) temp_a1->unk_04.at02.v;
            var_a2 += 1;
            ((S_800264D4_5 *)var_v1)->unk_28 = (u16) temp_a1->unk_08.at02.v;
            var_v1 += 8;
        } while (var_a2 < 8);
        temp_a0_2->unk_08 = var_s4;
        var_s4 = temp_v0;
        var_s1 += 1;
        temp_a0_2->unk_72 = arg3;
        if (var_s1 >= 6) {

        } else {
            goto loop_1;
        }
    }
    return temp_v0;
}
