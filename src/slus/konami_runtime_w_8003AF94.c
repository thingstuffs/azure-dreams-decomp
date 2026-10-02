#include "common.h"

extern s32 D_8006CD50[];
extern s32 D_80189394;
extern s32 D_801B8EB8;
extern void func_801768AC(void);
extern void func_800411FC(u16);

/* Run town_movie_exe with the supplied value and selected table entry, then process record zero. */
void town_movie_exe(s32 table_index, s32 value) {
    s32 table_value = D_8006CD50[table_index];

    D_80189394 = value;
    D_801B8EB8 = table_value;
    func_801768AC();
    func_800411FC(0);
}
