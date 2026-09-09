#include "common.h"

extern void *func_800A9B2C(s32 arg0, void *arg1);

extern u8 D_8006C894[];
extern u8 D_8006C8F7[];
extern u8 D_8006C982[];
extern u8 D_8006C9E4[];
extern u8 D_800C25C0[];
extern u8 D_800C3174[];
extern u8 D_800C321C[];
extern void *D_80100E38[];

/* Selects a response for the source and target, storing any associated text. */
void *func_800A9D74(void *source, void *target) {
    s32 response_kind;
    register void *text ASM_REG("$2"); /* MATCH: Both store paths use the return-value register. */
    void *data_base;

    if ((source != 0) && (target != 0)) {
        if (((*(u8 *)((u8 *)target + 0x14) == 4) ||
             (*(u8 *)((u8 *)target + 0x4D) != 0)) &&
            ((data_base = *(void **)((u8 *)source - 0x10),
              (data_base == D_800C3174)) ||
             (data_base == D_800C321C) ||
             ((data_base == D_800C25C0) &&
              (*(s32 *)((u8 *)source + 0x60) != 0)))) {
            response_kind = *(s32 *)((u8 *)source + 0x60);
            if (response_kind == 4) {
                return D_8006C9E4;
            }
            if (response_kind == 5) {
                if (*(u16 *)((u8 *)target + 0x4C) == 0xB05) {
                    data_base = (void *)0x80100000;
                    text = D_8006C8F7;
                } else {
                    data_base = (void *)0x80100000;
                    text = D_8006C982;
                }
                *(void **)((u8 *)data_base + 0xE38) = text;
            } else {
                text = func_800A9B2C(response_kind, (u8 *)target + 0x4C);
                D_80100E38[0] = text;
                if (text == 0) {
                    return 0;
                }
            }
            return D_8006C894;
        }
    }
    return 0;
}
