#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_func_800B0C68_arg0.h"


typedef struct S_800B0C68_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B0C68_2;   /* temp_v1 in func_800B0C68 */

typedef struct S_800B0C68_3 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800B0C68_3;   /* ((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv in func_800B0C68 */

typedef struct S_800B0C68_4 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B0C68_4;   /* ((S_800B0C68_2 *)temp_v1)->unk_0C in func_800B0C68 */

typedef struct S_800B0C68_5 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B0C68_5;   /* ((S_800B0C68_2 *)temp_v1)->unk_08 in func_800B0C68 */

typedef struct S_800B0C68_6 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B0C68_6;   /* ((S_800B0C68_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_08 in func_800B0C68 */

typedef struct S_800B0C68_7 {
    u8 pad_00[0x4];
    void * unk_04;
} S_800B0C68_7;   /* ((S_800B0C68_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_0C in func_800B0C68 */

typedef struct S_800B0C68_8 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_800B0C68_8;   /* ((S_800B0C68_4 *)(((S_800B0C68_2 *)temp_v1)->unk_0C))->unk_04 in func_800B0C68 */

typedef struct S_800B0C68_9 {
    u8 pad_00[0xA];
    u16 unk_0A;
} S_800B0C68_9;   /* ((S_800B0C68_5 *)(((S_800B0C68_2 *)temp_v1)->unk_08))->unk_04 in func_800B0C68 */

typedef struct S_800B0C68_10 {
    u8 pad_00[0x8];
    s16 unk_08;
    s16 unk_0A;
} S_800B0C68_10;   /* ((S_800B0C68_6 *)(((S_800B0C68_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_08))->unk_04 in func_800B0C68 */

typedef struct S_800B0C68_11 {
    u8 pad_00[0x8];
    s16 unk_08;
} S_800B0C68_11;   /* ((S_800B0C68_7 *)(((S_800B0C68_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_0C))->unk_04 in func_800B0C68 */





void func_800B0C68(Rec_func_800B0C68_arg0 *arg0) {
    S_800B0C68_2 *temp_v1;

    ((S_800B0C68_10 *)(((S_800B0C68_6 *)(((S_800B0C68_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_08))->unk_04))->unk_08 = -0x58;
    ((S_800B0C68_10 *)(((S_800B0C68_6 *)(((S_800B0C68_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_08))->unk_04))->unk_0A = (s16) (((arg0->unk_08 % 5) * 0x10) + 8);
    ((S_800B0C68_11 *)(((S_800B0C68_7 *)(((S_800B0C68_3 *)(((Rec_func_800B0C68_arg0 *)arg0)->unk_CC.as_pv))->unk_0C))->unk_04))->unk_08 = 0;
    temp_v1 = arg0->unk_CC.as_pv;
    ((S_800B0C68_8 *)(((S_800B0C68_4 *)(temp_v1->unk_0C))->unk_04))->unk_0A = (s16) (((S_800B0C68_9 *)(((S_800B0C68_5 *)(temp_v1->unk_08))->unk_04))->unk_0A - 9);
}
