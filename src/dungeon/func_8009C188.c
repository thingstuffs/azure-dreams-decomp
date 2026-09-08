#include "common.h"

extern u8 D_800E3DB0[];

extern s32 func_800A15B0(s32);
extern void func_80048190(s32);

/* Decrements a matching type-3 entry's count and clears it when exhausted. */
void func_800A18E8(s16 requested_id, s16 requested_type) {
    s16 slot;
    s16 match_id = requested_id;
    u8 *entry = D_800E3DB0;

    if (requested_id == 0x39) {
        match_id = 2;
    }

    if (requested_type == 1 || requested_type == 3) {
        for (slot = 0; slot < 6; slot++, entry += 8) {
            u8 *count = entry + 2;
            u8 entry_type = entry[0];
            u8 entry_id;

            if (entry_type == requested_type && (entry_id = count[-1], entry_id == match_id)) {
                if ((s8)count[0] > 0) {
                    if (entry_type != 1) {
                        if ((s8)--count[0] <= 0) {
                            count[-1] = 0;
                            count[0] = 0;
                            if ((func_800A15B0(entry_id) << 16) == 0) {
                                func_80048190(entry_id);
                                return;
                            }
                        }
                    }
                }
                return;
            }
        }
    }
}
