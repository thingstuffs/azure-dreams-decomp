#include "common.h"



#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void *func_8003FC64();
extern s32 func_8003FD64();
extern void *func_8009C3DC();
extern void *func_8009C44C();

typedef struct S_8009C390_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    s32 unk_10;
} S_8009C390_0;   /* temp_v0 in func_8009C390 */

typedef struct S_8009C390_1 {
    u8 pad_00[0x50];
    s32 unk_50;
    u8 pad_54[0x48];
    s32 unk_9C;
} S_8009C390_1;   /* temp_a0 in func_8009C390 */

typedef struct S_8009C390_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009C390_2;   /* temp_a1 in func_8009C390 */

typedef struct S_8009C390_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
} S_8009C390_3;   /* arg1 in func_8009C390 */

typedef struct S_8009C390_4 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0xC];
    s16 unk_1C;
    s16 unk_1E;
} S_8009C390_4;   /* temp_a2 in func_8009C390 */

void *func_8009C390(s32 arg0, S_8009C390_3 *arg1, s32 arg2, s32 arg3) {
    S_8009C390_1 *temp_a0;
    S_8009C390_2 *temp_a1;
    S_8009C390_4 *temp_a2;
    void *temp_v0;

    if (arg0 != 0) {
        register void *temp_v1 ASM_REG("$3");   /* MATCH pin: retail delay-slot contents depend on it */
        temp_v1 = (void *)func_8003FD64(0x116, arg0);
        ASM_TAILSLOT_PIN(temp_v1);   /* MATCH pin: retail delay-slot contents depend on it */
        return func_8009C3DC();
    }
    temp_v0 = func_8003FC64(0x116);
    temp_a0 = temp_v0 + 0x20;
    if (temp_v0 == NULL) {
        func_8009C44C(temp_a0);
        return NULL;
    }
    temp_a1 = ((S_8009C390_0 *)temp_v0)->unk_08;
    temp_a2 = ((S_8009C390_0 *)temp_v0)->unk_0C;
    ((S_8009C390_0 *)temp_v0)->unk_10 = arg2;
    ASM_KEEP(arg0);   /* MATCH pin: retail callee-saved set / frame layout depends on it */
    temp_a0->unk_50 = arg3;
    if (arg0 != 0) {
        temp_a0->unk_9C = (s32)(arg0 + 0x20);
    }
    if (arg1 != NULL) {
        temp_a1->unk_00 = arg1->unk_00;
        temp_a1->unk_04 = arg1->unk_04;
        temp_a1->unk_08 = arg1->unk_08;
    }
    temp_a2->unk_1E = 0x1000;
    temp_a2->unk_1C = 0x1000;
    temp_a2->unk_0C = 0x808080;
    return temp_v0;
}
