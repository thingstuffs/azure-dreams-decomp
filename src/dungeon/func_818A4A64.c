#include "common.h"



typedef s32 M2C_UNK;

#ifndef NULL
#define NULL 0
#endif

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80024320(void) __attribute__((noreturn));
extern M2C_UNK func_8003DB94();
extern void *func_8003FC64();
extern M2C_UNK func_8004491C();
extern u8 D_80024230[];
extern u8 D_80045340[];
extern u8 D_800DEAE0[];

#ifndef NON_MATCHING
register u32 match_v0 ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

typedef struct S_818A4A64_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xC];
    s32 unk_20;
} S_818A4A64_0;   /* temp_v0 in func_818A4A64 */

typedef struct S_818A4A64_1 {
    u8 pad_00[0xC];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
    u8 pad_0F[0x5];
    u16 unk_14;
    u8 pad_16[0x6];
    s16 unk_1C;
    s16 unk_1E;
} S_818A4A64_1;   /* temp_s0 in func_818A4A64 */

typedef struct S_818A4A64_2 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4A64_2;   /* arg1 in func_818A4A64 */

typedef struct S_818A4A64_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_818A4A64_3;   /* temp_v1 in func_818A4A64 */

void *func_818A4A64(s32 arg0, S_818A4A64_2 *arg1) {
    S_818A4A64_1 *temp_s0;
    S_818A4A64_0 *temp_v0;
    S_818A4A64_3 *temp_v1;
    u8 *call_data;
#ifdef NON_MATCHING
    u32 match_v0;
#endif

    temp_v0 = func_8003FC64(0x212);
#ifndef NON_MATCHING
    call_data = (u8 *) 0x800E0000;
#else
    call_data = D_800DEAE0;
#endif
    if (temp_v0 == NULL) {
        match_v0 = 0;
        func_80024320();
    }
#ifndef NON_MATCHING
    ASM_KEEP(call_data);   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
    call_data -= 0x1520;
    match_v0 = 0x80020000;
    ASM_KEEP(match_v0);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    match_v0 += 0x4230;
#else
    match_v0 = (u32) D_80024230;
#endif
    temp_s0 = temp_v0->unk_0C;
    temp_v0->unk_10 = (M2C_UNK *) match_v0;
    temp_v0->unk_20 = arg0;
    temp_s0->unk_0E = 0;
    temp_s0->unk_0D = 0;
    temp_s0->unk_0C = 0;
    func_8003DB94(temp_s0, call_data, 0);
    match_v0 = temp_s0->unk_14;
    temp_s0->unk_1E = 0x1000;
    temp_s0->unk_1C = 0x1000;
    match_v0 |= 0xC;
    temp_s0->unk_14 = (u16) match_v0;
    func_8004491C(temp_v0, D_80045340);
    temp_v1 = temp_v0->unk_08;
#ifndef NON_MATCHING
    __asm__ __volatile__("" : : "r"(arg1));
#endif
    match_v0 = arg1->unk_02;
    temp_v1->unk_02 = (u16) match_v0;
    match_v0 = arg1->unk_06;
    temp_v1->unk_06 = (u16) match_v0;
    temp_v1->unk_0A = (u16) arg1->unk_0A;
    return temp_v0;
}
