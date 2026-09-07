#include "common.h"

#include "common.h"

extern u8 *D_8001029C[];
extern s8 D_80010333[];
extern void func_800A0150(s32, u8 *, u8 *, s32);
extern void func_800B2244(u8 *entry);

/* Processes type-0x13 entries whose associated record code is nonnegative. */
void func_8003B64C(void)
{
    if (D_8001029C[0] != 0) {
        u32 data_base = 0x80010000;
        u32 *entry_slot = (u32 *)(data_base + 0x29C);

        do {
            u8 *entry = (u8 *)*entry_slot;

            if (entry[1] == 0x13) {
                s32 record_code = *(s8 *)(data_base + 0x333 +
                                          (entry[3] & 0x1F) * 84);

                if (record_code >= 0) {
                    func_800A0150(record_code & 0x3F, entry,
                                  (u8 *)(0x800102F0 +
                                      (entry[3] & 0x1F) * 84), 0);
                    func_800B2244((u8 *)*entry_slot);
                    continue;
                }
            }
            entry_slot++;
        } while (*entry_slot != 0);
    }
}
