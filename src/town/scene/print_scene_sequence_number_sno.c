/* Relinked copy of town/func_80877FEC (func_80877FEC.c); its print interface slot is +0x64 (twin +0x68), otherwise retail differs only at relocation sites. */
#include "common.h"
#include "town/scene.h"
#include "town/data.h"

extern char D_000034B0[];
extern char D_000034BC[];
extern char D_000034C4[];
extern char D_000034CC[];
extern s32 scene_captured_value;
extern s32 scene_captured_flags;

/* Print kind, mode, and scene/sequence number (sno) with their labels. */
void print_scene_sequence_number_sno(s32 kind)
{
    overlay_trace_methods->print(D_000034B0, D_000034BC, kind);
    overlay_trace_methods->print(D_000034B0, D_000034C4, scene_captured_flags);
    overlay_trace_methods->print(D_000034B0, D_000034CC, scene_captured_value);
}
