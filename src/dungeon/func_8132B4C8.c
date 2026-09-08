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

/* Creates a node at an offset from the origin and configures its display variant. */
void func_80172CC8(S_80172CC8_1 *origin, s32 x_offset, s32 y_offset, s32 z_offset, s32 variant) {
    Sub *setup_sub;
    Sub *display_sub;
    Node *node;
    S_80172CC8_0 *position;
    s32 origin_z;
    u16 x;
    u16 y;
    u16 z;
    register s32 variant_flag ASM_REG("$21");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

    variant_flag = variant;
    node = func_8003FC64(0x212);
    if (node != 0) {
        node->callback = D_80170D60;
        func_8004491C(node, D_80045340);
        setup_sub = node->sub;
        setup_sub->field_10 = 0x20;
        setup_sub->field_06 = 6;
        setup_sub->flags_14 |= 0xC;
        position = node->position;
        position->unk_00.at00.v = origin->unk_00;
        position->unk_04.at00.v = origin->unk_04;
        x = position->unk_00.at02.v;
        origin_z = origin->unk_08;
        position->unk_00.at02.v = (u16)(x + x_offset);
        y = position->unk_04.at02.v;
        position->unk_08.at00.v = origin_z;
        z = position->unk_08.at02.v;
        position->unk_04.at02.v = (u16)(y + y_offset);
        position->unk_08.at02.v = (u16)(z + z_offset);
        display_sub = node->sub;
        display_sub->field_1E = 0x1400;
        display_sub->field_1C = 0x1400;
        display_sub->field_0E = 0x80;
        display_sub->field_0D = 0x80;
        display_sub->field_0C = 0x80;
        if ((variant_flag << 0x10) == 0) {
            func_8003DB94(display_sub, D_800DE870, 0);
        } else {
            func_8003DB94(display_sub, D_800DEDB0, 0);
        }
        ASM_KEEP(variant_flag);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    }
}
