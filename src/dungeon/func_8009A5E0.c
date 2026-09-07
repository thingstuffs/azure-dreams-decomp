#include "common.h"
#include "m2c_compat.h"

s16 func_8009FCF0();                  /* extern */

typedef struct S_8009FD40_0 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009FD40_0;   /* arg0 in func_8009FD40 */

typedef struct S_8009FD40_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8009FD40_1;   /* arg1 in func_8009FD40 */

s16 func_8009FD40(S_8009FD40_0 *arg0, S_8009FD40_1 *arg1) {
    return func_8009FCF0(arg0->unk_24, arg0->unk_25, arg1->unk_24, arg1->unk_25);
}
