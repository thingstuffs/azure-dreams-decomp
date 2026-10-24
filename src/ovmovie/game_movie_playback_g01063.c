/* Game movie playback and display lifecycle.
 * Evidence: inferred-weak.
 */
#include "ovmovie/game_movie_playback_g01063.h"

/* Plays the selected movie and resets both frame buffers afterward. */
void play_selected_movie_and_restore_display(void) {
    u8 *frame_buffers;
    s32 movie_flag;
    s32 saved_movie_flag;
    u8 *resident_globals_hi = (u8 *) 0x80080000;
    u8 *movie_globals_hi;

    runtime_dispatch_state.field_0 &= ~1;
    if (scene_music_hold == 0) {
        SD_Call(0x7F);
        drain_audio_commands_and_service_channels();
    }

    submit_tagged_driver_byte(0, 0, 1);
    movie_volume = 0x7F;
    submit_scaled_driver_halfword_pair(0, (s16) movie_volume, (s16) movie_volume);

    movie_flag = (u32) movie_frame_control >> 31;
    movie_globals_hi = (u8 *) 0x80180000;
    *(s32 *) (movie_globals_hi - 0x7E1C) = movie_flag;
    clear_movie_display_area(movie_flag);
    SetDispMask(0);

    frame_buffers = upper_draw_context;
    frame_buffers[0x6D] = 1;
    frame_buffers[0x10941] = 1;
    saved_movie_flag = *(s32 *) (movie_globals_hi - 0x7E1C);
    clear_movie_display_area(saved_movie_flag);

    movie_rgb24_mode = 1;
    set_movie_strip_offsets(0, ((movie_frame_control & 0x40000000) == 0) * 0x10);
    play_movie_frames_with_skip_fade(0, movie_frame_control & 0x3FFFFFFF, movie_start_sector, *(s32 *) (movie_globals_hi - 0x7E1C));
    SetDispMask(0);

    {
        u8 *active_buffer;

        active_buffer = *(u8 **) (resident_globals_hi + 0x3160);
        frame_buffers[0x6D] = 0;
        frame_buffers[0x10941] = 0;
        func_800678E0(active_buffer + 0x5C);
    }
    DrawSync(0);
    VSync(2);
    func_80060DE8(0);
    Control_CD(9, 0, 0);
    drain_cd_command_queue();
    register_mode_one_callback(0);
    func_80061208(0);
    DrawSync(0);
    clear_movie_display_area(*(s32 *) (movie_globals_hi - 0x7E1C));

    {
        u8 *active_buffer;
        u8 *next_buffer;

        active_buffer = *(u8 **) (resident_globals_hi + 0x3160);
        next_buffer = frame_buffers;
        frame_buffers[0x6D] = 0;
        frame_buffers[0x10941] = 0;
        if (active_buffer == frame_buffers) {
            next_buffer = frame_buffers + 0x108D4;
        }
        *(u8 **) (resident_globals_hi + 0x3160) = next_buffer;
        func_8006751C(next_buffer + 0x70, 0x218);
        func_80067688(*(void **) (resident_globals_hi + 0x3160));
    }
    VSync(0);
    {
        u8 *next_buffer;

        next_buffer = frame_buffers;
        if (*(u8 **) (resident_globals_hi + 0x3160) == frame_buffers) {
            next_buffer = frame_buffers + 0x108D4;
        }
        *(u8 **) (resident_globals_hi + 0x3160) = next_buffer;
        func_8006751C(next_buffer + 0x70, 0x218);
        func_80067688(*(void **) (resident_globals_hi + 0x3160));
    }
    VSync(0);
    clear_movie_display_area(*(s32 *) (movie_globals_hi - 0x7E1C));
}

/* Clears a 480-pixel-wide movie display area to black, using a height of 480 or 448. */
void clear_movie_display_area(s32 useFullHeight) {
    s16 clearRect[4];
    s16 extent;
    s32 blackComponent;

    DrawSync(0);
    extent = 0x1E0;
    clearRect[0] = 0;
    clearRect[1] = 0;
    clearRect[2] = extent;
    if (useFullHeight == 0) {
        extent = 0x1C0;
    }
    blackComponent = 0;
    clearRect[3] = extent;
    ClearImage(clearRect, blackComponent, blackComponent, blackComponent);
    DrawSync(0);
}

/* Stores two signed values in the movie state globals. */
void set_movie_strip_offsets(s16 value_d8, s16 value_dc) {
    movie_strip_x_offset = (s32) value_d8;
    movie_strip_y_offset = (s32) value_dc;
}

