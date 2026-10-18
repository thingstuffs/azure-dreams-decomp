#include "common.h"
#include "m2c_compat.h"

#include "common.h"

M2C_UNK Control_CD(); /* extern */
M2C_UNK drain_cd_command_queue();                            /* extern */
extern s8 D_80080A89;
extern M2C_UNK D_80080C50;

/* Run initialization once and mark it complete. */
void load_shared_resource_once(void) {
    if (D_80080A89 == 0) {
        Control_CD(6, &D_80080C50, 0);
        drain_cd_command_queue();
        D_80080A89 = 1;
    }
}
