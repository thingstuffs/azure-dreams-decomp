#include "common.h"

typedef struct S_81814A80_0 {
    u16 unk_00;
} S_81814A80_0;   /* state in func_81814A80; pointer addresses record offset 0x2 */

typedef struct S_81814A80_1 {
    s32 unk_00;
} S_81814A80_1;   /* &D_800814A0 in func_81814A80 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    unsigned char pad00[2];
    u16 unk02;
    unsigned char pad04[20];
    s16 unk18;
    s16 unk1a;
    u16 unk1c;
    unsigned char pad1e[0x3a];
    s32 unk58;
    s32 unk5c;
    s32 unk60;
    s32 unk64;
    s32 unk68;
    s32 unk6c;
} State;

typedef struct {
    unsigned char pad00[0x14];
    u16 unk14;
} Flags;

extern s16 D_80025338;
extern s32 D_800814A0;
extern void func_800478B8(void *arg0);
extern void func_80024374(void) __attribute__((noreturn));
extern void func_800243C8(void) __attribute__((noreturn));

void func_81814A80(State *state, s32 *sum, Flags *flags) {
    s32 i;
    register s32 compare ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    u16 next;

    state->unk02 = state->unk02 - 1;
    state->unk58 = state->unk58 + state->unk64;
    state->unk5c = state->unk5c + state->unk68;
    state->unk60 = state->unk60 + state->unk6c;
    sum[0] = sum[0] + state->unk58;
    sum[1] = sum[1] + state->unk5c;
    D_80025338 = 1;
    sum[2] = sum[2] + state->unk60;

    if (state->unk18 != 1) {
        if (state->unk18 < 2) {
            if (state->unk18 != 0) {
                func_800243C8();
            }
            goto mode0;
        }
        if (state->unk18 != 2) {
            func_800243C8();
        }
        goto mode2;
    }

    goto mode1;

mode0:
    func_800478B8(flags);
    func_800243C8();

mode1:
    if (state->unk1a > 0) {
        i = 0;
        ASM_KEEP(i);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        func_800478B8(flags);
        i = i + 1;
        compare = i < state->unk1a;
        if (compare) {
            func_80024374();
        }
    }
    goto done;

mode2:
        next = state->unk1c + 1;
        state->unk1c = next;
        if ((s16) next >= state->unk1a) {
            func_800478B8(flags);
            state->unk1c = 0;
        }

done:

    if ((s16) state->unk02 <= 0) {
        ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 = ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        ((S_81814A80_1 *)(&D_800814A0))->unk_00 = ((S_81814A80_1 *)(&D_800814A0))->unk_00 | 0x8000;
    }
    if (flags->unk14 & 0x8000) {
        ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 = ((S_81814A80_0 *)((u8 *)state - 0x2))->unk_00 | 0x8000;
        ((S_81814A80_1 *)(&D_800814A0))->unk_00 = ((S_81814A80_1 *)(&D_800814A0))->unk_00 | 0x8000;
    }
}
