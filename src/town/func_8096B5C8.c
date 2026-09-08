#include "common.h"
#include "m2c_compat.h"

M2C_UNK func_80067014();                     /* extern */
M2C_UNK func_800671A8(); /* extern */
s32 func_80123200();                             /* extern */
M2C_UNK func_80123928();               /* extern */
M2C_UNK func_801239B8(); /* extern */
extern M2C_UNK D_8011ACD8;
typedef struct {
    void *image;
    void **image_ref;
    u16 unused;
    u16 width;
} ImageEntry;
extern ImageEntry D_80126E98[];

typedef struct S_80123A60_0 {
    u8 pad_00[0xF];
    u8 unk_0F;
} S_80123A60_0;   /* object in func_80123A60 */

/* Clears the image area and draws available images for the object's category. */
void func_80123A60(void *object_data) {
    S_80123A60_0 *object = object_data;
    s16 clear_rect[4];
    ImageEntry *image_entry;
    u8 *loop_image_base;
    s32 first_image_id;
    s32 second_image_id;
    s32 image_id;
    s32 slot;
    s32 grid_category;
    s32 category;

    clear_rect[0] = 0x180;
    clear_rect[1] = 0x80;
    clear_rect[2] = 0x36;
    clear_rect[3] = 0x60;
    func_800671A8(clear_rect, 0, 0, 0);
    func_801239B8(&D_8011ACD8, 0x192, 0xD0);
    func_80067014(0);
    category = object->unk_0F;
    slot = 0;
    if (category == 3) {
        ASM_KEEP(category);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        slot = category;
        first_image_id = slot * 0x10;
        ASM_KEEP(first_image_id);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        if (func_80123200(first_image_id & 0xF0) & 0xFF) {
            u8 *image_base = (u8 *)D_80126E98;
            void **image_ptr;
            image_ptr = (void **)((((slot << 5) + first_image_id) << 2) +
                                  (u32)image_base);
            func_80123928(*image_ptr, 0x180, 0x80);
        }
        second_image_id = first_image_id + 1;
        if (func_80123200(second_image_id & 0xFF) & 0xFF) {
            func_80123928(D_80126E98[second_image_id].image, 0x1A4, 0xA0);
        }
        goto done;
    }
    ASM_MEM_BARRIER();   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    grid_category = object->unk_0F;
    ASM_KEEP(grid_category);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    loop_image_base = (u8 *)D_80126E98;
    ASM_KEEP(loop_image_base);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
    image_id = grid_category * 0x10;
    image_entry = (ImageEntry *)(((((grid_category << 5) + image_id) << 2)) +
                            (u32)loop_image_base);
    do {
        if (func_80123200(image_id & 0xFF) & 0xFF) {
            func_80123928(image_entry->image, (s16) (((slot % 3) * 0x12) + 0x180), (s16) (((slot / 3) * 0x10) + 0x80));
        }
        slot += 1;
        image_entry += 1;
        image_id += 1;
    } while (slot < 0x10);
done:
    func_80067014(0);
}
