/* Movie frame playback (G00427).
 * Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - group G00427 - CL:ovmovie/func_80040360, CL:ovmovie/func_800403EC, CL:ovmovie/func_80040690, CL:ovmovie/func_8004072C, CL:ovmovie/func_800408BC, CL:ovmovie/func_80040954, CL:ovmovie/func_80040ED8, PD:ovmovie/ovmovie_bin:801781D0.
 */
#include "ovmovie/movie_frame_playback_g00427.h"

/* Polls for a result and switches buffers when the result is negative. */
s32 decode_next_movie_frame(void *buffer_state) {
    s32 result;
    s32 buffer_index;
    s32 polls_left;

    polls_left = 0x800000;
    while (1) {
        result = poll_movie_frame_and_update_dimensions(buffer_state);
        if (result != 0) {
            break;
        }
        if (--polls_left == 0) {
            return 0;
        }
    }
    if (result > 0) {
        return 0;
    }
    buffer_index = *((s32 *)buffer_state + 2) == 0;
    *((s32 *)buffer_state + 2) = buffer_index;
    func_80177E6C(result, *((void **)buffer_state + buffer_index));
    func_80063734(result);
    return 1;
}

s32 poll_movie_frame_and_update_dimensions(u8 *display) {
    s32 data;
    FrameInfo *info;
    s32 polls_left = 0x800000;
    s32 width;
    s32 rounded;
    MovieState *movie;
    MovieState *dimensions;
    while (func_80063828(&data,&info)) {
        func_80060D90(1,movie_cd_status);
        if (movie_cd_status[0] & 0x10) return 1;
        if (--polls_left == 0) return 0;
    }
    if (info->frame >= (u32)movie_stop_frame) active_movie->done = 1;
    movie = active_movie;
    movie_frame_number = info->frame;
    if (movie->width != info->width || movie->height != info->height) {
        movie->width = info->width;
        movie->height = info->height;
    }
    if (movie_rgb24_mode & 1) width = (active_movie->width * 3) / 2;
    else width = (u16)active_movie->width;
    *(s16 *)(display + 0x1C) = width;
    *(s16 *)(display + 0x14) = width;
    dimensions = active_movie;
    *(s16 *)(display + 0x16) = *(s16 *)(display + 0x1E) = dimensions->height;
    rounded = dimensions->height + 15;
    if (rounded < 0) rounded = dimensions->height + 30;
    ((FrameDisplay *)display)->rounded_height = rounded & 0xFFF0;
    return data;
}

/* Waits for readiness, switching entries and copying the selected pair on timeout. */
void wait_for_movie_strip_completion(MovieEntity *entity, s32 unused) {
    volatile s32 timeout;
    s32 entry_index;
    u16 *entry;
    s32 entry_stride;

    timeout = 0x800000;
    if (entity->unk2C == 0) {
        do {
            timeout = timeout - 1;
            if (0 == timeout) {
                entity->unk2C = 1;
                entry_index = entity->unk20 == 0;
                entity->unk20 = entry_index;
                entry = (u16 *) ((s32) entity + (entry_index * 8) + 0x10);
                entry_stride = 8;
                entity->unk24 = *entry;
                entity->unk26 = *(u16 *) ((s32) entity + (entity->unk20 * entry_stride) + 0x12);
            }
        } while (entity->unk2C == 0);
    }
    entity->unk2C = 0;
}

/* Start operation 0x15 and wait for the 0x1C0 completion check. */
void start_movie_cd_stream_and_wait_ready(void *playback_state) {
    Control_CD(0x15, func_80061350(), 0);
    drain_cd_command_queue();
    do {

    } while (func_80063424(0x1C0) == 0);
}

static inline s32 movie_skip_requested(s32 buttons,s32 previous) {
    s32 requested = 0;
    if (scene_mode_code == 30 || scene_mode_code == 32 || scene_mode_code == 1) {
        if (buttons) requested = 1;
    } else if (~previous & buttons & 0x9F0) requested = 1;
    return requested;
}

