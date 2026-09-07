#include "common.h"

typedef struct S_8009F9E8_0 {
    u8 unk_00;
    u8 unk_01;
} S_8009F9E8_0;   /* p in func_8009F9E8 */


extern volatile u16 D_80013716;

typedef struct {
    u8 flags;
    u8 kind;
} DungeonEntry;


extern DungeonEntry D_80013720[];

/* Scan backward through special entry kinds for a matching kind and flag bit. */
void *func_8009F9E8(s32 wanted_kind, s32 wanted_flag) {
    s32 entry_index;
    register s32 count ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    s32 count_page;
    s32 kind_group;
    s32 group_70;
    s32 group_78;
    s32 group_80;
    s32 group_90;
    void *entries;
    register void *entry ASM_REG("$3");   /* MATCH pin: retail delay-slot fill depends on it */

    entries = (void *)0x80010000;
    ASM_KEEP(entries);   /* MATCH pin: retail branch polarity depends on it */
    count = 0x80010000;
    count = *(volatile u16 *)(count + 0x3716);
    entry_index = count - 1;
    entries = (void *)((u32)entries | 0x3720);
    if (entry_index < 0) {
        return entries;
    }

    group_70 = 0x70;
    group_78 = 0x78;
    group_80 = 0x80;
    group_90 = 0x90;
    ASM_KEEP(group_70);   /* MATCH pin: retail schedule: same instructions, different order without it */
    ASM_KEEP(group_78);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(group_80);   /* MATCH pin: load-bearing for the whole function shape */
    ASM_KEEP(group_90);   /* MATCH pin: retail register colouring depends on it */
    wanted_kind &= 0xFF;
    wanted_flag &= 0xFF;
    count_page = 0x80010000;
    ASM_KEEP(count_page);   /* MATCH pin: retail register colouring depends on it */
    count = entry_index * 2;
    entry = (void *)((u32)count + (u32)entries);
    do {
        kind_group = ((S_8009F9E8_0 *)entry)->unk_01 & 0xF8;
        if (kind_group == group_70 || kind_group == group_78 || kind_group == group_80 || kind_group == group_90) {
            if (((S_8009F9E8_0 *)entry)->unk_01 == wanted_kind && (((S_8009F9E8_0 *)entry)->unk_00 & 0x20) == wanted_flag) {
                return entry;
            }
        } else {
            return (*(volatile u16 *)(count_page + 0x3716) * 2) + entries;
        }
        entry_index--;
        entry -= 2;
    } while (entry_index >= 0);

    return entries;
}
