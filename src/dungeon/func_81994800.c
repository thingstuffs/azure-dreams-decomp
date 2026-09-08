#include "common.h"
#include "records/Rec_D_800E3D7C.h"
typedef s32 M2C_UNK;

typedef struct S_81994800_0_pre {
    u16 unk_00;
} S_81994800_0_pre;   /* the 0x2 bytes before arg0 in BODY_NAME, addressed as arg0[-1] */


typedef struct S_81994800_1 {
    u8 pad_00[0x6];
    s16 unk_06;
    u8 pad_08[0x4];
    s8 unk_0C;
    u8 unk_0D;
    s8 unk_0E;
} S_81994800_1;   /* arg2 in BODY_NAME */

typedef struct S_81994800_2 {
    u8 pad_00[0x46];
    s16 unk_46;
} S_81994800_2;   /* ((((Rec_D_800E3D7C *)arg0)->unk_32 * 2) + ((Rec_D_800E3D7C *)arg0)->unk_60.as_s32) in BODY_NAME */

#ifdef __mips__
static const u32 bank_words[] __asm__("func_81994800") __attribute__((section(".text.func_81994800"), aligned(4))) = {
    0x8002458C,0x01400340,0x00400040,0x01800340,0x00400040,0x01C00340,0x00400040,0x01000380,
    0x00400040,0x01400380,0x00400040,0x01800380,0x00400040,0x01C00380,0x00400040,0x01000340,
    0x00400040,0x00000000,0x800245F0,0x80024674,0x8002478C,0x80024D98,0x8002512C,
};
__asm__(".globl func_81994800\n.type func_81994800,@function\n.size func_81994800,260\n");
#define BODY_NAME func_8199485C
#else
#define BODY_NAME func_81994800
#endif
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
extern s16 D_80025384;
extern s32 D_800814A0;
void BODY_NAME(void *arg0, void *arg1, void *arg2)
#ifdef __mips__
    __attribute__((section(".text.func_81994800")))
#endif
;
/* Advance the effect countdown, update its parameters, and flag completion. */
void BODY_NAME(void *effect, void *unused_context, void *effect_params) {
    s32 scale;
    u16 ticks_left;

    ticks_left = ((Rec_D_800E3D7C *)effect)->unk_2A.as_u16 - 1;
    scale = (s32)((s32)(ticks_left << 0x10) >> 9) / (s16)((Rec_D_800E3D7C *)effect)->unk_2C;
    D_80025384 = 1;
    ((Rec_D_800E3D7C *)effect)->unk_2A.as_u16 = ticks_left;
    ((S_81994800_1 *)effect_params)->unk_0D = (u8)(((S_81994800_1 *)effect_params)->unk_0D - 4);
    ((S_81994800_1 *)effect_params)->unk_0E = (s8)scale;
    ((S_81994800_1 *)effect_params)->unk_0C = (s8)scale;
    if (((S_81994800_1 *)effect_params)->unk_06 >= -6) {
        ((S_81994800_1 *)effect_params)->unk_06 = (s16)((u16)((S_81994800_1 *)effect_params)->unk_06 - 2);
    }
    if ((s16)((Rec_D_800E3D7C *)effect)->unk_2A.as_u16 <= 0) {
        ((S_81994800_2 *)(((((Rec_D_800E3D7C *)effect)->unk_32 * 2) + ((Rec_D_800E3D7C *)effect)->unk_60.as_s32)))->unk_46 = 0;
        (*(u16 *)((u8 *)effect + -2)) = (u16)(((S_81994800_0_pre *)effect)[-1].unk_00 | 0x8000);
        D_800814A0 = D_800814A0 | 0x8000;
    }
}
