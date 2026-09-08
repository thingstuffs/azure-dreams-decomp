#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type, offset) (*(type)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8008F074();
extern M2C_UNK D_800C26C0[3];
extern M2C_UNK D_800D4F88[3];

typedef struct S_800C2664_0 {
    u8 pad_00[0x50];
    M2C_UNK * unk_50;
    u8 pad_54[0x38];
    s16 unk_8C;
    s16 unk_8E;
    u8 pad_90[0x4];
    u8 unk_94;
} S_800C2664_0;   /* arg0 in func_800C2664 */

/* Initialize the object values to 0x40, apply its indexed setup, and assign its table. */
void func_800C2664(S_800C2664_0 *object, M2C_UNK setup_context, M2C_UNK unused) {
    object->unk_8C = 0x40;
    object->unk_8E = 0x40;
    func_8008F074(object, setup_context, *(object->unk_94 + D_800D4F88));
    object->unk_50 = D_800C26C0;
}
