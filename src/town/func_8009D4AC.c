#include "common.h"

extern void townCallTheHandlerSelectsNonzeroEntry(void *entries, void *record, s32 handler_param);
extern void townClearEntityRecordFields(s32 record);

extern u8 D_800834B8[];
extern u8 D_80097D2C[];
extern u8 D_8009ACFC[];
extern u8 D_800D0078[];
extern s32 D_800D0620;

/* Initializes the global object and resets its state pointers and flag. */
void townInitializeGlobalPlayerObject(void)
{
    void *object;
    void *object_header;
    s32 init_value;

    object = D_800834B8;
    object_header = (u8 *)object - 0x20;
    init_value = *(s32 *)((u8 *)object_header + 0xC);
    townClearEntityRecordFields(*(s32 *)((u8 *)object_header + 8));
    townCallTheHandlerSelectsNonzeroEntry(D_800D0078, object, init_value);
    D_800D0620 = 0;
    *(void **)D_800834B8 = D_80097D2C;
    *(void **)((u8 *)object + 4) = D_8009ACFC;
}