s32 play_movie_frames_with_skip_fade(s32 unused,s32 frame_limit,s32 stream,s32 mode) {
    MovieDisplayEnv display;
    MovieDrawEnv draw;
    s32 fade_started = 0;
    s32 fade_step = 1;
    s32 frames = 0;
    s32 previous_buttons;
    u8 **screen_slot = (u8 **)&g_game_work;

    movie_stop_frame = frame_limit - 8;
    movie_frame_number = 0;
    active_movie = (MovieState *)movie_work_buffer;
    func_8006124C(stream,movie_work_buffer);
    if (mode) initialize_movie_frame_buffers((MovieBuffer *)((u8 *)active_movie + 4),0,0,0,240);
    else initialize_movie_frame_buffers((MovieBuffer *)((u8 *)active_movie + 4),0,0,0,224);
    initialize_movie_decoder_and_start_stream(active_movie,upload_movie_strip_and_advance_buffer);
    if (decode_next_movie_frame((u8 *)active_movie + 4)) {
        func_80066F78(1);
        if (active_movie->height >= 225) {
            func_80066424(&display,active_movie->screen[1].x,active_movie->screen[1].y,active_movie->screen[1].w,active_movie->screen[1].h);
            func_8006636C(&draw,active_movie->screen[1].x,active_movie->screen[1].y,active_movie->screen[1].w,active_movie->screen[1].h);
        }
        if (movie_rgb24_mode & 1) {
            display.rgb24 = 1;
            display.viewport.w = (display.viewport.w * 2) / 3;
        }
        if (active_movie->height >= 225) {
            func_800678E0(&display);
            func_80067688(&draw);
        } else {
            func_800678E0(*screen_slot + 0x5C);
            func_80067688(*screen_slot);
        }
        previous_buttons = 0;
        while (1) {
            configure_decoder_command_flags(active_movie->frame_buffers[active_movie->frame_buffer_index],(movie_rgb24_mode & 1) | 2);
            request_decoder_output_dma((s32)active_movie->output,(active_movie->strip.w * active_movie->strip.h) / 2);
            if (!decode_next_movie_frame((u8 *)active_movie + 4)) break;
            wait_for_movie_strip_completion((MovieEntity *)((u8 *)active_movie + 4),0);
            func_8005FE18(2);
            if (active_movie->height >= 225) {
                s32 index = !active_movie->screen_index;
                func_80066424(&display,active_movie->screen[index].x,active_movie->screen[index].y,active_movie->screen[index].w,active_movie->screen[index].h);
                func_8006636C(&draw,active_movie->screen[index].x,active_movie->screen[index].y,active_movie->screen[index].w,active_movie->screen[index].h);
            } else {
                u8 *buffer = upper_draw_context;
                if (active_movie->screen_index) buffer += 0x108D4;
                *screen_slot = buffer;
            }
            if (movie_rgb24_mode & 1) {
                display.rgb24 = 1;
                display.viewport.w = (display.viewport.w * 2) / 3;
            }
            if (active_movie->height >= 225) {
                func_800678E0(&display);
                func_80067688(&draw);
            } else {
                func_800678E0(*screen_slot + 0x5C);
                func_80067688(*screen_slot);
            }
            if (movie_frame_number >= frame_limit - 8 || frames >= frame_limit - 3) break;
            ++frames;
            if (active_movie->done == 1) break;
            if (!fade_started) {
                s32 old_buttons = previous_buttons;
                s32 skip;
                previous_buttons = read_combined_controller_buttons(1);
                skip = 0;
                skip = movie_skip_requested(previous_buttons,old_buttons);
                if (skip) {
                    fade_started = 1;
                    fade_step = (movie_volume + 9) / 10;
                } else if (movie_frame_number >= frame_limit - 20) {
                    fade_started = 1;
                    {
                        s32 brightness = movie_volume;
                        s32 rounded = brightness + 7;
                        if (rounded < 0) rounded = brightness + 14;
                        fade_step = (u32)rounded >> 3;
                    }
                }
                if (!fade_started) continue;
            }
            movie_volume -= (s16)fade_step;
            if (movie_volume < 0) movie_volume = 0;
            submit_scaled_driver_halfword_pair(0,(s16)movie_volume,(s16)movie_volume);
            if (!movie_volume) {
                submit_tagged_driver_byte(0,0,0);
                break;
            }
        }
    }
    display.rgb24 = 0;
    /* The integer ratio truncates to one. This compiler retains the width
       read (retail word 310) while deleting the redundant store. */
    display.viewport.w *= 3 / 2;
    if (active_movie->height >= 225) func_800678E0(&display);
    else func_800678E0(*screen_slot + 0x5C);
    func_80063538();
    return 0;
}
