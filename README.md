# azure-dreams-decomp

Readable C reconstruction of *Azure Dreams* for PlayStation, NTSC-U
(`SLUS-006.14`), checked against a user-supplied disc. This is independent
community research, unaffiliated with Konami.

**Bring your own disc.** No disc images, extracted game files, retail binary
dumps, compiled objects or Psy-Q SDK are distributed. Reconstructed C includes
initialized game tables; those remain game material and the project licence
does not grant rights in Konami's work. See [NOTICE](NOTICE) and
[LICENSE](LICENSE).

## Current status

Snapshot at `f4f4ed991`, from [generated status](STATUS.md) and a fresh run of
[the readability census](tools/readability/score.py):

| Measurement | Result |
| --- | --- |
| Registered function and data rows | **21,432**, covering **8,028,304 bytes**, all recorded byte-identical |
| Registered build images | **1,490/1,490** matched in the recorded image proof |
| Overlay code reconstructed as C | **99.0%**, or **99.5%** including proven copies of C |
| Readability levels, by registered bytes | **L3 90.6%, L4 12.6%, L5 12.2%**; **zero pin sites** |
| Physical source census | **6,255 C files + 2 local headers**, **8,252 function definitions**; **8,117 (98.4%)** have names other than address placeholders |

These measurements have different denominators. The overlay C percentage
covers 7,619,712 classified or estimated code bytes in MAIN, TOWN, DUNGEON and
OVMOVIE; SLUS is accounted separately. The source census counts physical
spellings, including helpers and conditional definitions, without expanding
includes or multiplying placements. Names describe evidence-backed behavior;
they are not claimed to be recovered original identifiers. See
[counting conventions](docs/guide/README.md#counts-and-identities) and
[readability methodology](docs/READABILITY.md).

Byte-exact means that compiled output matches the corresponding retail bytes.
The complete build also imports unresolved gaps, data and library spans from
your disc. Those imported bytes match by construction: an exact image does not
mean every byte was reconstructed as C. The build checks compiled recipes,
placements and compiler-generated switch-table contents; readability and
historical compiler fidelity have additional requirements. See
[build proof](docs/BUILD.md#what-the-check-proves), [quality levels](docs/PLAN.md)
and [fidelity limits](docs/FIDELITY.md).

## Build

<a id="quick-start"></a>

Use Linux x86_64. Follow [the clean-machine steps](docs/BUILD.md) for host
packages, disc format and tool provisioning. Once prerequisites are installed,
put your NTSC-U BIN/CUE in `bin/` as `Azure Dreams.bin` and `Azure Dreams.cue`,
then run from the repository root:

```sh
bash tools/setup.sh
bash tools/setup.sh --check
make configure
make -j4
make check
```

Setup provisions the tools pinned in [the toolchain lock](tools/toolchain.lock.json)
and extracts your disc. For genuine ASPSX comparison of native translation
units, supply the assembler from your own [Psy-Q SDK](docs/TOOLCHAIN_PSYQ.md)
before configuration. Without it the build records `maspsx_only`; a matching
image alone does not claim genuine assembler comparison. The repository neither
includes nor downloads the proprietary SDK.

## Read the code

For how the game itself works (combat, leveling, familiars, items, dungeon generation, monsters, town), read
[the mechanics guide](docs/guide/mechanics/README.md), written from the code with links to each function.

Start with [the tree map](docs/LAYOUT.md) and [reader guides](docs/guide/README.md):

| Source folder | Read |
| --- | --- |
| `src/slus/` | [Executable and resident services](docs/guide/slus.md) |
| `src/engine/` | [Shared game systems](docs/guide/engine.md) |
| `src/main/` | [MAIN and the card server](docs/guide/main.md) |
| `src/frontend/` | [Card menus and settings](docs/guide/frontend.md) |
| `src/town/` | [Town scenes, people and shops](docs/guide/town.md) |
| `src/dungeon/` | [Floors, actors and monsters](docs/guide/dungeon.md) |
| `src/movie/`, `src/ovmovie/` | [Movie playback](docs/guide/movie.md) |

Folders describe source ownership. Stable row IDs retain disc-container and
address identities, so an ID need not resemble the current filename. Find the
editable translation unit without a disc:

```sh
python3 tools/source_layout.py path town/func_8008D54C
```

The [documentation index](docs/README.md) links deeper references.
[Known game bugs](docs/BUGS.md) maps player reports to code and retains credit
to the adrando randomizer guide and the Azure Dreams community.

## Contribute and credit

[CONTRIBUTING.md](CONTRIBUTING.md) explains how to support names and types,
prove changed bytes, and report a problem in the reconstruction. Keep source
readable, names short and meanings grounded in evidence. Check public links
with `python3 tools/docs/check_links.py README.md CONTRIBUTING.md docs/BUILD.md docs/LAYOUT.md docs/README.md docs/guide`.

Community foundations include **Azure Dreams De-Randomizer** (address/table
findings; no code copied) and **sotn-decomp** (structure vocabulary). Build and
research tools include splat, m2c, maspsx, decompals old-gcc, mkpsxiso,
spimdisasm and GNU binutils. Full credits and rights are in [NOTICE](NOTICE).
Original project work is under [The Unlicense](LICENSE); third-party parts
retain their licences.
