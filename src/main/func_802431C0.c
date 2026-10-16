/* Relink of matched main/func_80011F7C; every changed retail word is a paired relocation. */
#include "common.h"
#include "m2c_compat.h"

typedef struct S_80024F7C_0 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_80024F7C_0;   /* temp_a1 in func_800261C0 */

typedef struct S_80024F7C_1 {
    s32 unk_00;
    u8 pad_04[0x40];
    s32 unk_44;
} S_80024F7C_1;   /* arg0 in func_800261C0; pointer addresses record offset 0x10 */


/* Clears flag 0x2000 and restores the saved record value when set. */
void func_800261C0(void *object_data) {
    u16 flags;
    S_80024F7C_0 *object_header;

    object_header = object_data - 0x20;
    flags = object_header->unk_1E;
    if (flags & 0x2000) {
        object_header->unk_1E = (u16) (flags & 0xDFFF);
        ((S_80024F7C_1 *)((u8 *)object_data - 0x10))->unk_00 = (s32) ((S_80024F7C_1 *)((u8 *)object_data
            - 0x10))->unk_44;
    }
}
