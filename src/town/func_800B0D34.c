#include "common.h"
#include "m2c_compat.h"

typedef struct S_800AE494_0 {
    s32 unk_00;
    u8 pad_04[0xC];
    s32 unk_10;
    s32 unk_14;
} S_800AE494_0;   /* arg0 in func_800AE494; pointer addresses record offset 0x10 */


M2C_UNK func_800B0418();                         /* extern */
M2C_UNK func_800B0700();                         /* extern */

/* Pass the record handles to their handlers and clear its secondary handle and status. */
void func_800AE494(void *record_payload) {
    func_800B0700(((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_14);
    ((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_14 = 0;
    func_800B0418(((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_10);
    ((S_800AE494_0 *)((u8 *)record_payload - 0x10))->unk_00 = 0;
}
