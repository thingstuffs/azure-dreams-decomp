#include "common.h"

/* Element of the shared D_80084960 stat/entity table (stride 0x9C = 156 bytes);
 * only the field at offset 0x1C is touched here. */
typedef struct {
    u8 pad00[0x1C];
    s32 unk1C;
    u8 pad20[0x9C - 0x1C - 4];
} S_80084960; /* size 0x9C */

extern S_80084960 D_80084960[];

extern void func_80055E7C();

/* Sets D_80084960[index].unk1C = value & 0x7F (index comes from the first
 * parameter, masked to a byte; the second parameter is unused/dead), then
 * calls the stub notifier func_80055E7C(1, index, value & 0xFF). */
void func_80058494(u8 index, s32 unused, s32 value) {
    D_80084960[index].unk1C = value & 0x7F;
    func_80055E7C(1, index, value & 0xFF);
}
