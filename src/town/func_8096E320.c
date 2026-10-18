#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"

#ifndef NULL
#define NULL 0
#endif

typedef s32 M2C_UNK;

typedef struct S_801267B8_0 {
    u8 pad_00[0xC];
    void * unk_0C;
    M2C_UNK * unk_10;
    u8 pad_14[0xA];
    u16 unk_1E;
} S_801267B8_0;   /* obj in open_standalone_catalog */


s32 func_8004491C();
M2C_UNK func_8004B248();
M2C_UNK SD_Call();
M2C_UNK func_80064F00();
M2C_UNK func_80064F20();
void initialize_catalog_glyph_cache();
s32 initialize_catalog_display_nodes();
void initialize_catalog_state();

extern M2C_UNK D_8004CAA0;
extern s8 D_80080A84;
extern s32 D_80126704;

/* Initializes the object's state and callbacks, or flags initialization failure. */
void open_standalone_catalog(void) {
    s32 obj_data;
    s32 global_flags;
    u16 object_flags;
    void *obj;

    obj = func_8003FC64(0);
    obj_data = (u8 *)obj + 0x20;
    if (obj != NULL) {
        if (initialize_catalog_display_nodes(obj_data) != 0) {
            D_80080A84 = 1;
            initialize_catalog_glyph_cache();
            ((S_801267B8_0 *)obj)->unk_0C = (u8 *)obj + 0x68;
            initialize_catalog_state(obj_data);
            func_8004491C(obj, &D_8004CAA0);
            ((S_801267B8_0 *)obj)->unk_10 = &D_80126704;
            g_game_work.view.unk_088 = 0x200;
            func_80064F20(0x200);
            func_80064F00(0xA0, 0x78);
            SD_Call(0x701);
            return;
        }
        func_8004B248((u8 *)obj + 0x7C);
        global_flags = object_flag_block.flags;
        object_flags = ((S_801267B8_0 *)obj)->unk_1E;
        ((S_801267B8_0 *)obj)->unk_1E = object_flags | 0x8000;
        object_flag_block.flags = global_flags | 0x8000;
    }
}
