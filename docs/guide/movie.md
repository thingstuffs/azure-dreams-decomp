# Movie / OVMOVIE: requests, frames and decoder services

[Guide index](README.md) · [Scene loading](engine.md)

Movie work crosses three source locations. Scene-side wrappers request a
movie; the OVMOVIE game code manages playback and display restoration; the
movie/playback file implements decoder services. The
[OVMOVIE row index](../../src/ovmovie/INDEX.md) maps the latter two locations
to rows in the `OVMOVIE.BIN` container named by the
[file catalog](../../config/link_graph/files.000.jsonl).

## Folder map

| Location | Responsibility and reading entry point |
| --- | --- |
| `src/engine/movie/`, `src/engine/scene/` | [`town_movie_exe`](../../src/engine/movie/town_movie_exe.c) records sector/control values; [`play_scene_movie`](../../src/engine/scene/play_scene_movie.c) refreshes dispatch state after playback |
| `src/ovmovie/game_movie_playback_g01063.c` | [`play_selected_movie_and_restore_display`, `play_movie_frames_with_skip_fade`](../../src/ovmovie/game_movie_playback_g01063.c) and the frame/buffer helpers |
| `src/ovmovie/modules/` | The retained [`ovmovie_game.c`](../../src/ovmovie/modules/ovmovie_game.c) is an include wrapper; use the merged implementation above for the game-side function bodies |
| `src/movie/playback/libpress.c` | [`set_movie_decode_mode`, `reset_decoder_and_load_tables`, `request_decoder_output_dma`](../../src/movie/playback/libpress.c): decoder initialization, tables and hardware transfers |

The merged game file labels its original-file evidence **inferred-weak**;
that is its stated evidence level, not proof of an original filename.
[`libpress.c`](../../src/movie/playback/libpress.c) includes its initialized
tables and hardware register pointers as C source. Movie video/audio assets
are not supplied by those C files.

## Follow one playback

[`town_movie_exe`](../../src/engine/movie/town_movie_exe.c) writes
`movie_frame_control` and `movie_start_sector`, invokes
`play_selected_movie_and_restore_display`, then reloads dispatch entry zero's
files. In the
[game implementation](../../src/ovmovie/game_movie_playback_g01063.c), that
playback entry adjusts audio/display state, extracts control bits and calls
`play_movie_frames_with_skip_fade`; afterward it resets streaming callbacks,
clears display areas and restores draw buffers.

In the same file, `play_movie_frames_with_skip_fade` initializes frame buffers
and streaming, requests decoder output, waits for strips and alternates display
buffers. `movie_skip_requested` uses scene mode and button history; a skip or
the approaching frame limit starts the volume fade. `decode_next_movie_frame`
polls for input and changes the active decode buffer; `poll_movie_frame_and_update_dimensions`
updates frame number, dimensions and rounded strip height from frame metadata.

The relevant views are `MovieState`, `MovieBuffer`, `MovieEntity`, `FrameInfo`
and display/draw environments, declared through
[`movie_display_setup_g00426.h`](../../include/ovmovie/movie_display_setup_g00426.h)
and [`movie_frame_playback_g00427.h`](../../include/ovmovie/movie_frame_playback_g00427.h).
The merged file's
[`owning header`](../../include/ovmovie/game_movie_playback_g01063.h) includes
both interfaces. Start at the particular helper's argument type rather than
treating all movie buffers as one interchangeable layout.

## Overlay and stream loading

The type-4 branch of
[`load_scene_resource_group`](../../src/engine/scene/load_scene_resource_group.c)
calls [`load_movie_overlay_once`](../../src/engine/scene/load_shared_resource_once.c)
and selects movie sector/control data. The latter queues the shared descriptor
once and marks it loaded after draining the CD queue. Inside playback,
`start_movie_cd_stream_and_wait_ready` submits CD command 0x15 and waits for
stream readiness in the
[game file](../../src/ovmovie/game_movie_playback_g01063.c).

These branches distinguish preparing the shared resource from starting the
movie stream. For the OVMOVIE load image and imported-byte accounting, use
[BUILD.md](../BUILD.md); the guide does not infer load addresses or asset names
from the source-folder names.
