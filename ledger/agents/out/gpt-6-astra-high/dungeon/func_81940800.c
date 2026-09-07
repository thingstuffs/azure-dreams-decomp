#include "common.h"
typedef s32 M2C_UNK;

typedef struct S_81940800_0_pre {
    u16 unk_00;
} S_81940800_0_pre;   /* the 0x2 bytes before arg0 in BODY_NAME, addressed as arg0[-1] */

typedef struct S_81940800_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    s16 unk_2C;
    u8 pad_2E[0x4];
    s16 unk_32;
    u8 pad_34[0x2C];
    s32 unk_60;
} S_81940800_0;   /* arg0 in BODY_NAME */

typedef struct S_81940800_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    s8 unk_0D;
    s8 unk_0E;
} S_81940800_1;   /* arg2 in BODY_NAME */

typedef struct S_81940800_2 {
    u8 pad_00[0x46];
    s16 unk_46;
} S_81940800_2;   /* ((((S_81940800_0 *)arg0)->unk_32 * 2) + ((S_81940800_0 *)arg0)->unk_60) in BODY_NAME */

#ifdef __mips__
static const u32 bank_words[] __asm__("func_81940800") __attribute__((section(".text.func_81940800"), aligned(4))) = {
    0x80024B38,0x01400340,0x00400040,0x01800340,0x00400040,0x01C00340,0x00400040,0x01000380,
    0x00400040,0x01400380,0x00400040,0x01800380,0x00400040,0x01C00380,0x00400040,0x01000340,
    0x00400040,0x00000000,0x80024BA8,0x80024C4C,0x80024D60,0x800253A8,0x80025618,
};
__asm__(".globl func_81940800\n.type func_81940800,@function\n.size func_81940800,260\n");
#define BODY_NAME func_8194085C
#else
#define BODY_NAME func_81940800
#endif
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern s16 D_8002571C;
extern s32 D_800814A0;
void BODY_NAME(void *effect, void *unused, void *primitive)
#ifdef __mips__
    __attribute__((section(".text.func_81940800")))
#endif
;
/* Advance the effect fade and mark it finished when its countdown expires. */
void BODY_NAME(void *effect, void *unused, void *primitive) {
    s32 shade;
    u16 frames_left;

    frames_left = ((S_81940800_0 *)effect)->unk_2A - 1;
    shade = (s32)((s32)(frames_left << 0x10) >> 9) / (s16)((S_81940800_0 *)effect)->unk_2C;
    D_8002571C = 1;
    ((S_81940800_0 *)effect)->unk_2A = frames_left;
    ((S_81940800_1 *)primitive)->unk_0E = (s8)shade;
    ((S_81940800_1 *)primitive)->unk_0D = (s8)shade;
    ((S_81940800_1 *)primitive)->unk_0C = (s8)(shade + 0x10);
    if (((S_81940800_1 *)primitive)->unk_06 >= -6) {
        ((S_81940800_1 *)primitive)->unk_06 = (s16)((u16)((S_81940800_1 *)primitive)->unk_06 - 2);
    }
    if ((s16)((S_81940800_0 *)effect)->unk_2A <= 0) {
        ((S_81940800_2 *)(((((S_81940800_0 *)effect)->unk_32 * 2) + ((S_81940800_0 *)effect)->unk_60)))->unk_46 = 0;
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_81940800_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}
