#include "common.h"
#include "m2c_compat.h"

typedef struct S_8002692C_0 {
    M2C_UNK * unk_00;
    u8 pad_04[0x18];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0x4];
    s32 unk_2C;
} S_8002692C_0;   /* arg0 in func_8002692C; pointer addresses record offset 0x10 */


M2C_UNK func_80026708();                    /* extern */
M2C_UNK func_8002675C();                      /* extern */
extern M2C_UNK D_800266B0;

// Initializes record fields and substructures for the supplied type.
void func_8002692C(void *recordFields, s32 recordValue2C, s32 typeCode, s32 recordValue24) {
    s32 isType13;

    ((S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_1C = typeCode;
    isType13 = typeCode == 0x13;
    ((S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_20 = isType13;
    func_80026708(recordFields + 0x20, isType13);
    func_8002675C(recordFields + 0x2C);
    ((S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_24 = recordValue24;
    ((S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_2C = recordValue2C;
    ((S_8002692C_0 *)((u8 *)recordFields - 0x10))->unk_00 = &D_800266B0;
}
