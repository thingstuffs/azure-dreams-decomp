#include "common.h"
#include "records/Rec_D_8001E950.h"

typedef long long s64;
typedef unsigned long long u64;

typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
typedef s64 M2C_UNK64;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001A7E8();
extern s32 func_8001AC60();
extern void *D_8001E950;



typedef struct S_8001AC10_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001AC10_1;   /* arg0 in func_8001AC10 */

typedef struct S_8001AC10_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001AC10_2;   /* ((arg1 * 0x10) + ((S_8001AC10_1 *)arg0)->unk_10) in func_8001AC10 */

s32 func_8001AC10(S_8001AC10_1 *arg0, s32 arg1) {
    if (((Rec_D_8001E950 *)D_8001E950)->unk_05 == 9) {
        ((S_8001AC10_2 *)(((arg1 * 0x10) + arg0->unk_10)))->unk_08 = func_8001A7E8();
        return 0;
    }
    func_8001AC60();
    return 1;
}
