#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_8009402C_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0xF8];
    void * unk_124;
} S_8009402C_0;   /* arg0 in func_8009402C */


typedef struct S_8009402C_2 {
    u8 pad_00[0x13];
    s8 unk_13;
} S_8009402C_2;   /* temp_v0_2 in func_8009402C */

typedef struct S_8009402C_3 {
    u8 pad_00[0x8A];
    s16 unk_8A;
} S_8009402C_3;   /* tail_base in func_8009402C */

typedef struct S_8009402C_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8009402C_4;   /* temp_v0_3 in func_8009402C */

typedef struct S_8009402C_5 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8009402C_5;   /* ((((S_8009402C_3 *)tail_base)->unk_8A * 4) + arg0) in func_8009402C */

typedef struct DungeonSlot {
    u8 pad_00[0x1C];
    u32 flags;
} DungeonSlot;

s32 func_800941D8();
M2C_UNK func_80094E34();
M2C_UNK func_8009A21C();
M2C_UNK func_8009A3D0();
s32 func_8009B88C();
extern s8 D_8006CCD8;
extern s8 D_8006CCE8;
extern DungeonSlot *D_800E3DF0[];

s32 func_8009402C(void *arg0, void *arg1, void *arg2, s16 *arg3, s16 *arg4, void *arg5) {
    register s32 shifted_result ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s16 temp_a2;
    s16 temp_s0;
    s16 temp_s1;
    s16 temp_v0;
    s32 temp_s0_2;
    s32 temp_v1;
    s32 var_v0;
    s16 *coord_arg;
    void *tail_base;
    void *temp_v0_2;
    void *temp_v0_3;

    tail_base = arg0;
    coord_arg = arg3;
    if (arg5 != NULL) {
        var_v0 = 3;
        ASM_CLOBBER("$7");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        if (!(D_800E3DF0[(*(u8 *)((u8 *)arg5 + 3)) & 0x1F]->flags & 0x04000000)) {
            temp_v1 = ((u16) ((S_8009402C_0 *)arg0)->unk_2A >> 8) & 0xE;
            temp_v0 = ((Rec_D_80082E80 *)arg2)->unk_24 + *(u16 *)(&D_8006CCD8 + temp_v1);
            temp_a2 = ((Rec_D_80082E80 *)arg2)->unk_25 + *(u16 *)(&D_8006CCE8 + temp_v1);
            if (((func_8009B88C(0, temp_v0, temp_a2, coord_arg, arg4) << 0x10) == 0) || ((((S_8009402C_0 *)arg0)->unk_1C & 0x100000) && (temp_v0_2 = ((S_8009402C_0 *)arg0)->unk_124, (temp_v0_2 != NULL)) && (((S_8009402C_2 *)temp_v0_2)->unk_13 > 0) && (temp_s0 = *coord_arg, temp_s1 = *arg4, func_8009A21C(temp_s0, temp_s1, 0x8000), temp_s0_2 = func_8009B88C(0, temp_v0, temp_a2, coord_arg, arg4), func_8009A3D0(temp_s0, temp_s1, 0x8000), (shifted_result = temp_s0_2 << 0x10, shifted_result == 0)))) {
                func_800941D8();
                return 1;
            }
            goto block_9;
        }
        return var_v0;
    }
block_9:
    temp_v0_3 = ((S_8009402C_5 *)(((((S_8009402C_3 *)tail_base)->unk_8A * 4) + arg0)))->unk_AC;
    if ((temp_v0_3 != NULL) && !(((S_8009402C_4 *)temp_v0_3)->unk_1C & 0x20000)) {
        return 2;
    }
    func_80094E34();
    return 0;
}
