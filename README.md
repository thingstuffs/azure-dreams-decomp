# azure-dreams-decomp

Readable C reconstruction of *Azure Dreams* for PlayStation, NTSC-U
(`SLUS-006.14`), checked against a user-supplied disc. Independent community
research, unaffiliated with Konami. **No disc, extracted game assets, retail
binary dumps, SDK payloads or compiled objects are supplied.** You need your
own disc; see [NOTICE](NOTICE).

At BASE `964157065`:

- **6,258 C files**, containing **8,213 physical function definitions**;
  **7,557 (92.0%)** have identifiers other than address placeholders. This
  counts helpers and physical copies, before expanding includes or placements.
  [Counting conventions](docs/guide/README.md#counts-and-identities) explain
  why this differs from the row count.
- **21,432 function and data rows**, **8,028,304 bytes**, all byte-identical;
  **1,490/1,490 make images exact**. Some image bytes are imported gaps;
  matching an image does not mean all its contents were compiled from C.
- Overlay code is **99.0% C**, or **99.5%** including proven copies of C;
  SLUS has separate accounting. Readability levels by bytes: **L3 90.6%,
  L4 14.9%, L5 14.6%**; **zero pin sites**. See [STATUS.md](STATUS.md) for
  denominators, limits and the generated snapshot.

## Build

<a id="quick-start"></a>

Use Linux and the prerequisites in [setup](tools/setup.sh) and
[the toolchain lock](tools/toolchain.lock.json). Put your NTSC-U BIN/CUE in
`bin/`, using the setup defaults `Azure Dreams.bin` and `Azure Dreams.cue`:

```sh
bash tools/setup.sh
bash tools/setup.sh --check
make configure
make -j4
make check
```

`make` builds the registered images; `make check` compares them to your disc
and writes the content-bound proof used by quality accounting. Native module
proof also needs the pinned genuine ASPSX assembler from your own Psy-Q SDK;
without it the run is labelled `maspsx_only`. Installation, image coverage,
imported bytes and incremental builds are explained in
[docs/BUILD.md](docs/BUILD.md) and [Psy-Q setup](docs/TOOLCHAIN_PSYQ.md).

## Read the code

Start with the [reader guides](docs/guide/README.md):

| Source folder | Read |
| --- | --- |
| `src/slus/` | [Executable and resident services](docs/guide/slus.md) |
| `src/engine/` | [Shared game systems](docs/guide/engine.md) |
| `src/main/` | [MAIN and the card server](docs/guide/main.md) |
| `src/frontend/` | [Card menus and settings](docs/guide/frontend.md) |
| `src/town/` | [Town scenes, people and shops](docs/guide/town.md) |
| `src/dungeon/` | [Floors, actors and monsters](docs/guide/dungeon.md) |
| `src/movie/`, `src/ovmovie/` | [Movie playback](docs/guide/movie.md) |

Folders describe source ownership; row IDs and disc containers retain their
historical identities. To find the editable TU without a disc:

```sh
python3 tools/source_layout.py path town/func_8008D54C
```

Shared records and subsystem interfaces live in `include/`. `config/` records
symbols, recipes and placements; `ledger/` records rows, layout and evidence;
`link/` and `tools/` implement the build and checks. See the
[documentation index](docs/README.md) and [contribution guide](CONTRIBUTING.md).

Git contains reconstructed source, including initialized C tables, headers,
configuration, tools and documentation. Those C tables remain game material;
their inclusion does not grant rights in Konami's work. Disc files (`bin/`),
extracts (`work/disc/`), provisioned tools (`toolchain/`), `.venv/`, and build
outputs (`build/`, `build_slus/`, `build_ovl/`) are untracked. See
[.gitignore](.gitignore) and [publication decision 67](docs/evidence/r97_decisions.md).

## Contribute and credit

Use short, evidence-backed names and shared types, and preserve the matching
bytes. [CONTRIBUTING.md](CONTRIBUTING.md) and the
[naming rules](docs/guide/README.md#naming-and-ownership) describe the workflow.
Check the reader documentation with `python3 tools/docs/check_links.py`.

Community foundations include **Azure Dreams De-Randomizer** (address/table
findings; no code copied) and **sotn-decomp** (structure vocabulary). Build and
research tools include splat, m2c, maspsx, decompals old-gcc, mkpsxiso,
spimdisasm and GNU binutils. Full credits and rights are in [NOTICE](NOTICE).
Original project work is under [The Unlicense](LICENSE); third-party parts
retain their licences.
