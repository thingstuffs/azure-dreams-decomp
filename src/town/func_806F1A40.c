#include "common.h"
#include "m2c_compat.h"
#include "records/Rec_D_80016000.h"


typedef struct S_806F1A40_1 {
    u8 pad_00[0x334];
    s32 (*unk_334)(M2C_UNK);
} S_806F1A40_1;   /* ((Rec_D_80016000 *)D_80016000)->unk_20 in func_806F1A40 */




void func_80016290(void) __attribute__((noreturn)); /* extern */
M2C_UNK func_80017744();                     /* extern */
M2C_UNK func_800177BC();                     /* extern */
extern Rec_D_80016000 *D_80016000;
extern M2C_UNK D_80017A00;
extern M2C_UNK *D_80017A98;


void func_806F1A40(void) {
    if (((S_806F1A40_1 *)(D_80016000->unk_20))->unk_334(0) != 5) {
        register u32 pagebase ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */

        func_80017744(0xBE9);
        pagebase = 0x80010000;
        ASM_PAGEBASE_PIN(pagebase);   /* MATCH pin: retail delay-slot contents depend on it */
        func_80016290();
        return;
    }
    func_800177BC(0xBE9);
    D_80017A98 = &D_80017A00;
}

/* MECHANISM: Direct global chaining preserves the ra-only 0x18 frame and callback load order.
   Marking func_80016290 noreturn selects the retail tail-jump CFG and removes three extra words.
   A guarded $v1 page-base carrier fills that tail jump's dead lui 0x8001 delay slot. */
