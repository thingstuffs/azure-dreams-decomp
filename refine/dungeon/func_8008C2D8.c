/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"

#define M2C_BREAK() 0

extern void func_80096088(void *, void *);
extern void func_80099F04(s32);
extern void func_80099F70(s32);
extern void func_800BCFBC(s32, s32);
extern u16 D_80083460[8];
extern s32 *D_800DD6B8[];

/* Runs a banked callback and advances the object state when it completes. */
void func_80091A38(void *object, void *unused_1, void *unused_2, void *context) {
    u8 *callback_data;
    u8 state;
    register s32 **callback_table ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    s32 *callback_row;
    u32 row_index;
    u32 entry_index;
    u32 callback_entry;
    u32 bank;
    register u32 address_mask ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    s32 (*callback)(s32, void *, s32, s32);

    state = *((u8 *)object + 0x9B);
    if (state == 0 || state == 16) {
        callback_data = *(u8 **)((u8 *)object + 0x110);
        callback_table = D_800DD6B8;
        address_mask = 0xFFFFFF;
        row_index = callback_data[1] - 1;
        entry_index = callback_data[0] - 1;
        callback_row = callback_table[row_index];
        callback_entry = (u32)callback_row[entry_index];
        bank = callback_entry >> 0x18;
        callback = (s32 (*)(s32, void *, s32, s32))((callback_entry & address_mask) | 0x80000000);
        if (bank != 0) {
            func_800BCFBC(--bank, address_mask);
        }
        if (callback((s32)context | 0xA0000000, callback_data, 0, 0) != 0) {
            *(void **)((u8 *)object + 0x110) = NULL;
            *((u8 *)object + 0x9B) += 1;
            return;
        }
        return;
    }
    if (state == 1) {
        func_80099F70(*(s32 *)((u8 *)context + 0x5C));
        func_80099F04(*(s32 *)((u8 *)context + 0x5C));
        D_80083460[1] |= 0x812;
        func_80096088(object, context);
    }
}
