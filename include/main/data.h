#ifndef MAIN_DATA_H
#define MAIN_DATA_H
/* Imported data declarations for this image; maintained by tools/headers. */

#include "common.h"
#include "frontend/card/server_text.h"
#include "shared/timed_stream.h"
#include "frontend/settings.h"
#include "m2c_compat.h"

/* Data declarations. */
extern s16 D_80011F48;


extern M2C_UNK D_80025398;

extern s32 D_80025788;
extern M2C_UNK D_800261C0[ ];
extern M2C_UNK D_800261F0;
extern M2C_UNK D_800262BC;
extern s32 D_800263C0[ ];
extern s32 D_8002644C[ ];

struct CardChooserBody;
void D_800274D8(struct CardChooserBody *menu);



extern u8 D_80027A9C[ ];
extern u8 D_80027F48[ ];
extern u8 D_80027FD0[ ];
extern u8 D_80027FF8;
extern s16 D_80028010[ 8 ];
extern u8 D_80028020[ ];
extern u8 D_80028068[ ];
extern s32 D_8002806C[ ];
extern s32 D_80028074[ ];
extern s32 D_8002807C[2];
extern s32 D_80028084[2];
extern void (*D_8002809C[])(struct CardChooserBody *menu);
extern s32 D_80028294[ ];
extern s32 D_800282A0;
extern void *D_800282A4[ 3 ];
extern u8 D_800282CC[ ];
extern M2C_UNK D_80028418;
extern M2C_UNK D_80028430;
extern u8 card_command_panel_object[ ];
extern u8 D_80029618[ ];
extern u8 card_rotated_grid_object[ ];
extern M2C_UNK D_8002B7E0;
extern u8 D_8002B850[ ];
extern u8 card_save_heading_object[ ];
extern s32 text_sprite_builder_address[ 4 ];
extern M2C_UNK D_80078AF0;
extern s32 D_80079054;
extern s32 D_800790B4;
extern s32 D_80079114;
extern void *D_800791A4;
extern M2C_UNK D_80082FF4;
extern M2C_UNK D_80083060;
extern M2C_UNK D_8008306C;
extern s32 D_80083840[ ];
extern s32 D_80084110;
extern s32 D_80084158;
extern s32 D_8008432C;
extern s32 D_80088760[3];
extern SettingsEffectTable D_80088790;
extern s32 D_800887B8[5];
extern SettingsEffectTable D_800887CC;


extern M2C_UNK D_8008B230;
extern M2C_UNK D_8008B270;
extern s32 D_8008B2B0;
extern s32 D_8008B2B4;
extern s32 D_8008B2BC;
extern s32 D_8008B2C4[4];
extern s32 D_8008B2D4[2];
extern s32 D_8008B2DC;
extern s32 D_8008B2E4[3];
extern s32 D_8008B2FC[27];
extern u16 D_8008B368[ ];
extern u16 D_8008B36A[ ];
extern u16 D_8008B36C[ ];
extern s32 dev_card_remaining_8k_blocks[2];

extern u8 D_80400000[ ];

/* Static objects supplied by the MAIN card server. */
extern struct CardDevBackgroundObject card_background_object;
extern struct CardDevSmeObject card_sme_object;




extern u8 D_80400544[ ];
extern s32 D_804005EC;
extern s32 D_804005F0;
extern s16 D_80400660[ ];
extern s32 D_80400668[ ];
extern s16 D_804006AC[ ];
extern s16 D_804006BC[ ];
extern s16 D_804006C0[ ];
extern u8 D_804006C4[ ];
extern u8 D_804006EC[ ];
extern u8 D_8040071C[ ];
extern short D_8040077C[ ];
extern u8 D_80402F04[ ];
extern u8 D_80405AB4[ ];
extern M2C_UNK D_80405CB8;
extern M2C_UNK D_80405DE0;



void D_80407D90(struct CardChooserBody *menu);
void D_80407DB8(struct CardChooserBody *menu);

extern void *D_80407F40;

struct CardDevAllocatedObject;
extern void (*card_object_callbacks[])(struct CardDevAllocatedObject *object);
extern u8 card_dev_dialog_layouts[ ];
extern u8 D_80408ADD[ ] [ 4 ];
extern u8 D_80408ADE[ ];
extern u8 D_80408ADF[ ];
extern M2C_UNK D_80408C84;
extern s32 D_80408C8C;
extern M2C_UNK D_80408C9C;
extern s32 D_80408CB0[ ];
extern M2C_UNK D_80408CB8;
extern M2C_UNK D_80408CE8;
extern u8 D_80408CF0[ ];
extern const char *D_80408CF4[ ];
extern s32 D_80408CFC[ ];
extern u8 D_80408D40[ ] [ 2 ];
extern u8 D_80408D54[ ];
extern u8 D_80408D5C[ ];
extern M2C_UNK D_80408D64;
extern s32 D_80408D6C;
extern M2C_UNK D_80408D74;
extern short D_80408EC8[ ];
extern void (*D_804090E0[])(struct CardChooserBody *menu);
extern M2C_UNK D_80409110;
extern M2C_UNK D_80409128;
extern s32 card_slot_state_repeat_count[ ];
extern s32 card_last_polled_slot_state[ ];
extern s32 card_channel_state_repeat_count[ ];
extern s32 card_last_polled_channel_event[ ];
extern s32 dev_card_sw_done_event;
extern s32 dev_card_sw_error_event;
extern s32 dev_card_sw_timeout_event;
extern s32 dev_card_sw_new_event;
extern s32 dev_card_hw_done_event;
extern s32 dev_card_hw_error_event;
extern s32 dev_card_hw_timeout_event;
extern s32 dev_card_hw_new_event;
extern s32 D_804094E8_2[ 4 ];
extern s32 D_804094E8_3[ 4 ];
extern s32 D_804094E8_4[ 4 ];
extern s32 D_804094EC_2[ ];
extern s32 card_stable_slot_state[ ];
extern s32 card_debounced_channel_flags[ ];
extern s32 card_dev_hardware_status;
extern u8 card_message_object[ ];
extern u16 D_80409526;
extern u8 D_80409C90[ ];
extern u16 D_80409CAE;
extern u8 D_8040A0F0[ ];
extern u8 D_8040C318[ ];
extern u16 D_8040C336;
extern u16 D_8040C5DE;
extern u8 D_80410000[ ];
extern u8 D_804F281B[ ];
extern u8 D_805030EF[ ];
extern u8 attract_scene_index[ ];
extern s32 dev_card_directory_counts[ ];
extern s32 display_registration_tag;
extern u8 runtime_state_restore_requested;
extern u8 save_heading_chain_indices[];
extern u8 settings_palette_rect;


/* Imported data with no C definition (decision 74), formerly one-symbol headers. */
/* Devkit card-server directory records at 0x80409290. The search routines
 * advance by 0x28 bytes; the remaining-block reader uses the size at 0x18. */
typedef struct DevCardDirectoryEntry {
    u8 name[0x18];
    s32 file_size;
    u8 reserved[0xC];
} DevCardDirectoryEntry;

extern DevCardDirectoryEntry dev_card_directory[];

#endif
