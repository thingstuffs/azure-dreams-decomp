#include "common.h"

#ifndef NULL
#define NULL 0
#endif

typedef struct S_80026ED0_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80026ED0_0;   /* temp_v0 in func_80026ED0 */

typedef struct S_80026ED0_1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80026ED0_1;   /* temp_v0_2 in func_80026ED0 */

typedef struct S_80026ED0_2 {
    u8 pad_00[0x8];
    void * unk_08;
    s32 unk_0C;
    s16 unk_10;
    u8 pad_12[0x2];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_80026ED0_2;   /* temp_v1 in func_80026ED0 */

typedef struct S_80026ED0_3 {
    u8 pad_00[0x66];
    s16 unk_66;
    u8 pad_68[0x2];
    s16 unk_6A;
} S_80026ED0_3;   /* temp_v1_2 in func_80026ED0 */



extern void *func_8003FD64();
extern s32 func_8004491C();
extern s32 D_80026E3C;
extern s32 D_80045340;
extern s32 D_80083498;
extern s32 D_800DF358;

void *func_80026ED0(s16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    void *temp_v0;
    S_80026ED0_1 *temp_v0_2;
    S_80026ED0_2 *temp_v1;
    S_80026ED0_3 *temp_v1_2;
    register s16 p1 ASM_REG("$18");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 p2 ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    register s16 p3 ASM_REG("$20");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */

    p1 = arg1;
    p2 = arg2;
    p3 = arg3;

    temp_v0 = func_8003FD64(0x12, &D_80083498);
    ASM_KEEP(p1);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p2);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(p3);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if (temp_v0 != NULL) {
        ((S_80026ED0_0 *)temp_v0)->unk_10 = &D_80026E3C;
        func_8004491C(temp_v0, &D_80045340);
        temp_v0_2 = ((S_80026ED0_0 *)temp_v0)->unk_08;
        temp_v0_2->unk_02 = arg0;
        temp_v0_2->unk_06 = p1;
        temp_v0_2->unk_0A = p2;
        temp_v1 = ((S_80026ED0_0 *)temp_v0)->unk_0C;
        temp_v1->unk_08 = &D_800DF358;
        temp_v1->unk_0C = 0x808080;
        temp_v1->unk_1E = p3;
        temp_v1->unk_1C = p3;
        temp_v1->unk_10 = 0x20;
        temp_v1->unk_14 |= 0xC;
        temp_v1_2 = (u8 *)temp_v0 + 0x20;
        temp_v1_2->unk_66 = 0x20;
        temp_v1_2->unk_6A = 0x80;
    }
    return temp_v0;
}
