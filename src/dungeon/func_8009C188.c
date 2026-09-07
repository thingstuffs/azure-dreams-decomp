#include "common.h"

extern u8 D_800E3DB0[];

extern s32 func_800A15B0(s32);
extern void func_80048190(s32);
extern void func_800A19D0(void);

void func_800A18E8(s16 arg0, s16 arg1) {
    s16 i;
    s16 kind = arg0;
    u8 *entry = D_800E3DB0;

    if (arg0 == 0x39) {
        kind = 2;
    }

    if (arg1 == 1 || arg1 == 3) {
        for (i = 0; i < 6; i++, entry += 8) {
            u8 *field = entry + 2;
            u8 type = entry[0];
            u8 id;

            if (type == arg1 && (id = field[-1], id == kind)) {
                if ((s8)field[0] > 0) {
                    if (type != 1) {
                        if ((s8)--field[0] <= 0) {
                            field[-1] = 0;
                            field[0] = 0;
                            if ((func_800A15B0(id) << 16) == 0) {
                                func_80048190(id);
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
