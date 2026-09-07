#include "common.h"

typedef struct S_8001ADF8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001ADF8_2;   /* ((arg1 * 0x10) + arg0->unk_10) in func_8001ADF8 */


typedef struct S_8001ADF8_0 {
    u8 pad_00[0x3];
    u8 unk_03;
    u8 pad_04[0x1];
    u8 unk_05;
} S_8001ADF8_0;   /* D_8001E950 in func_8001ADF8 */

typedef struct S_8001ADF8_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001ADF8_1;   /* arg0 in func_8001ADF8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001A6D0();
extern s32 func_8001AE4C();
extern S_8001ADF8_0 *D_8001E950;

s32 func_8001ADF8(S_8001ADF8_1 *arg0, s32 arg1) {
    if (D_8001E950->unk_05 == 7) {
        ((S_8001ADF8_2 *)(((arg1 * 0x10) + arg0->unk_10)))->unk_08 =
            func_8001A6D0(D_8001E950->unk_03);
        return 0;
    }
    func_8001AE4C(D_8001E950);
    return 1;
}
