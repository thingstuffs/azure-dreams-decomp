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

extern s32 record_has_type_twenty(Item *);
extern s32 read_item_category_flag_ten(Item *);
extern s32 submit_script_with_registered_context(char *);
extern char *rindex(char *, s32);
extern char *strcpy(char *, char *);

extern CatEnt itemCategoryTable[];
extern char item_name_suffix_buffer[0x40];
extern char *item_name_suffix_texts[];

/* Selects item text or a fallback, adjusts its special suffix, and passes it to func_8004DD2C. */
s32 get_item_name_text(Item *item, StrPair *fallbacks) {
    char *item_text;
    s32 item_id;
    s32 record_words;
    CatEnt *category;
    CatEnt *category_table;
    s32 category_id;

    if ((item == 0) || (item->unk1 == 0)) {
        item_text = fallbacks->unk4;
    } else if (read_item_category_flag_ten(item) != 0) {
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
        record_words = record_words * 4;
        record_words = record_words + (s32)category->records;
        item_text = *(char **)(record_words + 8);
        record_words = item->unk1;
        if ((record_words == 0x13) && (record_has_type_twenty(item) != 0)) {
            strcpy(item_name_suffix_buffer, item_text);
            strcpy(rindex(item_name_suffix_buffer, 0) - 0x12, item_name_suffix_texts[0]);
            item_text = item_name_suffix_buffer;
        }
    }
    return submit_script_with_registered_context(item_text);
}
