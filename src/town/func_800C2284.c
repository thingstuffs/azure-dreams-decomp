#include "common.h"
#include "records/Rec_func_8008F074_arg0.h"

typedef s32 M2C_UNK;

typedef struct S_800BF9E4_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800BF9E4_0_pre;   /* the 0x10 bytes before arg0 in func_800BF9E4, addressed as arg0[-1] */


typedef struct S_800BF9E4_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BF9E4_1;   /* arg1 in func_800BF9E4 */

typedef struct S_800BF9E4_2 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
} S_800BF9E4_2;   /* temp_v0 in func_800BF9E4 */

typedef struct S_800BF9E4_3 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0xA];
    s16 unk_1A;
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} S_800BF9E4_3;   /* temp_v1 in func_800BF9E4 */

typedef struct S_800BF9E4_4 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_800BF9E4_4;   /* temp_v1_2 in func_800BF9E4 */

typedef struct S_800BF9E4_5 {
    u8 pad_00[0xA0];
    void * unk_A0;
} S_800BF9E4_5;   /* temp_v0_2 in func_800BF9E4 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern M2C_UNK func_8008F074();

extern u8 D_80045340[];
extern u8 D_80046398[];
extern u8 D_800BF72C[];
extern u8 D_800BF8DC[];
extern u8 D_800D2364[];
extern s32 D_800D237C[];
extern u8 D_800F9F78[];

void func_800BF9E4(void *arg0, S_800BF9E4_1 *arg1, M2C_UNK arg2) {
    void *temp_v0;
    S_800BF9E4_5 *temp_v0_2;
    S_800BF9E4_3 *temp_v1;
    S_800BF9E4_4 *temp_v1_2;

    ((S_800BF9E4_0_pre *)arg0)[-1].unk_00 = &D_800BF8DC[0];
    ((Rec_func_8008F074_arg0 *)arg0)->unk_50 = 0;
    func_8004491C(arg0 - 0x20, &D_80045340[0]);
    arg1->unk_00 = 0x0F200000;
    arg1->unk_04 = 0x02600000;
    arg1->unk_08 = 0;
    func_8008F074(arg0, arg1, &D_800D2364[0]);
    func_8003DB94(arg2, &D_800F9F78[0], 0);
    ((Rec_func_8008F074_arg0 *)arg0)->unk_48 = D_800D237C[0];
    temp_v0 = func_8003FC64(0x136);
    if (temp_v0 != 0) {
        func_8004491C(temp_v0, &D_80046398[0]);
        temp_v1 = ((S_800BF9E4_2 *)temp_v0)->unk_0C;
        ((S_800BF9E4_2 *)temp_v0)->unk_10 = &D_800BF72C[0];
        temp_v1->unk_1C = 0x1000;
        temp_v1->unk_1E = 0x1000;
        temp_v1->unk_20 = 0x1000;
        temp_v1->unk_1A = 0;
        temp_v1->unk_0C = 0x808080;
        temp_v1->unk_08 = 0x75;
        temp_v1_2 = ((S_800BF9E4_2 *)temp_v0)->unk_08;
        temp_v1_2->unk_00 = 0x0FA00000;
        temp_v1_2->unk_04 = 0x02300000;
        temp_v0_2 = temp_v0 + 0x20;
        ASM_USE(temp_v0_2);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        temp_v1_2->unk_08 = 0;
        temp_v0_2->unk_A0 = arg0;
    }
}

/* MECHANISM: Natural argument liveness gives the 0x20 frame and s2/s0/s1 save order.
   A split tail sub-base plus input-only ASM_USE materializes v0 = s0 + 0x20 without a second def.
   This restores the 0xA0(v0) store and its upstream branch displacement; aligned residue is zero. */
