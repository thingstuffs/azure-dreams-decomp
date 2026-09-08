#include "common.h"
#include "records/Rec_D_80016000.h"


typedef s32 (*Callback)(s32);


typedef struct S_8001BFF4_1 {
    u8 pad_00[0x10];
    void * unk_10;
} S_8001BFF4_1;   /* arg0 in func_8001BFF4 */

typedef struct S_8001BFF4_2 {
    u8 pad_00[0x20];
    void * unk_20;
} S_8001BFF4_2;   /* ((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v in func_8001BFF4 */

typedef struct S_8001BFF4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
} S_8001BFF4_3;   /* (u8 *)((S_8001BFF4_1 *)arg0)->unk_10 + arg1 * 0x10 in func_8001BFF4 */


extern s32 func_8001A58C(s32);
extern s32 func_8001A86C(s32);
extern s32 func_8001A9B4(s32);
extern s8 D_80016000[];
extern u8 *D_8001E950;

/* Updates the indexed entry from the current selection in mode 2. */
s32 func_8001BFF4(S_8001BFF4_1 *context, s32 entry_index) {
    u8 mode;

    mode = D_8001E950[5];
    if (mode == 2) {
        if ((*(Callback *)((u8 *)(((S_8001BFF4_2 *)(((Rec_D_80016000 *)D_80016000)->unk_00.at00_pv.v))->unk_20) + 0x2D4))(0) == mode) {
            if (func_8001A58C(D_8001E950[4]) != 0) {
                ((S_8001BFF4_3 *)((u8 *)context->unk_10 + entry_index * 0x10))->unk_08 =
                    func_8001A86C(D_8001E950[4]);
                return 0;
            } else {
                ((S_8001BFF4_3 *)((u8 *)context->unk_10 + entry_index * 0x10))->unk_08 =
                    func_8001A86C(0);
                return 0;
            }
        } else {
            s32 selection;

            if (func_8001A58C(D_8001E950[4]) != 0) {
                selection = D_8001E950[4];
            } else {
                selection = 0;
            }
            ((S_8001BFF4_3 *)((u8 *)context->unk_10 + entry_index * 0x10))->unk_08 =
                func_8001A9B4(selection);
            return 0;
        }
    }
    return 1;
}
