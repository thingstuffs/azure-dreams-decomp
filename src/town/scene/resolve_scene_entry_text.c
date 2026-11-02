#include "common.h"
#include "town/scene.h"
#include "town/scene/flags.h"
#include "town/scene/motion.h"

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

    result = apply_entry_position(entries, D_8001768C, context, selection);
    if (resolve_entry_flag(entries, context, selection)) {
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
