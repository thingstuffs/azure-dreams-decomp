#include "common.h"

typedef s32 M2C_UNK;

typedef struct S_8008F6EC_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x5C];
    s16 unk_88;
} S_8008F6EC_0;   /* arg3 in func_8008F6EC */

typedef struct S_8008F6EC_1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
} S_8008F6EC_1;   /* arg1 in func_8008F6EC */

typedef struct S_8008F6EC_2 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
} S_8008F6EC_2;   /* arg2 in func_8008F6EC */

typedef struct S_8008F6EC_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    s8 unk_9A;
    s8 unk_9B;
} S_8008F6EC_3;   /* arg0 in func_8008F6EC */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

M2C_UNK func_80048A44();
extern void func_8008F7DC(void) __attribute__((noreturn));
M2C_UNK func_8009A66C();
M2C_UNK func_8009F644();
s32 func_800A44E0();
s32 func_800A7234();
extern u8 D_8006CCD8[];
extern u8 D_8006CCE8[];
extern u8 D_80081485;
extern s16 D_80083228;
extern u16 D_80083460[];
extern u8 D_800DD0D0[];

void func_8008F6EC(void *arg0, void *arg1, void *arg2, void *arg3) {
    s16 sp18;
    s16 sp1A;
    s16 sp1C;
    s32 temp_v1;
    register s32 var_s1 ASM_REG("$17");   /* MATCH pin: load-bearing for the whole function shape */

    var_s1 = 0;
    if (D_80081485 == 0x13) {
        var_s1 = (func_8009A66C(((S_8008F6EC_0 *)arg3)->unk_2A, arg2, arg3, 0x20) << 0x10) > 0;
        ASM_TAILSLOT_PIN_TIED(var_s1);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
        func_8008F7DC();
    }
    if ((func_800A44E0(((S_8008F6EC_1 *)arg1)->unk_02, ((S_8008F6EC_1 *)arg1)->unk_06, ((S_8008F6EC_0 *)arg3)->unk_88, ((S_8008F6EC_0 *)arg3)->unk_2A) << 0x10) == 0) {
        temp_v1 = ((u16) ((S_8008F6EC_0 *)arg3)->unk_2A >> 8) & 0xE;
        if ((func_800A7234((s16) (((S_8008F6EC_2 *)arg2)->unk_24 + *(u16 *)(D_8006CCD8 + temp_v1)), (s16) (((S_8008F6EC_2 *)arg2)->unk_25 + *(u16 *)(D_8006CCE8 + temp_v1)), ((S_8008F6EC_0 *)arg3)->unk_88, &sp18, &sp1A, &sp1C) << 0x10) != 0) {
            do { var_s1 = 1; } while (0);
        }
    }
    if (var_s1 != 0) {
        ((S_8008F6EC_3 *)arg0)->unk_9A = 0x1F;
        ((S_8008F6EC_3 *)arg0)->unk_9B = 0;
        ((S_8008F6EC_3 *)arg0)->unk_8C = 0;
        (*(u8 **)((u8 *)arg2 + 0x2C)) = D_800DD0D0;
        func_80048A44(arg2, D_800DD0D0[(((s32) (D_80083228 + ((S_8008F6EC_0 *)arg3)->unk_2A + 0x100)) >> 9) & 7], 0, 1);
        D_80083460[5] = D_80083460[5] + 1;
        func_8009F644(arg3, 0x28, 0, 0);
    }
}
