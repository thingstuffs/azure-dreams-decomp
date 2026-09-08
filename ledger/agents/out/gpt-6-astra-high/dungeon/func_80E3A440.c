#include "common.h"
#include "records/Rec_D_800E3D7C.h"


extern void func_80047784();
extern s32 func_800A2BDC();

extern s16 D_80083228;
extern u8 D_80083460[12];
extern u8 D_80176670[16];


typedef struct S_80173C40_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_80173C40_0;   /* state in func_80173C40 */


typedef struct S_80173C40_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
    s8 unk_9B;
} S_80173C40_2;   /* arg0 in func_80173C40 */

/* Initialize the entity action and select its directional animation when ready. */
void func_80173C40(void *action, void *unused, void *animation, void *entity) {
    u8 *state = D_80083460;

    if (((S_80173C40_0 *)state)->unk_02 & 0x2000) {
        ((Rec_D_800E3D7C *)entity)->unk_71.as_u8 &= 0x7F;
        return;
    }

    if ((func_800A2BDC(entity) << 16) == 0) {
        s32 direction;

        ((S_80173C40_2 *)action)->unk_9A = 0x17;
        ((S_80173C40_2 *)action)->unk_9B = 0;
        ((S_80173C40_2 *)action)->unk_8C = 0;
        *(u8 **)((u8 *)animation + 0x2C) = D_80176670;

        direction = ((D_80083228 + ((Rec_D_800E3D7C *)entity)->unk_2A.as_s16 + 0x100) >> 9) & 7;
        func_80047784(animation, D_80176670[direction], 0);

        ((S_80173C40_2 *)action)->unk_96 = 0;
        ((Rec_D_800E3D7C *)entity)->unk_1C.as_s32 |= 0x10000000;
        ((S_80173C40_0 *)state)->unk_0A++;
        ((Rec_D_800E3D7C *)entity)->unk_44.at02_u16.v &= 0x7FFF;
    }
}
