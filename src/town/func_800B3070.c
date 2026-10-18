#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B07D0_1 {
    u8 pad_00[0xCC];
    void * unk_CC;
} S_800B07D0_1;   /* arg0 in process_shop_embedded_data */

typedef struct S_800B07D0_2 {
    u8 pad_00[0x74];
    s32 unk_74;
    s32 unk_78;
} S_800B07D0_2;   /* ((S_800B07D0_1 *)arg0)->unk_CC in process_shop_embedded_data */


M2C_UNK func_800497F4();                    /* extern */
s32 advance_timed_tagged_stream();                         /* extern */

typedef struct S_800B07D0_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_800B07D0_0;   /* arg0 in process_shop_embedded_data */

/* Process the embedded data and pass the record flag bits to its two linked handles. */
void process_shop_embedded_data(void *record) {
    advance_timed_tagged_stream(record + 0x28);
    func_800497F4(((S_800B07D0_2 *)(((S_800B07D0_1 *)record)->unk_CC))->unk_74, ((S_800B07D0_0 *)record)->unk_1C & 2);
    func_800497F4(((S_800B07D0_2 *)(((S_800B07D0_1 *)record)->unk_CC))->unk_78, ((S_800B07D0_0 *)record)->unk_1C & 1);
}
