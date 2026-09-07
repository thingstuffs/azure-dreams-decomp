#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

typedef struct {
    s32 words[6];
} Copy24;

extern void func_800211C4(void *, void *, void *);
extern void func_80047784(void *, s32, s32);
extern void func_800478B8(void *);

extern void *D_800201A0[];
extern s32 D_80081458[];
extern s16 D_80083228;
extern u8 D_80083220[];
extern s32 D_800834B8;
extern u8 D_80083780[];
extern u8 D_800D2398[];
extern u8 D_800D23A0[];

void func_80023A00(void *arg0, void *arg1, void *arg2)
{
    register u8 *caller_obj ASM_REG("$20") = arg0;
    u8 *dst = arg1;
    register u8 *entity ASM_REG("$18") = arg2;
    u8 *state_base = (u8 *)&D_800834B8;
    s32 state;
    s32 case1_magnitude;
    s32 magnitude;
    register s32 limit ASM_REG("$2");
    u8 *table;
    static void *const switch_keep[] = {
        &&case_0, &&case_1, &&case_2, &&case_3, &&case_4
    };

    func_800478B8(entity);
    *(Copy24 *)dst = *(Copy24 *)D_80083780;
    FIELD(arg0, u16, 0x2A) =
        (0x1400 - FIELD(state_base, u16, 0x10)) & 0xFFF;

    state = FIELD(arg0, s16, 0x18);
    if ((u32)state >= 5) {
        goto common;
    }
    (void)switch_keep;
    goto *D_800201A0[state];

case_0:
    FIELD(arg0, u16, 0x18)++;
    goto done;

case_1:
    case1_magnitude = D_80081458[0];
    FIELD(entity, void *, 0x2C) = D_800D23A0;
    FIELD(entity, s32, 0x28) = case1_magnitude;
    func_80047784(entity,
        D_800D23A0[((D_80083228 +
            FIELD(caller_obj, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x18)++;
    if (FIELD(state_base, s16, 8) != 2) {
        goto common;
    }
    FIELD(entity, void *, 0x2C) = D_800D2398;
    func_80047784(entity,
        D_800D2398[((*(s16 *)(D_80083220 + 8) +
            FIELD(caller_obj, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x18)++;
    goto common;

case_2:
    magnitude = FIELD(state_base, s32, 0x48);
    limit = 0xFFFF;
    ASM_KEEP(limit);
    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (limit < magnitude) {
        goto common;
    }
    FIELD(entity, void *, 0x2C) = D_800D23A0;
    func_80047784(entity,
        D_800D23A0[((D_80083228 + FIELD(caller_obj, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x18)++;
    goto common;

case_3:
    magnitude = FIELD(state_base, s32, 0x48);
    limit = 0xFFFF;
    ASM_KEEP(limit);
    if (magnitude < 0) {
        magnitude = -magnitude;
    }
    if (limit >= magnitude) {
        goto common;
    }
    table = D_800D2398;
    FIELD(entity, void *, 0x2C) = table;
    func_80047784(entity,
        table[((D_80083228 + FIELD(caller_obj, s16, 0x2A) + 0x100) >> 9) & 7],
        0);
    FIELD(arg0, u16, 0x18)--;
    goto common;

case_4:
common:
    if (FIELD(arg0, s16, 0x18) != 0) {
        func_800211C4(caller_obj, arg0, entity);
    }

done:
    return;
}
