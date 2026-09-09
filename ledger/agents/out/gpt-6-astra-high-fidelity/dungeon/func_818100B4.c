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

void func_800250B4(ItemResult *result, ItemId *item, void *data)
{
    void *new_data;

    if (data != 0) {
        result->data = data;
        return;
    }

    if (item->category == 19) {
        s32 tail_data;

        tail_data = func_80049330(item) + 52;
        new_data = (void *)tail_data;
    } else {
        new_data = func_8004A784(item->category, item->index);
        if (new_data == 0) {
            result->text = itemCategoryTable[item->category].records[item->index].text;
            new_data = func_8004A83C(item->category, item->index);
            result->data = new_data;
            strncpy(new_data, result->text, 12);
            return;
        }
    }

    result->data = new_data;
}

/* MECHANISM: A 32-byte frame naturally holds result/item in s1/s0; splitting the
   incoming data argument from call-result new_data removes the one-word v0 copy.
   A one-sided barrier preserves the early store/jump, while noreturn true-space
   tails plus a guarded v0 tail-slot pin reproduce the three local continuations. */
