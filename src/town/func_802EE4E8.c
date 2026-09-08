#include "common.h"



typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_80404EA0();
extern M2C_UNK func_804053A0();
extern void func_8040552C() __attribute__((noreturn));
extern u8 D_8009DDD8[];

typedef struct S_802EE4E8_0 {
    u8 pad_00[0x7C];
    s32 unk_7C;
} S_802EE4E8_0;   /* arg0 in func_802EE4E8 */

/* Select the exit or fallback path using the indexed table entry. */
void func_802EE4E8(S_802EE4E8_0 *object) {
    if (*(s32 *)(D_8009DDD8 + (object->unk_7C << 7)) != 0) {
        func_80404EA0();
        func_8040552C();
        return;
    }
    func_804053A0();
}
