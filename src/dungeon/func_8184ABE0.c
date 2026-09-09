#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800243E0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800243E0_0;   /* temp_v0 in func_800243E0 */

typedef struct S_800243E0_1 {
    u8 pad_00[0xC];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
    u8 pad_0F[0xD];
    s16 unk_1C;
    s16 unk_1E;
} S_800243E0_1;   /* temp_s0 in func_800243E0 */

typedef struct S_800243E0_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800243E0_2;   /* temp_v1 in func_800243E0 */

typedef struct S_800243E0_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800243E0_3;   /* arg0 in func_800243E0 */



extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK D_80024374;
extern M2C_UNK D_80045340;
extern M2C_UNK D_800DE870;

/* Creates a type 0x212 object, initializes its appearance, and copies the supplied components. */
void *func_800243E0(S_800243E0_3 *source) {
    S_800243E0_1 *appearance;
    S_800243E0_0 *object;
    S_800243E0_2 *components;
    register void *result ASM_REG("$2"); /* MATCH: Keep the merged return value in v0 for the shared epilogue. */

    object = func_8003FC64(0x212);
    if (object == 0) {
        result = 0;
    } else {
        object->unk_10 = &D_80024374;
        appearance = object->unk_0C;
        appearance->unk_0E = 0x80;
        appearance->unk_0D = 0x80;
        appearance->unk_0C = 0x80;
        func_8003DB94(appearance, &D_800DE870, 0);
        appearance->unk_1E = 0x2000;
        appearance->unk_1C = 0x2000;
        func_8004491C(object, &D_80045340);
        components = object->unk_08;
        components->unk_02 = source->unk_02;
        components->unk_06 = source->unk_06;
        components->unk_0A = source->unk_0A;
        result = object;
    }
    return result;
}
