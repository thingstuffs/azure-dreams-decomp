#include "common.h"

extern void func_8007C040(void *ptr_a, void *ptr_b, s32 value);

extern u8 D_80400114[];
extern u8 D_80400120[];
extern u8 D_80400134[];

/* Computes the game-save XOR checksum and compares it with the stored checksum. */
s32 func_8001AFEC(void *gsw)
{
    s32 *word;
    s32 checksum;
    s32 count;
    s32 value;

    checksum = 0;
    word = (s32 *)((u8 *)gsw + 0x208);
    if (gsw != 0) {
        count = checksum;
    } else {
        count = checksum;
    }
    do {
        value = *word;
        checksum ^= value;
        word++;
        count++;
    } while (count < 0x1782);

    func_8007C040(D_80400114, D_80400134, checksum);
    func_8007C040(D_80400114, D_80400120,
                  *(s32 *)((u8 *)gsw + 0x204));
    return *(s32 *)((u8 *)gsw + 0x204) == checksum;
}
