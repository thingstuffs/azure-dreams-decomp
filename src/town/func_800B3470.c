#include "common.h"

typedef struct S_800B0BD0_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    u8 pad_14[0xB8];
    s32 unk_CC;
} S_800B0BD0_0;   /* held in func_800B0BD0 */

typedef struct S_800B0BD0_1 {
    u8 pad_00[0x24];
    s32 unk_24;
} S_800B0BD0_1;   /* scratch in func_800B0BD0 */

#ifdef NON_MATCHING
#define LOCAL_ASM_REG(reg)
#define LOCAL_ASM_KEEP(var) ((void)0)
#else
#define LOCAL_ASM_REG(reg) asm(reg)
#define LOCAL_ASM_KEEP(var) ASM_KEEP(var)
#endif

extern void func_800B09EC(void *arg0, s32 arg1);

/* Updates up to five entries on the current page and clears unused slots. */
void func_800B0BD0(void *list) {
    register void *entry_list;
    register s32 slot;
    register s32 slot_work LOCAL_ASM_REG("$2");
    s32 entry_base;
    s32 entry_index;

    entry_list = list;
    slot = 0;
    for (;;) {
        slot_work = ((S_800B0BD0_0 *)entry_list)->unk_10;
        entry_base = slot_work * 5;
        slot_work = ((S_800B0BD0_0 *)entry_list)->unk_0C;
        entry_index = entry_base + slot;
        slot_work = entry_index < slot_work;
        if (slot_work == 0) {
            slot_work = slot < 5;
            goto check_slot;
        }
        slot_work = slot < 5;
        func_800B09EC(entry_list, entry_index);
        slot++;
        slot_work = slot < 5;
        if (slot_work == 0) {
            goto check_slot;
        }
    }

clear_slot:
    entry_base = ((S_800B0BD0_0 *)entry_list)->unk_CC;
    slot_work += entry_base;
    slot_work = ((S_800B0BD0_1 *)slot_work)->unk_24;
    slot++;
    *(s32 *)slot_work = 0;
    slot_work = slot < 5;
check_slot:
    LOCAL_ASM_KEEP(slot_work);
    if (slot_work != 0) {
        slot_work = slot * 4;
        goto clear_slot;
    }
}
