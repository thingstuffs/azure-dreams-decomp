#include "common.h"
#include "records/Rec_func_800A0668_arg0.h"


typedef struct S_800A0668_1 {
    u8 pad_00[0x1];
    u8 unk_01;
} S_800A0668_1;   /* ((Rec_func_800A0668_arg0 *)arg0)->unk_98 in func_800A0668 */


/* Test the object status, reversing the result when the linked record has bit 3 set. */
s32 func_800A0668(void *object) {
    if ((((S_800A0668_1 *)(((Rec_func_800A0668_arg0 *)object)->unk_98))->unk_01 & 8) != 0) {
        return ((Rec_func_800A0668_arg0 *)object)->unk_95 == 0;
    }
    return ((Rec_func_800A0668_arg0 *)object)->unk_95 != 0;
}
