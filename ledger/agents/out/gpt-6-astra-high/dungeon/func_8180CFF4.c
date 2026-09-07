#include "common.h"

typedef struct {
    u8 unk0[0xC];
    s32 value;
} DungeonNode;

extern void func_800B8FC8(void *, u16 *, u16 *, s32, s32);

/* Processes both objects at adjacent coordinates with node values temporarily set to 0x808080. */
void func_80025FF4(void *left_object, void *right_object) {
    u16 coords[6];
    s32 x_offset;
    s32 width;
    DungeonNode *node;
    s32 saved_value;
    void *object;
    u8 *node_slot;
    s16 x;

    x_offset = 0x40;
    coords[1] = 0x100;
    width = x_offset;
    ASM_KEEP_NV(width);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    coords[2] = width;
    coords[3] = 0x80;
    coords[5] = 0x13C;
    do {
        x = x_offset + 0x340;
        coords[0] = x;
        x += (s16)coords[2] / 2;
        coords[4] = x;
        if (x_offset == 0) {
            node_slot = (u8 *)left_object - 0x14;
        } else {
            node_slot = (u8 *)right_object - 0x14;
        }
        node = *(DungeonNode **)node_slot;
        saved_value = node->value;
        node->value = 0x808080;
        object = right_object;
        if (x_offset == 0) {
            object = left_object;
        }
        func_800B8FC8(object, &coords[0], &coords[4], 1, 2);
        x_offset -= 0x40;
        node->value = saved_value;
    } while (x_offset >= 0);
}
