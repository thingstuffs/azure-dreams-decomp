#include "common.h"
#include "m2c_compat.h"

void *func_8003FC64();                       /* extern */
s32 func_8004491C();           /* extern */
extern void func_80024D70();
extern M2C_UNK D_800CEEFC;

typedef struct FadeObject {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} FadeObject;   /* temp_v0 in func_80024DE8 */

typedef struct FadeTransition {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    s16 unk_0E;
    u8 pad_10[0x2];
    s16 unk_12;
    u8 pad_14[0x2];
    s16 unk_16;
} FadeTransition;   /* temp_a0 in func_80024DE8 */

typedef struct FadeEndpoints {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x2];
    u16 unk_16;
} FadeEndpoints;   /* arg0 in func_80024DE8 */

typedef struct FadeObjectSettings {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} FadeObjectSettings;   /* temp_v1 in func_80024DE8 */

typedef struct FadeSettings {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    u16 unk_14;
    u8 pad_16[0x6];
    u16 unk_1C;
    u16 unk_1E;
} FadeSettings;   /* arg1 in func_80024DE8 */

/* Creates an object with initial values, endpoint differences, and copied settings. */
void *func_80024DE8(FadeEndpoints *endpoints, FadeSettings *settings) {
    FadeTransition *transition;
    FadeObject *object;
    FadeObjectSettings *object_settings;

    object = func_8003FC64(0x202);
    if (object != NULL) {
        object->unk_10 = &func_80024D70;
        func_8004491C(object, &D_800CEEFC);
        transition = object->unk_08;
        transition->unk_02 = (u16) endpoints->unk_02;
        transition->unk_06 = (u16) endpoints->unk_06;
        transition->unk_0A = (u16) endpoints->unk_0A;
        transition->unk_0E = (s16) (endpoints->unk_02 - endpoints->unk_0E);
        transition->unk_12 = (s16) (endpoints->unk_06 - endpoints->unk_12);
        transition->unk_16 = (s16) (endpoints->unk_0A - endpoints->unk_16);
        object_settings = object->unk_0C;
        object_settings->unk_1C = (u16) settings->unk_1C;
        object_settings->unk_1E = (u16) settings->unk_1E;
        object_settings->unk_0C = (s32) settings->unk_0C;
        object_settings->unk_08 = (s32) settings->unk_08;
        object_settings->unk_14 = (u16) settings->unk_14;
    }
    return object;
}
