#include "common.h"

#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
} Item;

typedef struct {
    char *unk0;
    char *unk4;
} StrPair;

/* Category entry is 0x14 bytes; kind@0 selects 12- vs 20-byte records; records@0xC */
typedef struct {
    u8 kind;
    u8 pad[0xB];
    void *records;
    u8 pad2[4];
} CatEnt;

extern s32 func_8004928C(Item *);
extern s32 func_800494FC(Item *);
extern s32 func_8004DD2C(char *);
extern char *rindex(char *, s32);
extern char *strcpy(char *, char *);

extern CatEnt itemCategoryTable[];
extern char D_80083D38[0x40];
extern char *D_800713F8[];

/* Selects item text or a fallback, adjusts its special suffix, and passes it to func_8004DD2C. */
s32 func_80049374(Item *item, StrPair *fallbacks) {
    char *item_text;
    s32 record_words;
    CatEnt *category;
    CatEnt *category_table;
    s32 category_id;
    s32 item_id;

    if ((item == 0) || (item->unk1 == 0)) {
        item_text = fallbacks->unk4;
    } else if (func_800494FC(item) != 0) {
        item_text = fallbacks->unk0;
    } else {
        /* 3-statement category_table form: lui fills prior branch delay; category_id then add */
        category_table = itemCategoryTable;
        category_id = item->unk1;
        category = category_table + category_id;
        if (category->kind == 0) {
            item_id = item->unk0;
            record_words = item_id * 4;
        } else {
            item_id = item->unk0;
            record_words = item_id * 2;
        }
        record_words = record_words + item_id;
        /* Pin scale/record_addr to $v1 so final addu is addu v1,v1,v0 (not addu v0,v0,v1) */
        {
            register s32 record_addr ASM_REG("$3");   /* MATCH pin: slus-diff */
            record_addr = record_words;
            record_addr = record_addr * 4;
            record_addr = record_addr + (s32)category->records;
            item_text = *(char **)(record_addr + 8);
        }
        if ((item->unk1 == 0x13) && (func_8004928C(item) != 0)) {
            strcpy(D_80083D38, item_text);
            strcpy(rindex(D_80083D38, 0) - 0x12, D_800713F8[0]);
            item_text = D_80083D38;
        }
    }
    return func_8004DD2C(item_text);
}
