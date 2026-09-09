#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK func_8003B034();                            /* extern */
M2C_UNK func_8003B06C();                            /* extern */
M2C_UNK town_seq_reserve();            /* extern */

/* Run the runtime sequence ending in town_seq_reserve(0x2B, 0x200). */
void func_8003B264(void) {
    func_8003B034();
    func_8003B06C();
    town_seq_reserve(0x2B, 0x200);
}
