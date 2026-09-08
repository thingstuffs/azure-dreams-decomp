#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_8001ACA0_3 {
    u8 pad_00[0x68];
    void * unk_68;
} S_8001ACA0_3;   /* ((Rec_D_80016000 *)D_80016000)->unk_24 in func_8001ACA0 */

typedef struct S_8001ACA0_4 {
    u8 pad_00[0x8];
    void * unk_08;
} S_8001ACA0_4;   /* ((S_8001ACA0_3 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68 in func_8001ACA0 */




extern void *D_80016000;

typedef struct S_8001ACA0_0 {
    u16 unk_00;
    u16 unk_02;
    u16 unk_04;
} S_8001ACA0_0;   /* arg0 in func_8001ACA0 */

typedef struct S_8001ACA0_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8001ACA0_1;   /* temp_v1 in func_8001ACA0 */

/* Copy three 16-bit components from the current nested record to the output. */
void func_8001ACA0(S_8001ACA0_0 *components) {
    S_8001ACA0_1 *source_record;

    source_record = ((S_8001ACA0_4 *)(((S_8001ACA0_3 *)(((Rec_D_80016000 *)D_80016000)->unk_24))->unk_68))->unk_08;
    components->unk_00 = (u16) source_record->unk_02;
    components->unk_02 = (u16) source_record->unk_06;
    components->unk_04 = (u16) source_record->unk_0A;
}
