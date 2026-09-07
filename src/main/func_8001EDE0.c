#include "common.h"

typedef struct S_8001EDE0_0 {
    u8 pad_00[0x2C];
    s32 unk_2C;
    u8 pad_30[0x10];
    s32 unk_40;
} S_8001EDE0_0;   /* arg0 in func_8001EDE0 */

typedef struct S_8001EDE0_1 {
    u8 pad_00[0x4];
    s32 unk_04;
} S_8001EDE0_1;   /* var_s0 in func_8001EDE0 */


#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_80400908(void);
extern s32 func_80402084(s32, s32);
extern s32 func_80402154(s32, s32);
extern void func_80402214(void);
extern void func_8040334C(void *);
extern void func_80404688(s32);
extern void func_80405AB4(void *);
extern void func_80405C44(s32);
extern void func_80405E84(void) __attribute__((noreturn));
extern void func_80406368(void);
extern void func_80405A3C(void);

void func_8001EDE0(void *arg0) {
    s32 temp_a0;
    s32 var_s1;
    void *var_a0;
    void *var_s0;

    if (func_80402154(((S_8001EDE0_0 *)arg0)->unk_2C, 0x80010000) == 0) {
        var_a0 = (u8 *)arg0 - 0x20;
        goto tail;
    }
    *(s32 *)0x80010208 = 0;
    if (func_80402084((*(s32 *)((u8 *)arg0 + 0x28)), 0x80010000) == 0) {
        var_a0 = (u8 *)arg0 - 0x20;
        goto tail;
    }
    func_80405C44(0x80010000);
    var_s1 = 0;
    func_80402214();
    var_s0 = arg0;
    do {
        temp_a0 = ((S_8001EDE0_1 *)var_s0)->unk_04;
        var_s0 = (u8 *)var_s0 + 4;
        var_s1 += 1;
        func_80404688(temp_a0);
    } while (var_s1 < 5);
    func_80405AB4(arg0);
    func_80405E84();

tail:
    *(void (**)(void))((u8 *)arg0 + 0x34) = func_80406368;
    func_8040334C(var_a0);
    *(void * volatile *)((u8 *)arg0 - 0x10) = (void *)func_80405A3C;
    func_80400908();
    ((S_8001EDE0_0 *)arg0)->unk_40 = 0;
}
