#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_800BF9E4_0_pre {
    M2C_UNK * unk_00;
    u8 pad_04[0xC];
} S_800BF9E4_0_pre;   /* the 0x10 bytes before arg0 in func_800BF9E4, addressed as arg0[-1] */

typedef struct S_800BF9E4_0 {
    u8 pad_00[0x48];
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
} S_800BF9E4_0;   /* arg0 in func_800BF9E4 */

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

/* Initialize the object and create a positioned visual child linked to it. */
void func_800BF9E4(void *object, S_800BF9E4_1 *position, M2C_UNK resource_context) {
    void *child;
    S_800BF9E4_5 *child_data;
    S_800BF9E4_3 *child_visual;
    S_800BF9E4_4 *child_position;

    ((S_800BF9E4_0_pre *)object)[-1].unk_00 = &D_800BF8DC[0];
    ((S_800BF9E4_0 *)object)->unk_50 = 0;
    func_8004491C(object - 0x20, &D_80045340[0]);
    position->unk_00 = 0x0F200000;
    position->unk_04 = 0x02600000;
    position->unk_08 = 0;
    func_8008F074(object, position, &D_800D2364[0]);
    func_8003DB94(resource_context, &D_800F9F78[0], 0);
    ((S_800BF9E4_0 *)object)->unk_48 = D_800D237C[0];
    child = func_8003FC64(0x136);
    if (child != 0) {
        func_8004491C(child, &D_80046398[0]);
        child_visual = ((S_800BF9E4_2 *)child)->unk_0C;
        ((S_800BF9E4_2 *)child)->unk_10 = &D_800BF72C[0];
        child_visual->unk_1C = 0x1000;
        child_visual->unk_1E = 0x1000;
        child_visual->unk_20 = 0x1000;
        child_visual->unk_1A = 0;
        child_visual->unk_0C = 0x808080;
        child_visual->unk_08 = 0x75;
        child_position = ((S_800BF9E4_2 *)child)->unk_08;
        child_position->unk_00 = 0x0FA00000;
        child_position->unk_04 = 0x02300000;
        child_data = child + 0x20;
        ASM_USE(child_data);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        child_position->unk_08 = 0;
        child_data->unk_A0 = object;
    }
}

/* MECHANISM: Natural argument liveness gives the 0x20 frame and s2/s0/s1 save order.
   A split tail sub-base plus input-only ASM_USE materializes v0 = s0 + 0x20 without a second def.
   This restores the 0xA0(v0) store and its upstream branch displacement; aligned residue is zero. */
