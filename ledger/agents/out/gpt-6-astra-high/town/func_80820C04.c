#include "common.h"

typedef struct S_80023404_0 {
    u8 pad_00[0x4];
    union { s16 s; u16 u; } unk_04;   /* accessed as both */
    u16 unk_06;
    s16 unk_08;
    s16 unk_0A;
    union { s16 s; u16 u; } unk_0C;   /* accessed as both */
    union { s16 s; u16 u; } unk_0E;   /* accessed as both */
} S_80023404_0;   /* arg0 in func_80023404 */



extern void *D_80020264[5];
extern void func_80023578(s16, s16, s16);

/* Updates scrolling through 12 positions, accelerating or settling according to state. */
void func_80023404(S_80023404_0 *scroll)
{
    static void *const switch_labels[] = {
        &&case_0,
        &&case_1,
        &&case_2,
        &&case_3,
        &&case_4
    };
    s32 state;
    state = scroll->unk_04.s;
    if ((u32)state >= 5) {
        goto done;
    }
    (void)switch_labels;
    goto *D_80020264[state];

case_0:
    scroll->unk_0E.s = 0;
    scroll->unk_0C.s = 0;
    func_80023578(scroll->unk_08,
                  scroll->unk_0A,
                  scroll->unk_0E.s);
    scroll->unk_04.s = 1;
    goto done;

case_2:
    {
        u16 tick;
        tick = scroll->unk_06;
        scroll->unk_06 = tick + 1;
        if ((tick & 1) != 0) {
            if (scroll->unk_0C.s < 12) {
                scroll->unk_0C.s++;
            } else {
                scroll->unk_04.s = 3;
            }
        }
    }

case_3:
    scroll->unk_0E.u = scroll->unk_0E.u - scroll->unk_0C.u;
    if ((s16)scroll->unk_0E.u < 0) {
        do {
            scroll->unk_0E.u += 32;
            scroll->unk_0A = (scroll->unk_0A + 1) % 12;
        } while ((s16)scroll->unk_0E.u < 0);
    }
    goto common_call;

case_4:
    scroll->unk_0E.u -= (s32)(scroll->unk_0E.u << 16) >> 18;
    if ((s16)scroll->unk_0E.u < 4) {
        scroll->unk_0E.u = 0;
        scroll->unk_04.u = 0;
    }
common_call:
    func_80023578(scroll->unk_08,
                  scroll->unk_0A,
                  scroll->unk_0E.s);
    goto done;

case_1:
done:
    return;
}
