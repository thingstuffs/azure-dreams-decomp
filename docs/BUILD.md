# Build and verify

Build the NTSC-U PlayStation release (`SLUS-006.14`) on Linux x86_64. Run all
commands from the repository root. You need your own disc image; no game
files, compiled objects or Psy-Q SDK are distributed. See [NOTICE](../NOTICE).

## 1. Install host prerequisites

On Ubuntu 24.04 or a comparable Debian-based system:

```sh
sudo apt-get update
sudo apt-get install build-essential binutils-mipsel-linux-gnu ninja-build \
    cmake python3-venv python3-yaml git curl
```

Use GNU Make 4.3 or newer and Python 3.10 or newer. `python3-yaml` is needed
by the system interpreter as well as the separate Python environment created
by setup. The pinned GCC executables are static 32-bit x86 binaries: the Linux
x86_64 kernel must support running 32-bit x86 executables. They need no dynamic
32-bit userspace loader. The optional wibo loader is a static x86_64 binary.
Other hosts are not covered by these instructions. The host packages and
external inputs are listed in [tools/toolchain.lock.json](../tools/toolchain.lock.json).

Clone this repository using the URL from its Code menu and enter the checkout.
In this example, set `REPOSITORY_URL` to that clone URL first:

```sh
git clone "$REPOSITORY_URL" azure-dreams-decomp
cd azure-dreams-decomp
```

## 2. Supply the disc

Create `bin/` and copy your own BIN/CUE into it:

```sh
mkdir -p bin
```

Use the filenames `bin/Azure Dreams.bin` and `bin/Azure Dreams.cue`. The
supported image is the USA single-data-track **MODE2/2352** dump, not an ISO,
a PAL/Japanese release or a modified image. Its locked identity is:

| Input | Expected value |
| --- | --- |
| BIN size | 298,576,992 bytes |
| BIN SHA-1 | `fab68454be5e4e48f7a43ac797cc8c47325c6a20` |
| Executable | `SLUS_006.14` |

Check your image before setup:

```sh
sha1sum 'bin/Azure Dreams.bin'
```

Alternatively, point `AZURE_CLEAN_DISC` at your BIN when running setup. That
variable selects the BIN; it does not convert other disc formats. Retain the
matching CUE alongside your original image.

## 3. Provision tools and extract the disc

```sh
export CMAKE_BUILD_PARALLEL_LEVEL=4
nice -n 10 bash tools/setup.sh
nice -n 10 bash tools/setup.sh --check
```

Setup needs network access on its first run. It creates `.venv/`, installs
splat and test dependencies, downloads and hash-checks the seven stock GCC
drops, connects the vendored maspsx assembler frontend, and builds the pinned
mkpsxiso/dumpsxiso with the repository patch. It verifies the disc hash and
extracts the executable into `baserom/` and overlay containers into
`work/disc/`. These local inputs and outputs are ignored by Git.

Read any `GAP:` messages before continuing. A nonzero exit means setup is
incomplete. `--check` checks an already provisioned tree and does not download
missing dependencies. It also runs the vendored maspsx tests when pytest is
available. Setup's final suggested window-gate commands are historical; use
the Make commands below for the current complete-image build.

### Optional genuine assembler comparison

For native translation units, the build can additionally compare maspsx/GNU
output with genuine **ASPSX 2.79**. Supply it from your own Psy-Q SDK. Setup
copies only the hash-pinned assembler and obtains the open-source wibo loader;
it neither supplies nor downloads the proprietary SDK.

Set `PSYQ_DIR` to your SDK directory, then run before configuration:

```sh
nice -n 10 bash tools/setup.sh --psyq "$PSYQ_DIR"
nice -n 10 bash tools/setup.sh --check --psyq "$PSYQ_DIR"
```

The pinned assembler is from SDK 4.4 (4.5 has the same file). SDK headers,
libraries, compilers and linker are not used. See the exact filenames, hashes
and local-loader option in [Psy-Q setup](TOOLCHAIN_PSYQ.md).

Without these inputs, Make records `maspsx_only`. A retail match from that
build does not establish genuine assembler comparison. Native diagnostic
window gates that require genuine comparison fail if the inputs are absent.
Rerun `make configure` after installing or changing them.

## 4. Configure, compile and compare

```sh
make configure
make -j4
make check
```

`make configure` generates the managed build views (`build_slus/`,
`build_ovl/`) and `build/build.mk` from the registered sources and recipes.
`make -j4` builds the images with at most four Make jobs. Compilation commands
run with reduced priority. `make check` rebuilds outdated products, compares
the images with your disc, and writes `build/check.json`. Success prints
`MATCH` lines and a final `CHECK N/N images SHA-1 MATCH` summary. A mismatch
prints `DIFF` with the image, offset and symbol information and returns failure.

A clean configuration and build can take substantial time and disk space.
Generated source views and build products belong in their ignored directories;
edit the source resolved by [the layout tool](SOURCE_LAYOUT.md), rather than a
copy under a build view. These commands build registered images, not a new
playable disc image.

