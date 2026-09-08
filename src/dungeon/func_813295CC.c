#include "common.h"

typedef s32 M2C_UNK;

typedef struct {
    s32 x;
    s32 y;
    s32 z;
} Vec3;

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
    Vec3 *position;
    Sub *sub;
    M2C_UNK *callback;
} Node;

extern void func_8003DB94(Sub *, M2C_UNK *, s32);
extern Node *func_8003FC64(s32);
extern void func_8004491C(Node *, M2C_UNK *);
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;
extern M2C_UNK D_80170D60;

/* Creates and configures a node at a fixed offset from the given position. */
void func_80170DCC(void *unused, void *origin) {
    Node *node;
    Sub *node_sub;
    Vec3 *position;
    Sub *display_sub;

    node = func_8003FC64(0x212);
    if (node != 0) {
        node->callback = &D_80170D60;
        func_8004491C(node, &D_80045340);
        node_sub = node->sub;
        node_sub->field_10 = 0x20;
        node_sub->field_06 = 6;
        node_sub->flags_14 |= 0xC;
        position = node->position;
        position->x = ((Vec3 *)origin)->x + 0x180000;
        position->y = ((Vec3 *)origin)->y;
        position->z = ((Vec3 *)origin)->z + 0xFFF00000;
        display_sub = node->sub;
        display_sub->field_1E = 0x1400;
        display_sub->field_1C = 0x1400;
        display_sub->field_0E = 0x80;
        display_sub->field_0D = 0x80;
        display_sub->field_0C = 0x80;
        func_8003DB94(display_sub, &D_800DE870, 0);
    }
}
