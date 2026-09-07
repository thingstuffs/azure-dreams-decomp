#include "common.h"
#include "records/Rec_D_80082E80.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    s8 pad_00[0x2A];
    s16 field_2A;
} Arg0;

extern s32 D_800E296C[3];
extern u8 D_800DD0B8[8];
extern u8 D_800DCFB0[8];
extern s16 D_80083228[5];

extern void func_800B0F50(void *, s32, void *, void *);
extern void func_800B1768(s32, s32, s32, s32, s32, s32);
extern void func_80048A44(void *, u8, s32, s32);

typedef struct S_8008D024_0 {
    u8 pad_00[0xAC];
    void * unk_AC;
} S_8008D024_0;   /* temp_a3 in func_8008D024 */

typedef struct S_8008D024_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_8008D024_1;   /* temp_a0 in func_8008D024 */

typedef struct S_8008D024_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x6C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
    u8 pad_9C[0x68];
    void * unk_104;
    u8 pad_108[0x18];
    s16 unk_120;
} S_8008D024_2;   /* arg0 in func_8008D024 */


s32 func_8008D024(S_8008D024_2 *arg0, s32 arg1, Rec_D_80082E80 *arg2, s32 arg3, s32 arg4) {
    s32 temp_v1;
    s32 temp_offset;
    S_8008D024_1 *temp_a0;
    Arg0 *temp_s2;
    s8 *temp_a3;
    u8 *temp_a1;
    s16 temp_s3;

    temp_offset = (s32)(arg3 << 0x10) >> 0xE;
    temp_a3 = (s8 *)((s32)temp_offset + (s32)arg0);
    temp_s2 = arg0;
    temp_a0 = ((S_8008D024_0 *)temp_a3)->unk_AC;
    temp_s3 = arg4;
    if (temp_a0 != 0) {
        temp_v1 = temp_a0->unk_1C;
        if (temp_v1 & 0x20000) {
            if (!(temp_v1 & 0x80000)) {
                arg0->unk_104 = temp_a0;
                arg0->unk_9A = 0x27;
                arg0->unk_9B = 0;
                arg0->unk_8C = 0;
                func_800B0F50(temp_a0, arg1, arg2, temp_a3);
                if ((arg4 << 0x10) == 0) {
                    func_800B1768(0x21, 0xE0, 0x84, 0, 0, 0);
                    func_800B1768(0x22, 0xF2, 0x98, 1, 0, 2);
                    func_800B1768(0x24, 0xCE, 0x98, 2, 1, 4);
                    func_800B1768(0x23, 0xE0, 0xAC, 3, 1, 6);
                    D_800E296C[0] |= 0x2000;
                }
                if (arg0->unk_1C & 0x100000) {
                    temp_a1 = D_800DD0B8;
                } else {
                    temp_a1 = D_800DCFB0;
                }
                arg2->unk_2C.as_pu8 = temp_a1;
                func_80048A44(arg2, temp_a1[((s32)(D_80083228[0] + ((Arg0 *)temp_s2)->field_2A + 0x100) >> 9) & 7], 0, 1);
                arg0->unk_120 = temp_s3;
                return 1;
            }
        }
    }
    return 0;
}
