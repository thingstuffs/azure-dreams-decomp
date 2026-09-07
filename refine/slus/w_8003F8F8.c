#include "common.h"

#include "common.h"

typedef struct {
    void *data;
    s16 rect_x;
    s16 rect_y;
    s16 width;
    s16 height;
    s32 unk0C;
} S_8003F8F8;

extern s32 D_80080A7C;
extern s32 D_80081480;
extern s32 D_8008148C;

extern void DrawSync(s32 mode);
extern void *func_8004068C(void *src, void *dst);
extern s32 LoadImage(void *rect, void *data);

/* Uploads a null-terminated image list to VRAM through a staging buffer. */
void func_8003F8F8(S_8003F8F8 *images)
{
    S_8003F8F8 *entry;
    s32 width;
    s32 column_bytes;
    s32 image_bytes;

    entry = images;
    while (entry->data != 0) {
        width = entry->width;
        column_bytes = entry->height * 2;
        image_bytes = width * column_bytes;
        if ((u32)(D_8008148C + D_80080A7C) >=
            (u32)(D_80081480 + image_bytes)) {
            D_80081480 = D_8008148C;
            DrawSync(0);
        }
        func_8004068C(entry->data, (void *)D_80081480);
        LoadImage(&entry->rect_x, (void *)D_80081480);
        width = entry->width;
        column_bytes = entry->height * 2;
        image_bytes = width * column_bytes;
        entry++;
        D_80081480 += image_bytes;
    }
}
