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

/* Returns object data for slot 1 or objects with matching type and data tags. */
void *ms_mot_accpt_ow(u8 object_index)
{
    u8 *object;
    void *object_type;
    void *object_data;

    object = D_80082660[object_index].object;
    if (object == 0) {
        return 0;
    }

    object_data = object + 0x20;
    if (object_index == 1) {
        return object_data;
    }

    object_type = *(void **)(object + 0x10);
    if (object_type == D_800C3174 || object_type == D_800C321C) {
        if (*(void **)((u8 *)object_data + 0x50) == D_800C3960) {
            return object_data;
        }
    }

    return 0;
}
