#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_801740F4_0 {
    u8 pad_00[0x14];
    s32 unk_14;
    u8 pad_18[0x4];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x34];
    s32 unk_60;
    u8 pad_64[0x9];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
} S_801740F4_0;   /* arg3 in func_801740F4 */

typedef struct S_801740F4_1 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_801740F4_1;   /* arg0 in func_801740F4 */

typedef struct S_801740F4_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_801740F4_2;   /* arg2 in func_801740F4 */

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

typedef struct {
    u8 pad[10];
    u16 value;
} CounterState;

extern M2C_UNK func_80047784();
extern s32 func_800990FC(void);
extern s32 func_80099194();
extern s32 func_80099290();
extern s32 func_80099734();
extern s32 func_800A04F0();
extern s32 func_800A2BDC();
extern s32 func_800A5720();
extern s32 func_800A6D30(void);

extern s16 D_80083228;
extern u16 D_80083462;
extern CounterState D_80083460;
extern M2C_UNK D_80170854;
extern u8 D_80174B0C[];

void func_801740F4(void *arg0, void *arg1, void *arg2, void *arg3) {
    register s32 temp_v0 ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    void *call_arg;
    register s32 pass_result ASM_REG("$5");   /* MATCH pin: retail register colouring depends on it */
    s32 raw_result;
    s32 temp_v0_2;
    s32 field_60;
    u8 *table_base;

    ((S_801740F4_0 *)arg3)->unk_71 = (u8)(((S_801740F4_0 *)arg3)->unk_71 & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        ((S_801740F4_1 *)arg0)->unk_8C = 0;
        ((S_801740F4_1 *)arg0)->unk_9A = 0x17;
        ((S_801740F4_1 *)arg0)->unk_9B = 0;
        if (((S_801740F4_0 *)arg3)->unk_1C & 0x400) {
            temp_v0 = ((S_801740F4_0 *)arg3)->unk_14;
            if (temp_v0 >= 0) {
                ((S_801740F4_0 *)arg3)->unk_14 = (s32)(temp_v0 | 0x80000000);
                ((S_801740F4_0 *)arg3)->unk_2A = (u16)(((S_801740F4_0 *)arg3)->unk_2A + ((func_800A6D30() & 7) << 9));
            }
        }
        field_60 = func_800A04F0(arg3, ((S_801740F4_2 *)arg2)->unk_24, ((S_801740F4_2 *)arg2)->unk_25, (s16)((S_801740F4_0 *)arg3)->unk_2A);
        table_base = D_80174B0C;
        ((S_801740F4_0 *)arg3)->unk_60 = field_60;
        (*(u8 **)((u8 *)arg2 + 0x2C)) = table_base;
        func_80047784(arg2, table_base[((s32)(D_80083228 + (s16)((S_801740F4_0 *)arg3)->unk_2A + 0x100) >> 9) & 7], 0);
        ((S_801740F4_0 *)arg3)->unk_6D = (u8)(((S_801740F4_0 *)arg3)->unk_6D - 1);
        D_80083460.value = (u16)(D_80083460.value + 1);
        raw_result = func_800990FC();
        call_arg = arg3;
        ASM_KEEP(call_arg);   /* MATCH pin: retail schedule: same instructions, different order without it */
        pass_result = raw_result;
        ASM_KEEP(pass_result);   /* MATCH pin: retail address form (%hi/%lo vs base+offset) depends on it */
        temp_v0_2 = pass_result;
        func_80099290(func_80099194(&D_80170854, func_80099734(call_arg, pass_result)));
        func_800A5720(temp_v0_2);
    }
}
