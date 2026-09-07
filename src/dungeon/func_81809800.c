#include "common.h"
#include "m2c_compat.h"

typedef struct S_81809800_0 {
    u8 pad_00[0x26];
    s16 unk_26;
} S_81809800_0;   /* temp_v1 in BODY_NAME */

typedef struct S_81809800_1 {
    u8 pad_00[0xC];
    void * unk_0C;
} S_81809800_1;   /* ((index * 4) + temp_v1) in BODY_NAME */

typedef struct S_81809800_2 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_81809800_2;   /* arg1 in BODY_NAME */

typedef struct S_81809800_3 {
    u8 pad_00[0x8];
    void * unk_08;
} S_81809800_3;   /* temp_a2_base in BODY_NAME */

typedef struct S_81809800_4 {
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_04;   /* overlapping accesses */
} S_81809800_4;   /* temp_a2 in BODY_NAME */

typedef struct S_81809800_5 {
    u8 pad_00[0xA];
    s16 unk_0A;
} S_81809800_5;   /* arg0 in BODY_NAME */

typedef struct S_81809800_6 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_81809800_6;   /* arg2 in BODY_NAME */


/* cfail-repair: tf7-phase1-cache-v3 */
extern s16 D_8002715C[5];
extern s16 D_80027156;
extern void func_800478B8(void *, s16, void *, void *);

#ifdef __mips__
void func_80025000(void *, void *, void *);
static const u32 prefix_words[] __asm__("func_80025000")
    __attribute__((section(".text.func_80025000"), aligned(4))) = {
    0x8002527C, 0x800252C0, 0x800253B4, 0x800257F0, 0x80025844,
};
__asm__(
    ".globl func_80025000\n"
    ".type func_80025000,@function\n"
    ".size func_80025000,368\n");
#define BODY_NAME func_80025014
#else
#define BODY_NAME func_80025000
#endif

void BODY_NAME(void *arg0, void *arg1, void *arg2)
    __attribute__((section(".text.func_80025000")));
void BODY_NAME(void *arg0, void *arg1, void *arg2) {
    s16 temp_a0;
    s32 temp_a1;
    s16 temp_v0;
    s32 temp_v1_2;
    s32 temp_v1_3;
    void *temp_a2;
    void *temp_a2_base;
    void *temp_v1;
    s32 arg1_y;
    s32 index;
    s16 *counter;
    s16 gate;
    u16 remaining;

    temp_v1 = (*(void **)((u8 *)arg0 + 0));
    index = ((S_81809800_0 *)temp_v1)->unk_26;
    counter = D_8002715C;
    temp_a2_base = ((S_81809800_1 *)(((index * 4) + temp_v1)))->unk_0C;
    arg1_y = ((S_81809800_2 *)arg1)->unk_00.at02.v;
    temp_a2 = ((S_81809800_3 *)temp_a2_base)->unk_08;
    temp_a1 = ((S_81809800_4 *)temp_a2)->unk_00.at02.v;
    counter[0] = (s16) ((u16) counter[0] + 1);
    if ((temp_a1 != arg1_y) || (((S_81809800_4 *)temp_a2)->unk_04.at02.v != ((S_81809800_2 *)arg1)->unk_04.at02.v)) {
        ((S_81809800_5 *)arg0)->unk_0A = 2;
    }
    temp_a0 = ((S_81809800_5 *)arg0)->unk_0A;
    if (temp_a0 != 0) {
        ((S_81809800_2 *)arg1)->unk_00.at00.v = (s32) (((S_81809800_2 *)arg1)->unk_00.at00.v + ((s32) (((S_81809800_4 *)temp_a2)->unk_00.at00.v - ((S_81809800_2 *)arg1)->unk_00.at00.v) / temp_a0));
        ((S_81809800_2 *)arg1)->unk_04.at00.v = (s32) (((S_81809800_2 *)arg1)->unk_04.at00.v + ((s32) (((S_81809800_4 *)temp_a2)->unk_04.at00.v - ((S_81809800_2 *)arg1)->unk_04.at00.v) / (s16) ((S_81809800_5 *)arg0)->unk_0A));
        temp_v0 = (u16) ((S_81809800_5 *)arg0)->unk_0A - 1;
        ((S_81809800_5 *)arg0)->unk_0A = temp_v0;
        if ((temp_v0 << 0x10) <= 0) {
            ((S_81809800_2 *)arg1)->unk_00.at02.v = (s16) (u16) ((S_81809800_4 *)temp_a2)->unk_00.at02.v;
            ((S_81809800_2 *)arg1)->unk_04.at02.v = (s16) (u16) ((S_81809800_4 *)temp_a2)->unk_04.at02.v;
            ((S_81809800_5 *)arg0)->unk_0A = 0;
        }
    }
    func_800478B8(arg2, temp_a1, temp_a2, arg1);
    gate = D_80027156;
    remaining = *(u16 *)&D_80027156;
    if (gate != 0) {
        *(u16 *)&D_80027156 = (u16) (remaining - 1);
    }
    if ((*(u16 *)&D_80027156) & 1) {
        ((S_81809800_6 *)arg2)->unk_14 = (u16) (((S_81809800_6 *)arg2)->unk_14 | 0x80);
    } else {
        ((S_81809800_6 *)arg2)->unk_14 = (u16) (((S_81809800_6 *)arg2)->unk_14 & 0xFF7F);
    }
}
