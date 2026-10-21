#include "common.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in run_record_handler_if_active, addressed as arg0[-1] */

typedef struct S_800A78AC_0 {
    u8 pad_00[0x50];
    s32 (*unk_50)(void *);
} S_800A78AC_0;   /* arg0 in run_record_handler_if_active */
void advance_sprite_animation_and_textures(void *entity);                     /* extern */

/* Call the record handler and update its data if the record remains active. */
void run_record_handler_if_active(void *record, s32 unused, s32 update_data) {
    s32 (*handler)(void *);

    handler = ((S_800A78AC_0 *)record)->unk_50;
    if (handler != 0) {
        handler(record);
        if (!(((ObjectRetirementFlags *)record)[-1].unk_00 & 0x8000)) {
            advance_sprite_animation_and_textures(update_data);
        }
    }
}
