#include "common.h"

#include "common.h"
void func_8003B034(void);                            /* extern */
void func_8003B06C(void);                            /* extern */
void town_seq_reserve(s16 sequence_effect, s16 sequence_id);            /* extern */

/* Run the runtime sequence ending in town_seq_reserve(0x2B, 0x200). */
void func_8003B264(void) {
    func_8003B034();
    func_8003B06C();
    town_seq_reserve(0x2B, 0x200);
}
