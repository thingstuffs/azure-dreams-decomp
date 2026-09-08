#include "common.h"
#include "m2c_compat.h"

typedef struct S_80814D60_0 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
    void * unk_10;
} S_80814D60_0;   /* temp_v0 in func_80814D60 */

typedef struct S_80814D60_1 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
} S_80814D60_1;   /* temp_s1 in func_80814D60 */

typedef struct S_80814D60_2 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
} S_80814D60_2;   /* arg0 in func_80814D60 */


void *func_800373DC();                       /* extern */
M2C_UNK func_8003BC18();           /* extern */
s32 func_80071494();                                /* extern */
extern u8 D_8003C558[];
extern u8 D_802843E8[];
extern s32 D_802843EC[];
extern u8 D_8052FA64[];

void func_80814D60(S_80814D60_2 *arg0) {
    u32 page;
    register u16 flags ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
    s32 global_word;
    void *temp_s0;
    S_80814D60_1 *temp_s1;
    S_80814D60_0 *temp_v0;

    temp_v0 = func_800373DC(0x136);
    if (temp_v0 != NULL) {
        temp_v0->unk_10 = D_8052FA64;
        func_8003BC18(temp_v0, &D_8003C558);
        temp_s1 = temp_v0->unk_08;
        temp_s0 = temp_v0->unk_0C;
        temp_s1->unk_00 = (s32) (arg0->unk_00 + 0xFFF90000);
        temp_s1->unk_04 = (s32) (arg0->unk_04 + 0xFFFD0000);
        temp_s1->unk_08 = (s32) arg0->unk_08;
        temp_s1->unk_0C = (s32) ((s32) arg0->unk_0C >> 1);
        temp_s1->unk_14 = (s32) (((func_80071494() & 0x1FF) - 0x100) << 0xA);
        page = 0x00800000;
        ASM_KEEP(page);   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
        (*(volatile s16 *)((u8 *)temp_s0 + 0x1E)) = 0x800;
        (*(volatile s16 *)((u8 *)temp_s0 + 0x1C)) = 0x800;
        (*(volatile s16 *)((u8 *)temp_s0 + 0x10)) = 0x60;
        flags = (*(volatile u16 *)((u8 *)temp_s0 + 0x14));
        ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        (*(void * volatile *)((u8 *)temp_s0 + 0)) = D_802843E8;
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        (*(volatile u16 *)((u8 *)temp_s0 + 0x14)) = flags | 0xD;
        global_word = D_802843EC[0];
        page |= 0x80F0;
        (*(volatile s8 *)((u8 *)temp_s0 + 4)) = 0;
        (*(volatile s8 *)((u8 *)temp_s0 + 5)) = 0;
        (*(volatile s32 *)((u8 *)temp_s0 + 0xC)) = page;
        (*(volatile s32 *)((u8 *)temp_s0 + 8)) = global_word;
    }
}
/* MECHANISM: Symbol-typed hi/lo globals preserve the 0x20 frame and natural s2/s1/s0 held roles.
   A guarded v0 flags pin plus volatile tail fields and one scheduler fence reproduce the lhu/address/store order.
   A named 0x00800000 page kept live splits the late ori and fills the global-load delay. */
