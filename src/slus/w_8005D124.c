#include "common.h"

#define VOLATILE_FIELD(ptr, type, off) \
    (*(volatile type *)((u8 *)(ptr) + (off)))

extern void func_8005D704(void);
extern void func_8005D730(void);
extern void *D_80079958;
extern s32 *D_8007995C;
extern s32 * volatile D_80079960;
extern s32 *D_80079964;
extern s32 D_800799A8;

void func_8005D124(s32 arg0, s16 arg1, s32 arg2)
{
    VOLATILE_FIELD(D_80079958, s16, 0x1A6) = arg1;
    func_8005D730();
    VOLATILE_FIELD(D_80079958, u16, 0x1AA) |= 0x30;
    func_8005D730();
    func_8005D704();

    *D_8007995C = arg0;
    *D_80079960 = ((u32)arg2 << 16) | 0x10;
    D_800799A8 = 1;
    *D_80079964 = 0x01000200;
}