## What the check proves

The build covers **402 load/file outputs**: SLUS, MAIN, OVMOVIE, two resident
engines, 60 town views and 337 dungeon banks. Additional `check_<recipe>` and
`check_place_<id>` images exercise compiled recipes and registered placements
outside those extents. These extra images are diagnostic layouts, not claims
that the game loads those combinations at runtime. The current snapshot has
1,490 checked images; consult [STATUS.md](../STATUS.md) for current coverage.

The checker:

- verifies the five disc containers against their registered sizes and hashes,
  then compares each image with its corresponding disc slice;
- checks that objects bind their current recipe, source/include inputs, tools
  and hashes, and that images bind their actual link inputs;
- refuses omitted images, unused compiled recipes, uncovered registered overlay
  rows and inputs changing during the check;
- separately compares loaded compiler-local switch-table contents, even when
  an image imports the table's bytes;
- records the actual assembler mode and content-bound results in
  `build/check.json` for quality accounting.

Explicit imported gaps copy unresolved bytes from your disc. They match by
construction and remain separate from compiled C, assembler and library bytes
in origin accounting. Matching every image proves the covered output bytes;
it does not prove complete C reconstruction, original source recovery,
historical linker recovery or runtime overlay exclusivity. Readability levels
L4/L5 add module/header and source-quality requirements. See
[quality definitions](PLAN.md), [fidelity limits](FIDELITY.md) and
[coverage accounting](LINK_LISTS.md).

Per-row verification and local overlay-window gates remain useful diagnostics.
Complete-image proof is the current integration check; module-certificate
renewal and the historical all-window loop are not required steps for this
workflow.

### Optional native compile check

The retail build compiles only the TUs its images link. A header change can
therefore pass `make check` and still break a host-native build of the same
source: retained row facades that retail no longer links, decoded-image TUs and
a native runtime's own C files all include the shared headers. Maintainers who
keep such a native port in a separate checkout can let the lander check it:

```sh
export AZURE_NATIVE_PORT=/path/to/native-port-checkout
bash tools/land_make.sh --message "..." change.patch
```

`tools/build/land_make.py` then runs that checkout's `port/tools/natcheck.py`
in a `native-check` step after the debt and layout checks and before
`make configure`, so a failure costs about a minute instead of a full build. The
checker reads this tree, compiles every native consumer with `-fsyntax-only`
and caches results by each unit's actual header dependencies; it writes nothing
here except `build/landing/native-check.log` and `.json`. A failure names each
unit with its compiler errors. Without the variable the step records `SKIP`;
`--require-native-check` turns that into a failure. Exit status 3 means every
unit compiles but a source hash pinned by the port is stale; the landing fails
unless `--allow-native-pin-drift` accepts it, and the port must refresh that
pin. No native port code is part of this repository.

## Incremental work and troubleshooting

After editing source, run `make -j4` and the relevant checks. Existing source
and header edits rebuild their consumers; a shared header or shared TU can
affect several images and containers. Adding/removing files or changing SDK
inputs requires `make configure`. Configuration and proof use content digests;
an old receipt alone does not prove a changed tree. See
[CONTRIBUTING.md](../CONTRIBUTING.md) for candidate checks and evidence.

### Scoped proof of an edit (build graph)

`tools/build/affected.py` proves a source/header edit on the generated build
graph itself, without `make configure` or a full build:

```sh
python3 tools/build/affected.py set include/town/scene.h            # recipes + images, no compile
python3 tools/build/affected.py prove --edited-from-git HEAD        # compile, compare, relink
python3 tools/build/affected.py prove --base ../master-root FILE... # baseline from another built root
```

The affected set is every current recipe in `build/.state/recipes` and
`slus-recipes` whose production dependency closure or own source contains an
edited file (placement copies are reached through their owner TU; SLUS
partition bodies through their render rule), plus every image that links one.
`prove` compiles each at its production arguments, evidence files and name
input into `build/.affected/<run>/`, compares raw object bytes and relocations
with the baseline `build/obj` (whose `.proof.json` must name the pre-edit
text), and relinks only images with a changed object. Verdicts are `PASS`,
`CHANGED` (with the first differing symbol), `STALE_BASE` or `ERROR`; the SLUS
image is judged by its objects. `tools/typing/tu_identity.py` and
`tools/headers/extern_wave.py` run it after their complete-TU filter
(`--proof build-graph`, the default when the root has a built tree).

The standalone typing captures (`layout_compile_identity.capture_one`, used by
`tu_identity`, `cast_wave`, `retype_family` and the probes) compile each row TU
at the cell, cc flags, maspsx flags and evidence tables of every linked
production recipe of that source, so they prove the object the build links
(`tools/build/census_proof_flags.py --all` measures capture against
`build/obj`). The first capture in a process loads the build graph (about ten
seconds); a root without a generated graph falls back to the registry recipe.