/* Reset movie state and apply the requested playback settings. */
void initialize_movie_decoder_and_start_stream(void *playback_state, void (*playback_option)(void)) {
    set_movie_decode_mode(0);
    *(s32 *)((u8 *)active_movie + 0x34) = 0;
    register_mode_one_callback(playback_option);
    func_80060B04((u8 *)active_movie + 0x40, 0x20);
    func_800636AC(movie_rgb24_mode & 1, 1, -1, 0, 0);
    start_movie_cd_stream_and_wait_ready(playback_state);
}

/* Initializes movie buffer pointers and frame rectangles for the current mode. */
void initialize_movie_frame_buffers(MovieBuffer *movie, s32 frame_x, s32 frame_y, s32 next_frame_x, s32 next_frame_y) {
    s32 buffer_offset = 0x15A40;
    s32 next_buffer_offset = 0x22AB0;
    s32 work_offset = 0x10040;
    u8 *buffer_base = (u8 *)active_movie;
    s32 movie_flags = *(s32 *)((u8 *)&movie_rgb24_mode + 0);   /* read through a plain pointer: the array spelling sets MEM_IN_STRUCT_P and reschedules the two global loads */

    movie->unk08 = 0;
    movie->unk20 = 0;
    movie->unk2C = 0;
    movie->unk00 = buffer_base + buffer_offset;
    movie->unk04 = buffer_base + next_buffer_offset;
    movie->unk0C = buffer_base + work_offset;
    if (movie_flags & 1) {
        movie->unk14 = 0x1E0;
        movie->unk1C = 0x1E0;
        movie->unk10 = frame_x;
        movie->unk12 = frame_y;
        movie->unk16 = 0xF0;
        movie->unk18 = next_frame_x;
        movie->unk1A = next_frame_y;
        movie->unk1E = 0xF0;
        movie->unk24 = frame_x;
        movie->unk26 = frame_y;
        movie->unk28 = 0x18;
        movie->unk2A = 0xF0;
    } else {
        movie->unk14 = 0x140;
        movie->unk1C = 0x140;
        movie->unk10 = frame_x;
        movie->unk12 = frame_y;
        movie->unk16 = 0xF0;
        movie->unk18 = next_frame_x;
        movie->unk1A = next_frame_y;
        movie->unk1E = 0xF0;
        movie->unk24 = frame_x;
        movie->unk26 = frame_y;
        movie->unk28 = 0x10;
        movie->unk2A = 0xF0;
    }
}

/* Uploads a decoded movie strip, then requests the next strip or marks the frame ready and swaps screens. */
void upload_movie_strip_and_advance_buffer(void) {
    MovieRect rectangle;
    MovieState *movie;
    if (movie_rgb24_mode & 1) {
        if (D_80086D8C) {
            func_8006390C();
            D_80086D8C = 0;
        }
    }
    rectangle = active_movie->strip;
    if (movie_rgb24_mode & 1) {
        rectangle.x += (movie_strip_x_offset / 3) * 3;
        rectangle.y += (movie_strip_y_offset / 3) * 3;
    } else {
        rectangle.x += movie_strip_x_offset;
        rectangle.y += movie_strip_y_offset;
    }
    LoadImage(&rectangle, active_movie->output);
    DrawSync(0);
    movie = active_movie;
    movie->strip.x += movie->strip.w;
    if (movie->strip.x < movie->screen[movie->screen_index].x + movie->screen[movie->screen_index].w) {
        request_decoder_output_dma((s32)movie->output, (movie->strip.w * movie->strip.h) / 2);
    } else {
        movie->ready = 1;
        movie->screen_index = !movie->screen_index;
        movie->strip.x = movie->screen[movie->screen_index].x;
        movie->strip.y = movie->screen[movie->screen_index].y;
    }
}

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

/* Polls the next movie frame, records its number and stop flag, and updates display dimensions. */
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
    Control_CD(0x15, func_80061350(playback_state), 0);
    drain_cd_command_queue();
    do {

    } while (func_80063424(0x1C0) == 0);
}

/*
 * Accepts any held button in scene modes 30, 32, or 1; other modes require a newly pressed button
 * in mask 0x9F0.
 */
static inline s32 movie_skip_requested(s32 buttons,s32 previous) {
    s32 requested = 0;
    if (scene_mode_code == 30 || scene_mode_code == 32 || scene_mode_code == 1) {
        if (buttons) requested = 1;
    } else if (~previous & buttons & 0x9F0) requested = 1;
    return requested;
}

/* Streams and displays movie frames, fading the audio when skipped or near the frame limit. */
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
        SetDispMask(1);
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
            VSync(2);
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
