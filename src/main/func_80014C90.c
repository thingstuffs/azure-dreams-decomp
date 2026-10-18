#include "common.h"

extern void set_object_cleanup_flag(s32);
extern void card_boot_mark_object_complete(s32);
extern void configure_shared_fade_primitive(void);
extern s32 D_800814A0;

typedef struct {
    /* 0x00 */ s8 pad0[0x1E];
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s8 pad28[0x18];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
} Struct80014C90;

/* Process the entry's values and set its local and global status flags. */
void card_boot_destroy_card_chooser(Struct80014C90 *entry) {
    Struct80014C90 *entry_data = (Struct80014C90 *)((s8 *)entry + 0x20);

    set_object_cleanup_flag(entry_data->unk20);
    card_boot_mark_object_complete(entry_data->unk24);
    if (entry->unk20 == 2) {
        configure_shared_fade_primitive();
    }
    entry->unk1E |= 0x8000;
    D_800814A0 |= 0x8000;
}
