#include "common.h"
#include "m2c_compat.h"

#include "common.h"

typedef struct S_800399EC_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800399EC_1;   /* arg0 in func_800399EC */

typedef struct S_800399EC_2 {
    u8 pad_00[0x3D];
    u8 unk_3D;
} S_800399EC_2;   /* ((S_800399EC_1 *)arg0)->unk_80 in func_800399EC */


typedef struct S_800399EC_0 {
    u8 pad_00[0x1C];
    u8 * unk_1C;
} S_800399EC_0;   /* arg0 in func_800399EC */


/* Store the next event-script byte in the linked object's field and advance the script pointer. */
void func_800399EC(S_800399EC_0 *script_ctx) {
    u8 *script_ptr;

    script_ptr = script_ctx->unk_1C;
    ((S_800399EC_2 *)(((S_800399EC_1 *)script_ctx)->unk_80))->unk_3D = (u8) *script_ptr;
    script_ctx->unk_1C = (u8 *) (script_ptr + 1);
}
