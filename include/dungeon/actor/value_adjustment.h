#ifndef DUNGEON_OVL_191E87C_H
#define DUNGEON_OVL_191E87C_H
#include "common.h"
#include "m2c_compat.h"
/* cfail-repair: tf7-phase1-cache-v3 */

typedef struct Row_818FE800_Target {
    u8 pad0[3];
    u8 field3;
    u8 pad4[0x22];
    u8 field26;
} Row_818FE800_Target;

#ifdef __mips__






#endif

/* Roll the target's 0x3 resistance against the attack level: on a hit, halve its 0x26 counter and run effect 0x53 with that amount, otherwise apply the miss record and run 0x53 with -1. */
s32 get_unused_text_buffer(void);
s32 expand_text_control_codes(void *src, void *dst);
s32 clear_byte_and_advance(void *byte_ptr);
s32 write_text_byte_and_advance(s8 value, void *dest);
s32 append_entity_display_text(void *record, void *out);
s32 adjust_source_value_and_finalize(void *, void *);
#include "dungeon/effect/screen.h"
s32 display_text_with_fullwidth_adjustment(void *text);
s32 generate_random_value(void);
s32 create_actor_value_popup(s32 flags, void *source_data, s16 value, u16 callback_mode);
void update_effect_particles_and_cleanup(void);
void func_80024658(void);
void randomize_counted_sprite_angle(void);
void func_8002469C(void);
void card_boot_refresh_five_slot_selection(void);
void func_800250A4(void);
void func_8002536C(void);
void func_8002561C(void);
void func_80025BB0(void);
void func_80025CDC(void);
void func_80025D20(void);
void func_80025DF4(void);
void func_80025D90(void);
extern u8 D_800E2096[38];
extern u8 D_800E20BC[26];
s32 apply_random_actor_value_adjustment(Row_818FE800_Target *target, s32 level, void *record);
#endif
