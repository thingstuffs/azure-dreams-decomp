/* Relink of matched main/func_80010A00; every changed retail word is a paired relocation. */
#define cardBootReleaseThreeRowPanelText func_800240EC
#include "common.h"
#include "shared/object_flags.h"

extern void func_800240EC(void *);

/* Processes a nonzero record and sets its flag and the global flag to include bit 15. */
void func_80024184(s32 record) {
    void *record_data;

    if (record != 0) {
        record_data = (void *) (record + 0x20);
        func_800240EC(record_data);
        *(u16 *) ((s8 *) record_data - 2) = *(u16 *) ((s8 *) record_data - 2) | 0x8000;
        objectFlagBlock.flags = objectFlagBlock.flags | 0x8000;
    }
}
