#include "common.h"

typedef struct { u8 pad[0x6F]; u8 mode; } Subwork;
typedef struct { u8 pad[0x40]; Subwork *subwork; } Work;
extern Work *town_scene_root;
void set_subwork_mode_3(void) { town_scene_root->subwork->mode = 3; }
