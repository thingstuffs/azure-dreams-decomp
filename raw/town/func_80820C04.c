#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void *D_80020264[5];
extern void func_80023578(s16, s16, s16);

void func_80023404(void *arg0)
{
    static void *const switch_labels[] = {
        &&case_0,
        &&case_1,
        &&case_2,
        &&case_3,
        &&case_4
    };
    s32 state;
    state = FIELD(arg0, s16, 4);
    if ((u32)state >= 5) {
        goto done;
    }
    (void)switch_labels;
    goto *D_80020264[state];

case_0:
    FIELD(arg0, s16, 0xE) = 0;
    FIELD(arg0, s16, 0xC) = 0;
    func_80023578(FIELD(arg0, s16, 8),
                  FIELD(arg0, s16, 0xA),
                  FIELD(arg0, s16, 0xE));
    FIELD(arg0, s16, 4) = 1;
    goto done;

case_2:
    {
        u16 count;
        count = FIELD(arg0, u16, 6);
        FIELD(arg0, u16, 6) = count + 1;
        if ((count & 1) != 0) {
        if (FIELD(arg0, s16, 0xC) < 12) {
            FIELD(arg0, s16, 0xC)++;
        } else {
            FIELD(arg0, s16, 4) = 3;
        }
        }
    }

case_3:
    FIELD(arg0, u16, 0xE) =
        FIELD(arg0, u16, 0xE) - FIELD(arg0, u16, 0xC);
    if ((s16)FIELD(arg0, u16, 0xE) < 0) {
        do {
            FIELD(arg0, u16, 0xE) += 32;
            FIELD(arg0, s16, 0xA) =
                (FIELD(arg0, s16, 0xA) + 1) % 12;
        } while ((s16)FIELD(arg0, u16, 0xE) < 0);
    }
    goto common_call;

case_4:
    FIELD(arg0, u16, 0xE) -=
        (s32)(FIELD(arg0, u16, 0xE) << 16) >> 18;
    if ((s16)FIELD(arg0, u16, 0xE) < 4) {
        FIELD(arg0, u16, 0xE) = 0;
        FIELD(arg0, u16, 4) = 0;
    }
common_call:
    func_80023578(FIELD(arg0, s16, 8),
                  FIELD(arg0, s16, 0xA),
                  FIELD(arg0, s16, 0xE));
    goto done;

case_1:
done:
    return;
}
