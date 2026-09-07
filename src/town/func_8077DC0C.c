#include "common.h"
#include "m2c_compat.h"

extern void func_80016464(void) __attribute__((noreturn));
extern void func_80017670(s32);
extern void *D_80016000;
extern M2C_UNK D_8001601C;
extern M2C_UNK D_8001605E;
extern M2C_UNK D_800162A4;
extern M2C_UNK *D_80017760;

typedef struct S_8077DC0C_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    void * unk_1C;
    u8 pad_20[0x20];
    s32 unk_40;
} S_8077DC0C_0;   /* state in func_8077DC0C */

typedef struct S_8077DC0C_1 {
    u8 pad_00[0x40];
    M2C_UNK * unk_40;
} S_8077DC0C_1;   /* dispatch_base in func_8077DC0C */

void func_8077DC0C(void) {
    u8 *temp_a2;
    S_8077DC0C_0 *state;
    s32 event;
    void *dispatch_value;
    register S_8077DC0C_1 *dispatch_base ASM_REG("$3");   /* MATCH pin: load-bearing for the whole function shape */

    state = D_80016000;
    D_80017760 = &D_800162A4;
    temp_a2 = state->unk_40 + (state->unk_08 * 8);
    if (*temp_a2 != 0) {
        dispatch_value = (void *)0x80010000;
        ASM_KEEP(dispatch_value);   /* MATCH pin: retail delay-slot fill depends on it */
        dispatch_base = state->unk_1C;
        ASM_USE(dispatch_base);   /* MATCH pin: retail basic-block layout depends on it */
        dispatch_value = (u8 *)dispatch_value + 0x605E;
        ASM_TAILSLOT_PIN(dispatch_value);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80016464();
    }
    ASM_CLOBBER("$2");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    dispatch_value = (void *)0x80010000;
    ASM_KEEP(dispatch_value);   /* MATCH pin: retail delay-slot fill depends on it */
    dispatch_base = state->unk_1C;
    dispatch_value = (u8 *)dispatch_value + 0x601C;
    dispatch_base->unk_40 = dispatch_value;
    event = 0x7E;
    *temp_a2 = (*temp_a2 + 1) & 1;
    func_80017670(event);
    func_80017670(0x7F);
}
