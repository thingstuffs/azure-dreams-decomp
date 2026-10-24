#include "common.h"
#include "engine/script.h"
#include "m2c_compat.h"

#include "common.h"
#include "engine/script/vm.h"

typedef struct S_800399EC_1 {
    u8 pad_00[0x80];
    void * unk_80;
} S_800399EC_1;   /* arg0 in script_set_block_byte_3d */

typedef struct S_800399EC_2 {
    u8 pad_00[0x3D];
    u8 unk_3D;
} S_800399EC_2;   /* ((S_800399EC_1 *)arg0)->unk_80 in script_set_block_byte_3d */

/* Opcode 0x05: Store the u8 operand at VM block +0x3D. */
void script_set_block_byte_3d(ScriptReader *script_ctx) {
    u8 *script_ptr;

    script_ptr = script_ctx->cursor;
    ((S_800399EC_2 *)(((S_800399EC_1 *)script_ctx)->unk_80))->unk_3D = (u8) *script_ptr;
    script_ctx->cursor = (u8 *) (script_ptr + 1);
}
