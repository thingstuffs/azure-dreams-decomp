#include "common.h"

extern void func_8007C040(void *arg0, void *arg1, s32 arg2);

extern u8 D_80400114[];
extern u8 D_80400120[];
extern u8 D_80400134[];

s32 func_8001AFEC(void *arg0)
{
    s32 *word;
    s32 checksum;
    s32 count;
    s32 value;

    checksum = 0;
    word = (s32 *)((u8 *)arg0 + 0x208);
    if (arg0 != 0) {
        count = checksum;
    } else {
        count = checksum;
    }
    do {
        value = *word;
        count++;
        checksum ^= value;
        word++;
    } while (count < 0x1782);

    func_8007C040(D_80400114, D_80400134, checksum);
    func_8007C040(D_80400114, D_80400120,
                  *(s32 *)((u8 *)arg0 + 0x204));
    return *(s32 *)((u8 *)arg0 + 0x204) == checksum;
}
