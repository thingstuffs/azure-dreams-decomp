#include "common.h"

typedef struct S_800B25D8_0 {
    u8 pad_00[0x3C];
    s32 unk_3C;
} S_800B25D8_0;   /* (((*(s32 *)((u8 *)arg0 + 0x14)) * 4) + arg0) in func_800B25D8 */
typedef struct {
    u8 unk0;
    u8 unk1;
} S_8004AFE8;
void func_8004B08C(S_8004AFE8 **entries);                         /* extern */

/* Pass the indexed record value to func_8004B08C. */
void func_800B25D8(void *record) {
    func_8004B08C(((S_800B25D8_0 *)((((*(s32 *)((u8 *)record + 0x14)) * 4) + record)))->unk_3C);
}
