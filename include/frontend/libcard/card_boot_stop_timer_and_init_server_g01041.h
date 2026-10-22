#ifndef FRONTEND_LIBCARD_CARD_BOOT_STOP_TIMER_AND_INIT_SERVER_G01041_H
#define FRONTEND_LIBCARD_CARD_BOOT_STOP_TIMER_AND_INIT_SERVER_G01041_H
/* Card boot stop timer and init server. Shared declarations. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-weak - group G01041 - CL:main/func_80014C60. */

#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "m2c_compat.h"
#include "modules/main_server_ship_interfaces.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard.h"
#include "engine/menu.h"
#include "shared/game_work.h"
#include "sdk/libgte.h"

typedef struct {
    /* 0x00 */ s8 pad0[0x1E];
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s8 pad28[0x18];
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
} Struct80014C90;

typedef struct Node8002BB08 Node8002BB08;

extern s8 animation_tick_scale;
extern void configure_shared_fade_primitive(void);
extern s32 D_800814A0;
void save_and_clear_entity_flag_ten(void);

/* Shared import declarations; data casts preserve each measured view. */


/* Functions defined in this translation unit. */
void card_boot_stop_timer_and_init_server(void);
void card_boot_destroy_card_chooser(Struct80014C90 *entry);
void card_boot_open_save_slot_selection(s32 request);
void dispatch_request_mode_two(s32 request);
void dispatch_menu_update_callback(s32 request);

#endif
