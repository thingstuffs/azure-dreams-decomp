#include "common.h"

#include "common.h"
void func_8003B034(void);                            /* extern */
void init_town_runtime_objects(void);                            /* extern */
void town_seq_reserve(s16 sequence_effect, s16 sequence_id);            /* extern */

/* Run the runtime sequence ending in town_seq_reserve(0x2B, 0x200). */
void init_town_runtime_with_sequence(void) {
    func_8003B034();
    init_town_runtime_objects();
    town_seq_reserve(0x2B, 0x200);
}
