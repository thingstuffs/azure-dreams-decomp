#include "common.h"
#include "shared/object_flags.h"
#include "m2c_compat.h"

typedef struct S_80024CD4_0_pre {
    u16 unk_00;
} S_80024CD4_0_pre;   /* the 0x2 bytes before arg0 in func_80024CD4, addressed as arg0[-1] */

typedef struct S_80024CD4_0 {
    u8 pad_00[0xA];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0xA];
    s16 unk_16;
    union { u16 s; u16 u; s16 p; } unk_18;   /* accessed as both */
    u16 unk_1A;
    u16 unk_1C;
    u8 pad_1E[0x4];
    s16 unk_22;
} S_80024CD4_0;   /* arg0 in func_80024CD4 */

typedef struct S_80024CD4_1 {
    u8 pad_00[0x6];
    union { u16 s; s16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x4];
    u8 unk_0C;
    u8 unk_0D;
    u8 unk_0E;
} S_80024CD4_1;   /* arg2 in func_80024CD4 */

typedef struct S_80024CD4_2 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
} S_80024CD4_2;   /* arg1 in func_80024CD4 */


typedef struct {
    u16 value;
    u8 pad[8];
} Counter;

typedef struct {
    s16 value;
    u8 pad[8];
} Flag;

void func_8002522C();
void func_800262AC();
extern Counter D_80026472;
extern Flag D_80026474;

/* Advance the effect state, update its ramp and color, and apply its transform. */
void func_80024CD4(void *effect, S_80024CD4_2 *transform, S_80024CD4_1 *visual) {
    s16 state;
    u16 rising_value;
    u16 ramp_or_red;
    u16 delay_left;
    u16 final_ramp;
    u16 decaying_value;
    void *call_transform;
    s32 base_value;

    D_80026472.value++;
    state = ((S_80024CD4_0 *)effect)->unk_0A.s;
    switch (state) {
    case 0:
        ramp_or_red = visual->unk_06.s + 0x80;
        visual->unk_06.s = ramp_or_red;
        if ((s16) ramp_or_red < 0x101) {
            break;
        }
        visual->unk_06.s = 0x100U;
        if (((S_80024CD4_0 *)effect)->unk_22 < 0x61) {
            call_transform = transform;
            base_value = ((S_80024CD4_0 *)effect)->unk_16;
            decaying_value = ((S_80024CD4_0 *)effect)->unk_18.s;
            decaying_value = (u16) (decaying_value - ((s32) (decaying_value << 0x10) >> 0x13));
            ((S_80024CD4_0 *)effect)->unk_18.u = decaying_value;
            rising_value = ((S_80024CD4_0 *)effect)->unk_1C;
            rising_value += 0x80;
            ((S_80024CD4_0 *)effect)->unk_1C = rising_value;
            func_8002522C(call_transform, base_value,
                ((S_80024CD4_0 *)effect)->unk_18.p, (s16) rising_value,
                effect - 0x20);
        }
        ((S_80024CD4_0 *)effect)->unk_0A.u++;
        if (((S_80024CD4_0 *)effect)->unk_22 == 0x6F) {
            D_80026474.value = 1;
        }
        break;
    case 1:
        if (D_80026474.value != 0) {
            visual->unk_06.u = -0x100;
            ((S_80024CD4_0 *)effect)->unk_1A = 0x10U;
            ((S_80024CD4_0 *)effect)->unk_0A.u++;
        }
        break;
    case 2:
        delay_left = ((S_80024CD4_0 *)effect)->unk_1A - 1;
        ((S_80024CD4_0 *)effect)->unk_1A = delay_left;
        if ((delay_left << 0x10) > 0) {
            break;
        }
        ((S_80024CD4_0 *)effect)->unk_0A.u++;
    case 3:
        final_ramp = visual->unk_06.s + 0x80;
        visual->unk_06.s = final_ramp;
        if ((s16) final_ramp >= 0) {
            ((S_80024CD4_0_pre *)effect)[-1].unk_00 |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
        break;
    default:
        break;
    }
    visual->unk_0C = 0x20;
    visual->unk_0D = 0xE0;
    visual->unk_0E = 0x40;
    func_800262AC(transform->unk_02, transform->unk_06, transform->unk_0A);
}
