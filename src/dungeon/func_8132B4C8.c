#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_80172CC8_0 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { volatile s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; u16 v; } at02; } unk_08;   /* overlapping accesses */
} S_80172CC8_0;   /* temp_v1 in func_80172CC8 */

typedef struct S_80172CC8_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_80172CC8_1;   /* arg0 in func_80172CC8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    u8 unk00[6];
    s16 field_06;
    u8 unk08[4];
    u8 field_0C;
    u8 field_0D;
    u8 field_0E;
    u8 unk0F;
    s16 field_10;
    u8 unk12[2];
    u16 flags_14;
    u8 unk16[6];
    s16 field_1C;
    s16 field_1E;
} Sub;

typedef struct {
    u8 unk00[8];
    void *position;
    Sub *sub;
    M2C_UNK *callback;
} Node;

M2C_UNK func_8003DB94();
Node *func_8003FC64();
M2C_UNK func_8004491C();

extern M2C_UNK D_80045340[3];
extern M2C_UNK D_800DE870[3];
extern M2C_UNK D_800DEDB0[3];
extern M2C_UNK D_80170D60[3];

void func_80172CC8(S_80172CC8_1 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Sub *temp_a0;
    Sub *temp_a0_2;
    Node *temp_v0;
    S_80172CC8_0 *temp_v1;
    s32 word_08;
    u16 x;
    u16 y;
    u16 z;
    register s32 flag ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    flag = arg4;
    temp_v0 = func_8003FC64(0x212);
    if (temp_v0 != 0) {
        temp_v0->callback = D_80170D60;
        func_8004491C(temp_v0, D_80045340);
        temp_a0 = temp_v0->sub;
        temp_a0->field_10 = 0x20;
        temp_a0->field_06 = 6;
        temp_a0->flags_14 |= 0xC;
        temp_v1 = temp_v0->position;
        temp_v1->unk_00.at00.v = arg0->unk_00;
        temp_v1->unk_04.at00.v = arg0->unk_04;
        x = temp_v1->unk_00.at02.v;
        word_08 = arg0->unk_08;
        temp_v1->unk_00.at02.v = (u16)(x + arg1);
        y = temp_v1->unk_04.at02.v;
        temp_v1->unk_08.at00.v = word_08;
        z = temp_v1->unk_08.at02.v;
        temp_v1->unk_04.at02.v = (u16)(y + arg2);
        temp_v1->unk_08.at02.v = (u16)(z + arg3);
        temp_a0_2 = temp_v0->sub;
        temp_a0_2->field_1E = 0x1400;
        temp_a0_2->field_1C = 0x1400;
        temp_a0_2->field_0E = 0x80;
        temp_a0_2->field_0D = 0x80;
        temp_a0_2->field_0C = 0x80;
        if ((flag << 0x10) == 0) {
            func_8003DB94(temp_a0_2, D_800DE870, 0);
        } else {
            func_8003DB94(temp_a0_2, D_800DEDB0, 0);
        }
        ASM_KEEP(flag);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    }
}
