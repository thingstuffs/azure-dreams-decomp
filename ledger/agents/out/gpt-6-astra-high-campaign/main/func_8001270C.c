#include "common.h"

extern void func_800250E8(void *arg0, s32 arg1);
extern void func_800230A4(void *arg0, s32 arg1);

extern s32 D_8002593C;
extern s32 D_80024FAC;

#ifndef NON_MATCHING
register u8 *entry_ptr ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it changes the immediate-load split; the source shape that makes it unnecessary has not been found */
#endif

/* Select an entry handler and update the owning object's callback. */
void func_8002570C(void *state) {
#ifndef NON_MATCHING
    s32 entry_id;
    s32 entry_addr;
    void *owner;

    entry_ptr = (u8 *)0x80080000;
    __asm__ __volatile__("" : "=r"(entry_ptr) : "0"(entry_ptr));
    entry_id = *(s32 *)((u8 *)state + 0x28);
    entry_ptr += 0x3E98;
    entry_addr = entry_id << 7;
    entry_addr += (u32)entry_ptr;
    entry_ptr = (u8 *)*(u32 *)entry_addr;

    if (entry_ptr != 0) {
        *(s32 *)((u8 *)state + 0x2C) = entry_id;
        func_800250E8(state, entry_id);
        entry_ptr = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(entry_ptr) : "0"(entry_ptr));
        entry_ptr += 0x5584;
    } else {
        owner = (u8 *)state - 0x20;
        ASM_KEEP(owner);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        entry_ptr = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(entry_ptr) : "0"(entry_ptr));
        entry_ptr += 0x593C;
        *(u8 **)((u8 *)state + 0x34) = entry_ptr;
        func_800230A4(owner, entry_id);
        entry_ptr = (u8 *)0x80020000;
        __asm__ __volatile__("" : "=r"(entry_ptr) : "0"(entry_ptr));
        entry_ptr += 0x4FAC;
    }
    *(u8 **)((u8 *)state - 0x10) = entry_ptr;
#else
    extern s32 D_80083E98[];
    s32 entry_id = *(s32 *)((u8 *)state + 0x28);

    if (D_80083E98[entry_id * 32] != 0) {
        *(s32 *)((u8 *)state + 0x2C) = entry_id;
        func_800250E8(state, entry_id);
    } else {
        *(s32 **)((u8 *)state + 0x34) = &D_8002593C;
        func_800230A4((u8 *)state - 0x20, entry_id);
    }
    *(s32 **)((u8 *)state - 0x10) = &D_80024FAC;
#endif
}
