#include "common.h"
#include "town/scene.h"

extern char *func_80016BE4(void *entries, void *positions, void *context, s32 selection);
extern s32 func_80016B2C(void *entries, void *context, s32 selection);
extern u8 D_8001759C[];
extern u8 D_8001768C[];
extern char D_8001857B[];
extern char D_80018898[];
extern char D_80017AB4[];
extern char D_80018042[];
extern char D_800182CA[];

/* Resolve the scene entry, using its alternate text when its flag is set. */
char *resolve_scene_entry_text(void *context, s32 unused, s32 selection)
{
    char *result;
    u8 *entries = D_8001759C;

    result = func_80016BE4(entries, D_8001768C, context, selection);
    if (func_80016B2C(entries, context, selection)) {
        switch (selection) {
        case 52:
            return D_8001857B;
        case 41:
        case 42:
            return D_80018898;
        case 16:
            return D_80017AB4;
        case 45:
            return D_80018042;
        case 69:
            return D_800182CA;
        }
    }
    return result;
}