`tools/codemap/codemap.py build|refresh|check|query` keeps `build/codemap.db`,
a SQLite map of recipes, images, header closures, every declaration and call
site (clang), retail ABI facts per function and call (capstone over the linked
objects), per-placement call binding, names and debt sites. It is a build
artefact; `refresh` is incremental by source/closure and object hashes. The
binding (`tools/codemap/bind.py`) follows each image's link map and linked
bytes to the function a call site really reaches in its bank, so queries such
as `query voidret` join callers and callees per placement rather than by name.
`check` tells a lane whether a copied map is current for its tree (read-only;
exit 0 fresh, 1 stale): only files whose size or mtime differ from the stored
stat are hashed, `--full` hashes all. A successful `land_make.py` landing
refreshes an existing map at nice 10 under a time limit and never fails on it
(`build/landing/codemap.log`; `AZURE_CODEMAP_REFRESH=0` skips, `=1` also builds
a missing map, `AZURE_CODEMAP_TIMEOUT` seconds, default 600).

The map also keeps typing facts (`tools/codemap/typing_facts.py`, refresh phase `typing`): per registered
physical TU, one clang parse yields the pointer-cast census rows, every record layout with its members and
the TU's type-flow graph, stamped by include closure, recipe and extractor sources. A cold extraction is
about 3.5 minutes at six workers; a lane batch of a few dozen files refreshes in about 20 seconds; the phase
commits every 50 TUs, so a refresh stopped by the landing's time limit resumes on the next run
(`--no-typing` or `AZURE_CODEMAP_TYPING=0` skips it). `cast_census.py --codemap` and
`type_flow.py graph --codemap` read these facts instead of parsing, and refuse a stale map;
`codemap.py load-runtime DIR` / `load-flow DIR` add runtime evidence and type-flow holds, joined per
`file::function::param` by `query param`. A lane root seeded without link maps keeps the copied
`call_bind` rows instead of clearing them.

### Configure hash reuse

`mkbuild.py generate` runs bootstrap and recipe generation in one process. They
share one content snapshot, so files verified by bootstrap are not read again
when generation asks for the same SHA-256. A hash is reused only while the
file's device, inode, size, nanosecond mtime and ctime still match; a changed
identity is rehashed, and a change during a read aborts generation. The
snapshot lasts for this command only. Generated recipes and build rules remain
content-bound, including the normal tool-input hash in `build/build.mk`.

Configure stores include-closure checkpoints under a second guard. This guard
binds the exact `include_closure` entry point, all other configure authorities,
and source/header path presence; each cached closure also binds the content of
its discovered files. A change elsewhere in `mkbuild.py` can therefore reuse
those closure walks while the general row and recipe checkpoints regenerate.
Changing the walker, its entry point, a discovered file, or a path's presence
recomputes the affected closures. Generated rule bytes are still checked by
the ordinary configure output receipt.

### Post-build accounting reuse

`levels.py` and `status.py` cache row facts by their semantic input keys in
ignored `ledger/cache/row_facts/`. A missing cache is safe but makes the first
run expensive. On a current 1,530-image proof, a cold run computed 21,385
levels rows and 8,131 status rows; the next run hit all of those cache entries
and reproduced `ledger/levels.jsonl` byte for byte. `STATUS.md` changed only
its generated UTC timestamp. Set `AZURE_ROW_CACHE_STATS` to a path to record
hits, misses and phase times for a particular run.

Every run still validates the current image receipt and rebuilds dependency
keys, source context and source indexes. These checks account for much of a
warm run, especially when the shared disk is busy. The advisory codemap
refresh also runs after the final proof and writes only ignored
`build/codemap.db`; no later landing stage reads it. In a warm refresh with
zero Clang reparses and zero typing extractions, binding 93,371 call sites
still took 174.5 seconds. It can be scheduled outside the landing's critical
path by a caller that does not need a current map immediately.

The lander skips `levels.py` when the only changed accounting inputs are under
`tools/lint/` or `tools/typing/`, the previous levels output is intact, and
the current make receipt passes verification. It still runs `status.py` so its
UTC timestamp records that status generation. Source, evidence, build-proof,
and other tool changes retain the full accounting path.

| Symptom | Next step |
| --- | --- |
| Setup reports a wrong disc SHA-1 | Check the region, dump format and locked hash; supply an unmodified supported image |
| Missing `yaml`, `splat`, MIPS assembler or compiler | Install the host packages, rerun setup, then `--check`; splat belongs in `.venv/`, PyYAML must also import under `python3` |
| Genuine assembler input is missing or has a wrong hash | Follow [Psy-Q setup](TOOLCHAIN_PSYQ.md); verify the pinned version and configure again |
| Generated view or input stamp is stale | Rerun `make configure`, then build; edit the source authority rather than generated copies |
| `DIFF` after a source or type change | Keep the evidenced compiler recipe; inspect the named row/image and reduce the change before retrying |

For a build bug report, include the revision, host/tool versions, command,
exit status and the first useful failure. Attach compact text logs; omit game
files, SDK files, binary dumps and local private paths. The
[contribution guide](../CONTRIBUTING.md#report-a-problem) distinguishes build
failures, reconstruction errors and preserved [game bugs](BUGS.md).
