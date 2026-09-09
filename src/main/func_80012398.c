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

/* Process five context entries if checks pass, or schedule the fallback callback. */
void func_80025398(void *context) {
    s32 entry_value;
    s32 entry_count;
    void *owner;
    void *entry_cursor;

    if (func_80021FF0(((S_80025398_0 *)context)->unk_2C, 0x80010000, 0) == 0) {
        owner = (u8 *)context - 0x20;
        goto tail;
    }
    func_80025358(0x80010000, ((S_80025398_0 *)context)->unk_28);
    if (func_80021F18(((S_80025398_0 *)context)->unk_28, 0x80010000) == 0) {
        owner = (u8 *)context - 0x20;
        goto tail;
    }
    func_8002519C(0x80010000);
    entry_count = 0;
    func_800220DC();
    entry_cursor = context;
    do {
        entry_value = ((S_80025398_1 *)entry_cursor)->unk_04;
        entry_cursor = (u8 *)entry_cursor + 4;
        entry_count += 1;
        func_80024298(entry_value);
    } while (entry_count < 5);
    func_80024FFC(context);
    goto finish;

tail:
    *(void (**)(void))((u8 *)context + 0x34) = (void (*)(void))func_80024FFC;
    func_800230F4(owner);
    *(void * volatile *)((u8 *)context - 0x10) = (void *)D_80024F7C;
finish:
    func_80020984();
    ((S_80025398_0 *)context)->unk_40 = 0;
}
