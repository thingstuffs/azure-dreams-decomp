#include "common.h"





#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern u8 D_80409508[];
extern u8 D_80400548[];
extern u8 D_80400570[];
extern u8 D_8040861C[];
extern u8 D_80402F04[];
extern u16 D_80409526;
__asm__(".set D_80409526, 0x80409526");

s32 func_8003C714(s32, u8 *, s32);
s32 func_80040560(s32, u8 *);
s32 func_80047FD8(u8 *);
s32 func_8007BEF0(s32);
s32 func_8007BFE0(u8 *, s32);
s32 func_8007C040(u8 *, u8 *, s32);
void *func_80402DC8(u8 *);
s32 func_80402DF0(u8 *, s32);
void func_80402EBC(u8 *, s32, s32, s32, s32);
u8 *func_80403060(u8 *);
s32 func_8040343C(s32, u8 *);

typedef struct S_8001BF84_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
} S_8001BF84_0;   /* root in func_8001BF84 */

typedef struct S_8001BF84_1 {
    u8 pad_00[0x688];
    s32 unk_688;
} S_8001BF84_1;   /* store_base in func_8001BF84 */

/* Initializes or retrieves the memory card message object. */
u8 *func_8001BF84(s32 message_param_1, s32 message_param_2, s32 message_param_3, s32 message_param_4)
{
    s32 result;
    u8 *store_base;
    u8 *root = D_80409508;
    u8 *child = D_80409508 + 0x20;

    if (func_80047FD8(root) == 0) {
        result = func_8003C714(0, root, 0x1E1);
        if (result == 0) {
            func_8007C040(D_80400548, D_80400570, 0x299);
            func_8007BEF0(1);
        }
        func_80040560(result, D_8040861C);
        do {
            return func_80403060(child);
        } while (0);
    }

    func_8040343C(*(s32 *)0x80409534 != 2, root);
    D_80409526 &= 0x7FFF;
    func_8007BFE0(child, 0x764);
    func_80402DF0(child, 6);
    ((S_8001BF84_0 *)root)->unk_0C = (s32)(child + 0x67C);
    result = (s32)func_80402DC8(child + 0x68C);
    store_base = child;
    ((S_8001BF84_1 *)store_base)->unk_688 = result;
    func_80402EBC(store_base, message_param_1, message_param_2, message_param_3, message_param_4);
    ((S_8001BF84_0 *)root)->unk_10 = (s32)D_80402F04;
    return root;
}
