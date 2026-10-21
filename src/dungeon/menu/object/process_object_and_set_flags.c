#include "common.h"
#include "shared/object_flags.h"

extern void flag_object_for_removal(s32 object);
extern s32 dungeon_menu_object[];

/* Process the object handle, clear the global state, and set the high flag bits. */
void process_object_and_set_flags(void *object)
{
    flag_object_for_removal(*(s32 *)((u8 *)object + 0x5C));
    dungeon_menu_object[0] = 0;
    {
        u16 object_flags = *(u16 *)((u8 *)object + 0x1E);
        s32 global_flags = object_flag_block.flags;
        *(u16 *)((u8 *)object + 0x1E) = object_flags | 0x8000;
        object_flag_block.flags = global_flags | 0x8000;
    }
}
