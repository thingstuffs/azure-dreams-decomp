#include "common.h"

#include "common.h"

typedef struct {
    s32 unk0;
    void *object;
} ObjectEntry;

extern ObjectEntry D_80082660[];
extern u8 D_800C3174[];
extern u8 D_800C321C[];
extern u8 D_800C3960[];

__asm__(".set D_800C3174, 0x800C3174");
__asm__(".set D_800C321C, 0x800C321C");

void *func_800392A4(u8 arg0)
{
    u8 *object;
    void *type;
    void *result;

    object = D_80082660[arg0].object;
    if (object == 0) {
        return 0;
    }

    result = object + 0x20;
    if (arg0 == 1) {
        return result;
    }

    type = *(void **)(object + 0x10);
    if (type == D_800C3174 || type == D_800C321C) {
        if (*(void **)((u8 *)result + 0x50) == D_800C3960) {
            return result;
        }
    }

    return 0;
}
