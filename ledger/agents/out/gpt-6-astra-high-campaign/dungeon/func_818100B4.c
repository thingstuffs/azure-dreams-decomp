#include "common.h"

typedef struct {
    u8 index;
    u8 category;
    u8 unk2;
    u8 unk3;
} ItemId;

typedef struct {
    u8 pad0[12];
    void *text;
    u8 pad10[4];
} ItemRecord;

typedef struct {
    u8 pad0[12];
    ItemRecord *records;
    u8 pad10[4];
} ItemCategory;

typedef struct {
    u8 pad0[4];
    void *data;
    void *text;
} ItemResult;

extern ItemCategory itemCategoryTable[];
extern s32 func_80049330(ItemId *item);
extern void *func_8004A784(s32 category, s32 index);
extern void *func_8004A83C(s32 category, s32 index);
extern char *strncpy(char *dst, const char *src, u32 count);

/* Sets item data from the supplied pointer or a lookup, copying fallback text when needed. */
void func_800250B4(ItemResult *result, ItemId *item, void *data)
{
    void *item_data;

    if (data != 0) {
        result->data = data;
        return;
    }

    if (item->category == 19) {
        s32 data_addr;

        data_addr = func_80049330(item) + 52;
        item_data = (void *)data_addr;
    } else {
        item_data = func_8004A784(item->category, item->index);
        if (item_data == 0) {
            result->text = itemCategoryTable[item->category].records[item->index].text;
            item_data = func_8004A83C(item->category, item->index);
            result->data = item_data;
            strncpy(item_data, result->text, 12);
            return;
        }
    }

    result->data = item_data;
}
