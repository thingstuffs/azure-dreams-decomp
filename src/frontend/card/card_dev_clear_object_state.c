#include "common.h"
#include "m2c_compat.h"

typedef struct S_8001D224_0 {
    s32 unk_00;
} S_8001D224_0;   /* arg0 in card_dev_clear_object_state; pointer addresses record offset 0x10 */


/* Clears the record's first word given a pointer to its offset 0x10. */
void card_dev_clear_object_state(void *record_data) {
    ((S_8001D224_0 *)((u8 *)record_data - 0x10))->unk_00 = 0;
}
