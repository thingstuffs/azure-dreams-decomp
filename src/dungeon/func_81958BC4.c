#include "common.h"
#include "records/Rec_func_800243C4_arg1.h"


extern s32 func_8003DE58(void *, void *, void *, s32);
extern s32 func_80024ED4(void *);
extern void func_8004491C(void *, void *);

typedef struct CounterView {
    u16 value;
    u16 pad[5];
} CounterView;

typedef struct FlagsView {
    s32 value;
    s32 pad[2];
} FlagsView;

extern CounterView D_800281F8;
extern u8 D_80045340[];
extern FlagsView D_800814A0;


typedef struct S_800243C4_0_pre {
    u16 unk_00;
} S_800243C4_0_pre;   /* the 0x2 bytes before arg0 in func_800243C4, addressed as arg0[-1] */

typedef struct S_800243C4_0 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x18];
    u16 unk_24;
    u16 unk_26;
    union { s16 s; u16 u; } unk_28;   /* accessed as both */
    u8 pad_2A[0x2];
    union { s16 s; u16 u; } unk_2C;   /* accessed as both */
    s16 unk_2E;
} S_800243C4_0;   /* arg0 in func_800243C4 */

typedef struct S_800243C4_1 {
    u8 pad_00[0x8];
    void * unk_08;
    u8 pad_0C[0x8];
    u16 unk_14;
} S_800243C4_1;   /* temp_s0 in func_800243C4 */


typedef struct S_800243C4_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_800243C4_3;   /* temp_a0_2 in func_800243C4 */

typedef struct S_800243C4_4 {
    u8 pad_00[0xC];
    union { u8 u8; u32 u32; } unk_0C;   /* accessed as both */
} S_800243C4_4;   /* arg2 in func_800243C4 */

typedef struct S_800243C4_5 {
    u8 pad_00[0x8];
    void * unk_08;
    void * unk_0C;
} S_800243C4_5;   /* ((S_800243C4_0 *)arg0)->unk_08 in func_800243C4 */

/* Updates the effect's position, then brightens and fades its color. */
void func_800243C4(void *effect, Rec_func_800243C4_arg1 *position, S_800243C4_4 *color)
{
    s16 phase;
    u16 phase_value;
    S_800243C4_3 *base_position;
    S_800243C4_1 *source;

    D_800281F8.value = D_800281F8.value + 1;
    phase = ((S_800243C4_0 *)effect)->unk_2C.s;
    phase_value = ((S_800243C4_0 *)effect)->unk_2C.u;

    if (phase == 0) {
        source = ((S_800243C4_5 *)(((S_800243C4_0 *)effect)->unk_08))->unk_0C;
        if (((S_800243C4_0 *)effect)->unk_2E == 0) {
            if (func_8003DE58(source->unk_08, source,
                              (u8 *)effect + 0x24, 0) != 0) {
                ((S_800243C4_0 *)effect)->unk_2E = 1;
            } else if (source->unk_14 & 0x8000) {
                ((S_800243C4_0 *)effect)->unk_2E = 1;
                ((S_800243C4_0 *)effect)->unk_28.s = -0x40;
            }
            if (((S_800243C4_0 *)effect)->unk_2E == 0) {
                goto end;
            }
        }

        base_position = ((S_800243C4_5 *)(((S_800243C4_0 *)effect)->unk_08))->unk_08;
        position->unk_02 =
            base_position->unk_02 + ((S_800243C4_0 *)effect)->unk_24;
        position->unk_06 =
            base_position->unk_06 + ((S_800243C4_0 *)effect)->unk_26;
        position->unk_0A.as_s16 =
            base_position->unk_0A + ((S_800243C4_0 *)effect)->unk_28.u;
        if (func_80024ED4(position) != 0) {
            func_8004491C((u8 *)effect - 0x20, D_80045340);
            ((S_800243C4_0 *)effect)->unk_2C.u = ((S_800243C4_0 *)effect)->unk_2C.u + 1;
            return;
        }
    } else if (phase == 1) {
        if (color->unk_0C.u8 < 0xC0) {
            color->unk_0C.u32 += 0x202020;
            return;
        }
        ((S_800243C4_0 *)effect)->unk_2C.u = phase_value + 1;
        return;
    } else if (phase == 2) {
        color->unk_0C.u32 += 0xFFFBFBFC;
        if (color->unk_0C.u8 == 0) {
            ((S_800243C4_0_pre *)effect)[-1].unk_00 |= 0x8000;
            D_800814A0.value |= 0x8000;
        }
    }
end:
    ;
}
