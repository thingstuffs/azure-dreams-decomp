#include "common.h"
#include "m2c_compat.h"

typedef struct S_800270E0_0 {
    u8 pad_00[0xF0];
    void * unk_F0;
    void * unk_F4;
    void * unk_F8;
    void * unk_FC;
} S_800270E0_0;   /* arg0 in func_800270E0 */

typedef struct S_800270E0_1 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_1;   /* ((S_800270E0_0 *)arg0)->unk_FC in func_800270E0 */

typedef struct S_800270E0_2 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_2;   /* ((S_800270E0_0 *)arg0)->unk_F0 in func_800270E0 */

typedef struct S_800270E0_3 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_3;   /* ((S_800270E0_0 *)arg0)->unk_F4 in func_800270E0 */

typedef struct S_800270E0_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800270E0_4;   /* ((S_800270E0_0 *)arg0)->unk_F8 in func_800270E0 */

typedef struct S_800270E0_5 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_5;   /* ((S_800270E0_1 *)(((S_800270E0_0 *)arg0)->unk_FC))->unk_04 in func_800270E0 */

typedef struct S_800270E0_6 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_6;   /* ((S_800270E0_2 *)(((S_800270E0_0 *)arg0)->unk_F0))->unk_04 in func_800270E0 */

typedef struct S_800270E0_7 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_7;   /* ((S_800270E0_3 *)(((S_800270E0_0 *)arg0)->unk_F4))->unk_04 in func_800270E0 */

typedef struct S_800270E0_8 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800270E0_8;   /* ((S_800270E0_4 *)(((S_800270E0_0 *)arg0)->unk_F8))->unk_04 in func_800270E0 */




M2C_UNK func_80027018();                      /* extern */
M2C_UNK func_80027054();                            /* extern */
M2C_UNK func_80027080();       /* extern */


void func_800270E0(void *arg0) {
    func_80027054();
    func_80027080(arg0 + 4, 0x36, 0x10);
    func_80027018(arg0);
    ((S_800270E0_5 *)(((S_800270E0_1 *)(((S_800270E0_0 *)arg0)->unk_FC))->unk_04))->unk_08 = 0x8E;
    ((S_800270E0_5 *)(((S_800270E0_1 *)(((S_800270E0_0 *)arg0)->unk_FC))->unk_04))->unk_0A = 0x82;
    ((S_800270E0_6 *)(((S_800270E0_2 *)(((S_800270E0_0 *)arg0)->unk_F0))->unk_04))->unk_08 = 9;
    ((S_800270E0_6 *)(((S_800270E0_2 *)(((S_800270E0_0 *)arg0)->unk_F0))->unk_04))->unk_0A = 0xA;
    ((S_800270E0_7 *)(((S_800270E0_3 *)(((S_800270E0_0 *)arg0)->unk_F4))->unk_04))->unk_08 = 0x42;
    ((S_800270E0_7 *)(((S_800270E0_3 *)(((S_800270E0_0 *)arg0)->unk_F4))->unk_04))->unk_0A = 0xA;
    ((S_800270E0_8 *)(((S_800270E0_4 *)(((S_800270E0_0 *)arg0)->unk_F8))->unk_04))->unk_08 = 0x24;
    ((S_800270E0_8 *)(((S_800270E0_4 *)(((S_800270E0_0 *)arg0)->unk_F8))->unk_04))->unk_0A = 0xA;
}
