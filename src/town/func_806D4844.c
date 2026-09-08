#include "common.h"



typedef s32 M2C_UNK;

typedef struct S_80016844_2 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_80016844_2;   /* ((((S_80016844_1 *)(D_80016000[0]))->unk_08 * 8) +
                   ((S_80016844_1 *)(D_80016000[0]))->unk_40) in func_80016844 */

typedef struct S_80016844_3 {
    u8 pad_00[0x4];
    s8 unk_04;
} S_80016844_3;   /* ((((S_80016844_1 *)(D_80016000[0]))->unk_08 * 8) +
                       ((S_80016844_1 *)(D_80016000[0]))->unk_40) in func_80016844 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_800176B8();
extern M2C_UNK func_800177CC();
extern M2C_UNK func_80018594();
extern s32 func_8001868C();
extern void *D_80016000[];

typedef struct S_80016844_0 {
    u8 pad_00[0x18];
    s16 unk_18;
} S_80016844_0;   /* arg0 in func_80016844 */

typedef struct S_80016844_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x34];
    s32 unk_40;
} S_80016844_1;   /* D_80016000[0] in func_80016844 */

/* Runs the selected object handler and clears the current entry status. */
s32 func_80016844(S_80016844_0 *object, M2C_UNK context) {
    s32 result;

    result = 0;
    if (func_8001868C(0x1459) != 0) {
        func_80018594(object->unk_18);
        ((S_80016844_2 *)(((((S_80016844_1 *)(D_80016000[0]))->unk_08 * 8) +
                   ((S_80016844_1 *)(D_80016000[0]))->unk_40)))->unk_04 = 0;
        return func_800177CC(object, context);
    }
    if (func_8001868C(0x1458) != 0) {
        func_80018594(object->unk_18);
        result = func_800176B8(object, context);
        if (result != 0) {
            ((S_80016844_3 *)(((((S_80016844_1 *)(D_80016000[0]))->unk_08 * 8) +
                       ((S_80016844_1 *)(D_80016000[0]))->unk_40)))->unk_04 = 0;
        }
    }
    return result;
}
