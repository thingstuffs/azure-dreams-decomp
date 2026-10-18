#include "common.h"
#include "m2c_compat.h"

typedef struct S_800B34A8_0 {
    u8 pad_00[0xA8];
    void * unk_A8;
} S_800B34A8_0;   /* arg0 in reset_record_resources */

typedef struct S_800B34A8_1 {
    u8 pad_00[0x98];
    s32 unk_98;
    s32 unk_9C;
} S_800B34A8_1;   /* ((S_800B34A8_0 *)arg0)->unk_A8 in reset_record_resources */


M2C_UNK func_800497F4();                /* extern */
s32 advance_timed_tagged_stream();                         /* extern */


/* Resets the object substate and its two referenced resources. */
void reset_record_resources(void *object) {
    advance_timed_tagged_stream(object + 0x1C);
    func_800497F4(((S_800B34A8_1 *)(((S_800B34A8_0 *)object)->unk_A8))->unk_98, 0);
    func_800497F4(((S_800B34A8_1 *)(((S_800B34A8_0 *)object)->unk_A8))->unk_9C, 0);
}
