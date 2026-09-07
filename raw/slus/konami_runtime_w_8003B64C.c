#include "common.h"

#include "common.h"

extern u8 *D_8001029C[];
extern s8 D_80010333[];
extern void func_800A0150(s32, u8 *, u8 *, s32);
extern void func_800B2244(u8 *entry);

void func_8003B64C(void)
{
    if (D_8001029C[0] != 0) {
        u32 page = 0x80010000;
        u32 *cursor = (u32 *)(page + 0x29C);

        do {
            u8 *entry = (u8 *)*cursor;

            if (entry[1] == 0x13) {
                s32 value = *(s8 *)(page + 0x333 +
                                    (entry[3] & 0x1F) * 84);

                if (value >= 0) {
                    func_800A0150(value & 0x3F, entry,
                                  (u8 *)(0x800102F0 +
                                      (entry[3] & 0x1F) * 84), 0);
                    func_800B2244((u8 *)*cursor);
                    continue;
                }
            }
            cursor++;
        } while (*cursor != 0);
    }
}
