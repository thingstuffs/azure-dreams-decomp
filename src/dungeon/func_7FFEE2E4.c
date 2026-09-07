#include "common.h"
#include "m2c_compat.h"

typedef struct S_8008BA44_0 {
    void * unk_00;
    u8 pad_04[0x60];
    union { volatile s16 s; s16 u; } unk_64;   /* accessed as both */
    s16 unk_66;
    M2C_UNK * unk_68;
    s32 unk_6C;
} S_8008BA44_0;   /* arg0 in func_8008BA44 */

typedef struct S_8008BA44_1 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008BA44_1;   /* temp_v0 in func_8008BA44 */

typedef struct S_8008BA44_2 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_8008BA44_2;   /* temp_v1 in func_8008BA44 */


extern M2C_UNK D_8008BC58;
extern s8 D_800CFC70[];
extern s32 D_800CFC7C[];

void func_8008BA44(S_8008BA44_0 *arg0) {
    S_8008BA44_1 *temp_v0;
    S_8008BA44_2 *temp_v1;
    s32 temp_v2;

    temp_v0 = arg0->unk_00;
    temp_v0->unk_0A = (u16) (temp_v0->unk_0A - 0x100);
    temp_v1 = arg0->unk_00;
    if ((s16) temp_v1->unk_0A < 0) {
        temp_v1->unk_0A = 0U;
        arg0->unk_68 = &D_8008BC58;
        arg0->unk_64.s = (s16) (s8) D_800CFC70[arg0->unk_66];
        temp_v2 = D_800CFC7C[arg0->unk_66];
        arg0->unk_64.u = 0x16;
        arg0->unk_6C = temp_v2;
    }
}
