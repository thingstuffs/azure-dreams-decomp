#include "common.h"

typedef struct {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
} Rect;

typedef struct {
    void *image;
    void **image_ref;
    u16 unused;
    u16 width;
} ImageEntry;

typedef struct {
    void **images;
    u8 count;
    u8 pad[3];
} ImageList;

extern void func_80067014();
extern void func_800671A8();
extern void strcat();
extern void func_80123928();
extern void func_801239B8();

extern u8 D_8011ACEC[16];
extern u8 D_8011AD00[16];
extern ImageEntry D_80126E98[];
extern ImageList D_801278B0[];

/* Clear display regions and draw the selected entry images and number label. */
void func_80123C18(void *entry_state)
{
    Rect clear_rect;
    char label[16];
    char number_text[5];
    ImageList *image_lists;
    char *label_cursor;
    s32 pos;
    u8 entry_index;

    clear_rect.x = 0x1C0;
    clear_rect.y = 0x80;
    clear_rect.w = 0x38;
    clear_rect.h = 0x10;
    func_800671A8(&clear_rect, 0, 0, 0);

    clear_rect.y = 0xA0;
    clear_rect.w = 0x1E;
    clear_rect.x = 0x1C0;
    clear_rect.h = 0x20;
    func_800671A8(&clear_rect, 0, 0, 0);

    clear_rect.x = 0x340;
    clear_rect.w = 0x3E;
    clear_rect.y = 0;
    clear_rect.h = 0xF0;
    func_800671A8(&clear_rect, 0, 0, 0);

    entry_index = ((u8 *)entry_state)[0x13];
    func_801239B8(D_80126E98[entry_index].image, 0x1C0, 0x80);
    func_80123928(D_8011ACEC, 0x1C7, 0xA0);

    entry_index = ((u8 *)entry_state)[0x13];
    func_80123928(*D_80126E98[entry_index].image_ref,
                  (s16)(0x1CF - D_80126E98[entry_index].width), 0xB0);

    entry_index = ((u8 *)entry_state)[0x13];
    pos = 0;
    if (D_801278B0[entry_index].count != 0) {
        image_lists = D_801278B0;
        do {
            func_80123928(image_lists[entry_index].images[pos], 0x340, (s16)(pos * 0x10));
            if ((pos & 1) || (pos < (image_lists[((u8 *)entry_state)[0x13]].count - 1))) {
                func_80067014(0);
            }
            pos++;
            entry_index = ((u8 *)entry_state)[0x13];
        } while (pos < image_lists[entry_index].count);
    }

    pos = 10;
    label_cursor = &label[10];
    do {
        *label_cursor = 0;
        pos--;
        label_cursor--;
    } while (pos >= 0);

    strcat(label, D_8011AD00);
    number_text[0] = 0x82;
    number_text[1] = ((((u8 *)entry_state)[0x13] + 1) / 10) + 0x4F;
    number_text[2] = 0x82;
    number_text[3] = ((((u8 *)entry_state)[0x13] + 1) % 10) + 0x4F;
    number_text[4] = 0;
    strcat(label, number_text);
    func_801239B8(label, 0x1DB, 0x80);
    func_80067014(0);
}
