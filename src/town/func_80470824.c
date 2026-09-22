#include "common.h"
#include "m2c_compat.h"

typedef struct S_80017824_2 {
    u8 pad_00[0x4];
    M2C_UNK * unk_04;
} S_80017824_2;   /* (offset + obj->unk_10) in func_80017824 */


s32 func_800169EC();                                /* extern */
M2C_UNK func_80017808();                      /* extern */
M2C_UNK func_8001A418();                     /* extern */
s32 func_8001A510();                         /* extern */
extern M2C_UNK D_80016A3C;
extern M2C_UNK D_8001B718;

typedef struct S_80017824_0 {
    u8 pad_00[0x10];
    s32 unk_10;
} S_80017824_0;   /* obj in func_80017824 */

typedef struct S_80017824_1 {
    u8 pad_00[0x8];
    M2C_UNK * unk_08;
} S_80017824_1;   /* entry in func_80017824 */

/* On the first 0x479 event, point the object's table slot at the two shared records and refresh it. */
s32 func_80017824(S_80017824_0 *obj, s32 index) {
    s32 offset;
    S_80017824_1 *entry;

    if ((func_8001A510(0x479) == 0) && (func_800169EC() != 0)) {
        func_8001A418(0x479);
        offset = index * 0x10;
        ((S_80017824_2 *)((offset + obj->unk_10)))->unk_04 = &D_80016A3C;
        entry = offset + obj->unk_10;
        entry->unk_08 = &D_8001B718;
        func_80017808(entry);
    }
    return 0;
}
