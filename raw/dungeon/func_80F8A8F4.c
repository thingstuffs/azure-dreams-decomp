#include "common.h"

typedef s32 M2C_UNK;
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
    register s32 temp_v0 ASM_REG("$2");
    register void *call_arg ASM_REG("$4");
    register s32 pass_result ASM_REG("$5");
    s32 raw_result;
    s32 temp_v0_2;
    s32 field_60;
    u8 *table_base;

    M2C_FIELD(arg3, u8 *, 0x71) = (u8)(M2C_FIELD(arg3, u8 *, 0x71) & 0x7F);
    if (!(D_80083462 & 0x2000) && ((func_800A2BDC(arg3) << 0x10) == 0)) {
        M2C_FIELD(arg0, s32 *, 0x8C) = 0;
        M2C_FIELD(arg0, s8 *, 0x9A) = 0x17;
        M2C_FIELD(arg0, s8 *, 0x9B) = 0;
        if (M2C_FIELD(arg3, s32 *, 0x1C) & 0x400) {
            temp_v0 = M2C_FIELD(arg3, s32 *, 0x14);
            if (temp_v0 >= 0) {
                M2C_FIELD(arg3, s32 *, 0x14) = (s32)(temp_v0 | 0x80000000);
                M2C_FIELD(arg3, u16 *, 0x2A) = (u16)(M2C_FIELD(arg3, u16 *, 0x2A) + ((func_800A6D30() & 7) << 9));
            }
        }
        field_60 = func_800A04F0(arg3, M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25), (s16)M2C_FIELD(arg3, u16 *, 0x2A));
        table_base = D_80174B0C;
        M2C_FIELD(arg3, s32 *, 0x60) = field_60;
        M2C_FIELD(arg2, u8 **, 0x2C) = table_base;
        func_80047784(arg2, table_base[((s32)(D_80083228 + (s16)M2C_FIELD(arg3, u16 *, 0x2A) + 0x100) >> 9) & 7], 0);
        M2C_FIELD(arg3, u8 *, 0x6D) = (u8)(M2C_FIELD(arg3, u8 *, 0x6D) - 1);
        D_80083460.value = (u16)(D_80083460.value + 1);
        raw_result = func_800990FC();
        call_arg = arg3;
        ASM_KEEP(call_arg);
        pass_result = raw_result;
        ASM_KEEP(pass_result);
        temp_v0_2 = pass_result;
        func_80099290(func_80099194(&D_80170854, func_80099734(call_arg, pass_result)));
        func_800A5720(temp_v0_2);
    }
}
