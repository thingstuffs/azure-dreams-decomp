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

void func_80123ECC(void *arg0)
{
    Rect rect;
    char text[16];
    char digits[5];
    ImageList *lists;
    char *textp;
    s32 i;
    u8 index;

    rect.x = 0x1C0;
    rect.y = 0x90;
    rect.w = 0x38;
    rect.h = 0x10;
    func_800671A8(&rect, 0, 0, 0);

    rect.y = 0xC0;
    rect.w = 0x1E;
    rect.x = 0x1C0;
    rect.h = 0x20;
    func_800671A8(&rect, 0, 0, 0);

    rect.x = 0x2C0;
    rect.w = 0x3E;
    rect.y = 0;
    rect.h = 0xF0;
    func_800671A8(&rect, 0, 0, 0);

    index = ((u8 *)arg0)[0x14];
    func_801239B8(D_80126E98[index].image, 0x1C0, 0x90);
    func_80123928(D_8011ACEC, 0x1C7, 0xC0);

    index = ((u8 *)arg0)[0x14];
    func_80123928(*D_80126E98[index].image_ref,
                  (s16)(0x1CF - D_80126E98[index].width), 0xD0);

    index = ((u8 *)arg0)[0x14];
    i = 0;
    if (D_801278B0[index].count != 0) {
        lists = D_801278B0;
        do {
            func_80123928(lists[index].images[i], 0x2C0, (s16)(i * 0x10));
            if ((i & 1) || (i < (lists[((u8 *)arg0)[0x14]].count - 1))) {
                func_80067014(0);
            }
            i++;
            index = ((u8 *)arg0)[0x14];
        } while (i < lists[index].count);
    }
    func_80067014(0);

    i = 10;
    textp = &text[10];
    do {
        *textp = 0;
        i--;
        textp--;
    } while (i >= 0);

    strcat(text, D_8011AD00);
    digits[0] = 0x82;
    digits[1] = ((((u8 *)arg0)[0x14] + 1) / 10) + 0x4F;
    digits[2] = 0x82;
    digits[3] = ((((u8 *)arg0)[0x14] + 1) % 10) + 0x4F;
    digits[4] = 0;
    strcat(text, digits);
    func_801239B8(text, 0x1DB, 0x90);
    func_80067014(0);
}
