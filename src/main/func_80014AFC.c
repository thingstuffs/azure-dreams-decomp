#include "common.h"

/* Linked-list node shape shared with func_8004B4A8/func_800403BC's Node/
 * S_80081498: next ptr @0x0, a pointer field @0x10, a 16-bit flags field
 * @0x1E. D_8002BB08 is accessed via %hi/%lo (not $gp), so declare it with
 * a size well past the -G8 small-data threshold. */
typedef struct Node8002BB08 {
    struct Node8002BB08 *next; /* 0x00 */
    u8 pad4[0x10 - 0x4];
    void *field_10;            /* 0x10 */
    u8 pad14[0x1E - 0x14];
    u16 field_1E;              /* 0x1E */
    u8 pad20[0x28 - 0x20];
} Node8002BB08;

extern Node8002BB08 D_8002BB08;

/* D_80082E60: shared global state struct; only the flags byte at offset 0xF
 * is touched here. Size >8B forces %hi/%lo. */
extern u8 D_80082E60[];

/* Address-only use; size clears the small-data threshold. */
extern u8 D_80027A9C[];

extern Node8002BB08 *func_8004B4A8(Node8002BB08 *a0);
extern Node8002BB08 *func_8003FE78(s32 a0, void *a1, s32 a2);
extern void func_80027C90(void *a0);
extern void bzero(void *a0, s32 a1);
extern void func_80027A68(void *a0, s32 a1, s32 a2);

Node8002BB08 *func_80027AFC(s32 arg0, s32 arg1) {
    Node8002BB08 *node = &D_8002BB08;
    void *temp = (u8 *)node + 0x20;

    if (func_8004B4A8(node) == 0) {
        node = func_8003FE78(0, node, 25);
    } else {
        func_80027C90(node);
        node->field_1E &= 0x7FFF;
        bzero(temp, 0x44);
    }
    D_80082E60[0xF] |= 0x80;
    func_80027A68(temp, arg0, arg1);
    node->field_10 = &D_80027A9C[0];
    return node;
}
