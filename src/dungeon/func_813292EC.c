#include "common.h"

typedef struct Node {
    u8 pad0[8];
    void *part8;
    void *partC;
    void *data10;
} Node;

extern Node *func_8003FC64(s32);
extern void func_8004491C(Node *, void *);
extern void func_8003DB94(void *, void *, s32);

extern u8 D_80045340[9];
extern u32 D_80083780[3];
extern u8 D_800DE870[9];
extern u8 D_80170A54[9];

/* Allocate and initialize an effect node with default parameters and data. */
void func_80170AEC(void)
{
    Node *node;
    s16 *node_params;
    s16 *effect;
    u32 *part_words;
    u32 *initial_words;
    register void *effect_part ASM_REG("$4");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    node = func_8003FC64(0x212);
    if (node != 0) {
        node_params = (s16 *)((u8 *)node + 0x20);
        node_params[11] = 0x1E;
        node_params[12] = 0x1E;
        node->data10 = D_80170A54;
        func_8004491C(node, D_80045340);

        effect_part = node->partC;
        *(s16 *)((u8 *)effect_part + 6) = 0;
        part_words = (u32 *)node->part8;
        initial_words = D_80083780;
        part_words[0] = initial_words[0];
        part_words[1] = initial_words[1];
        part_words[2] = initial_words[2];

        effect = (s16 *)node->partC;
        effect[15] = 0x1000;
        effect[14] = 0x1000;
        ((u8 *)effect)[14] = 0;
        ((u8 *)effect)[13] = 0;
        ((u8 *)effect)[12] = 0;
        effect[10] |= 0x80;
        func_8003DB94(effect, D_800DE870, 0);
    }
}

/* MECHANISM: Node * stays live in s0, inducing the retail 0x18 frame and sole
   s0 save; separate node_params/effect locals encode retail's disjoint v1/a0 lives.
   Exact sh/sb/lhu widths and the three-word global copy preserve body shape. */
