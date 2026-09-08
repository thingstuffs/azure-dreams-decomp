#include "common.h"
#include "records/Rec_D_8001E950.h"

typedef struct S_8001ADF8_2 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001ADF8_2;   /* ((arg1 * 0x10) + arg0->unk_10) in func_8001ADF8 */



typedef struct S_8001ADF8_1 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_8001ADF8_1;   /* arg0 in func_8001ADF8 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8001A6D0();
extern Rec_D_8001E950 *D_8001E950;

/* Stores the lookup result in the selected entry when the current record has code 7. */
s32 func_8001ADF8(S_8001ADF8_1 *entry_table, s32 entry_index) {
    if (D_8001E950->unk_05 == 7) {
        ((S_8001ADF8_2 *)(((entry_index * 0x10) + entry_table->unk_10)))->unk_08 =
            func_8001A6D0(D_8001E950->unk_03);
        return 0;
    }
    return 1;
}
