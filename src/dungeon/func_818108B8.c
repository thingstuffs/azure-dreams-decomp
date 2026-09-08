#include "common.h"

typedef struct {
    u8 pad0[0xC];
    s32 value;
    u8 pad10[4];
} ItemRecord;

typedef struct {
    u8 pad0[0xC];
    ItemRecord *records;
    u8 pad10[4];
} ItemCategory;

typedef struct {
    u8 pad0[8];
    s32 value;
    u8 padC[0x10];
    s32 index;
} Subobject;

typedef struct {
    u8 pad0[0xC];
    s32 category;
    u8 pad10[4];
    void *subobject_base;
    u8 pad18[0x60];
    u8 fallback_arg[0x10];
    s32 fallback_value;
} Object;

extern ItemCategory D_80073414[];
extern void func_8004A7D8();
extern void strcpy();



typedef struct S_800258B8_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x70];
    s32 unk_88;
} S_800258B8_0;   /* object in func_800258B8 */

typedef struct S_800258B8_1 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0x10];
    s32 unk_1C;
} S_800258B8_1;   /* subobject in func_800258B8 */

/* Updates an item category record's value or copies the object's fallback string. */
void func_800258B8(void *item_object)
{
    s32 category;
    s32 subobject_base;
    void *object = item_object;
    S_800258B8_1 *subobject;

    subobject_base = ((S_800258B8_0 *)object)->unk_14;
    category = ((S_800258B8_0 *)object)->unk_0C;
    subobject = (void *)(subobject_base + 0x20);
    if (category != 0x13) {
        if (subobject->unk_08 != 0) {
            func_8004A7D8(category, subobject->unk_1C);
            D_80073414[((S_800258B8_0 *)object)->unk_0C]
                .records[subobject->unk_1C].value =
                subobject->unk_08;
            return;
        }
    }
    strcpy(((S_800258B8_0 *)object)->unk_88, (u8 *)object + 0x78);
}
