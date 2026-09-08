#include "common.h"

typedef struct DungeonState {
    u8 pad[0x1C];
    u32 flags;
} DungeonState;

extern DungeonState *D_800E3D7C[];
extern void * volatile D_800DD724[];

extern s32 func_8004AC3C(s32, s32 *);
extern s32 strlen(s32);
extern void memcpy(s32, s32, s32);

/* Copies the selected text without its terminator and returns the destination end. */
s32 func_800992E8(s32 text_id, s32 dest) {
    s32 text_info;
    s32 text;
    s32 length;

    if (D_800E3D7C[0]->flags & 0x10) {
        text = (s32)D_800DD724[0];
    } else {
        text = func_8004AC3C(text_id, &text_info);
    }
    length = strlen(text);
    memcpy(dest, text, length);
    return dest + length;
}
