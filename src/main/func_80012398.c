#include "common.h"



#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern void func_80020984(void);
extern s32 func_80021F18(s32, s32);
extern s32 func_80021FF0(s32, s32, s32);
extern void func_800220DC(void);
extern void func_800230F4(void *);
extern void func_80024298(s32);
extern void func_80024FFC(void *);
extern void func_8002519C(s32);
extern void func_80025358(s32, s32);
extern void func_80025444(void) __attribute__((noreturn));

extern u8 D_80024F7C[];

typedef struct S_80025398_0 {
    u8 pad_00[0x28];
    s32 unk_28;
    s32 unk_2C;
    u8 pad_30[0x10];
    s32 unk_40;
} S_80025398_0;   /* arg0 in func_80025398 */

typedef struct S_80025398_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_80025398_1;   /* var_s0 in func_80025398 */

void func_80025398(void *arg0) {
    s32 temp_a0;
    s32 var_s1;
    void *var_a0;
    void *var_s0;

    if (func_80021FF0(((S_80025398_0 *)arg0)->unk_2C, 0x80010000, 0) == 0) {
        var_a0 = (u8 *)arg0 - 0x20;
        goto tail;
    }
    func_80025358(0x80010000, ((S_80025398_0 *)arg0)->unk_28);
    if (func_80021F18(((S_80025398_0 *)arg0)->unk_28, 0x80010000) == 0) {
        var_a0 = (u8 *)arg0 - 0x20;
        goto tail;
    }
    func_8002519C(0x80010000);
    var_s1 = 0;
    func_800220DC();
    var_s0 = arg0;
    do {
        temp_a0 = ((S_80025398_1 *)var_s0)->unk_04;
        var_s0 = (u8 *)var_s0 + 4;
        var_s1 += 1;
        func_80024298(temp_a0);
    } while (var_s1 < 5);
    func_80024FFC(arg0);
    func_80025444();

tail:
    *(void (**)(void))((u8 *)arg0 + 0x34) = (void (*)(void))func_80024FFC;
    func_800230F4(var_a0);
    *(void * volatile *)((u8 *)arg0 - 0x10) = (void *)D_80024F7C;
    func_80020984();
    ((S_80025398_0 *)arg0)->unk_40 = 0;
}
