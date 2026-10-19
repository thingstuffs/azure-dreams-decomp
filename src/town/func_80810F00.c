#include "common.h"
#include "shared/object_links.h"

   /* the 0x2 bytes before arg0 in func_80810F00, addressed as arg0[-1] */

typedef struct S_80810F00_0 {
    s16 unk_00;
    u8 pad_02[0x2];
    s32 unk_04;
    s16 * unk_08;
    void * unk_0C;
} S_80810F00_0;   /* arg0 in func_80810F00 */

typedef struct S_80810F00_1 {
    u8 pad_00[0xC];
    u16 unk_0C;
} S_80810F00_1;
void func_80058588(s32 value, s32 query, s32 key);               /* extern */
s32 func_80071424();                             /* extern */
extern s32 D_80084D5C;

/* Process an entry in state zero and propagate its linked status flag. */
void func_80810F00(void *entry) {
    ObjectStatusPrefix16 *entry_view = entry;
    u16 *flags;
    void *flag_data;

    flag_data = ((S_80810F00_0 *)entry)->unk_0C;
    if (((S_80810F00_0 *)entry)->unk_00 == 0) {
        func_80058588(*((S_80810F00_0 *)entry)->unk_08, func_80071424(((S_80810F00_0 *)entry)->unk_04),
            ((S_80810F00_0 *)entry)->unk_04);
        if (((S_80810F00_1 *)flag_data)->unk_0C & 2) {
            flags = &entry_view[-1].unk_00;
            *flags = (u16) (entry_view[-1].unk_00 | 0x8000);
            D_80084D5C |= 0x8000;
        }
    }
}
