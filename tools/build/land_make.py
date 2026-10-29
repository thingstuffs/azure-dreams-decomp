"""Land reviewed text patches using complete make image proof.

A failure preserves the applied tree for inspection and never commits it.
Use --no-commit for a complete proof rehearsal. This is an opt-in successor;
it does not modify the old lander or run arbitrary package scripts.

Optional native compile check: the retail build compiles only linked TUs, so a
shared-header edit can break a host-native build of the same source (unlinked
row facades, decoded-image TUs, the native runtime's own C) without failing
make. When AZURE_NATIVE_PORT names a native port checkout (kept outside this
repository), the 'native-check' step runs its port/tools/natcheck.py against
this root before configure; it reads the tree and writes nothing in it besides
build/landing/native-check.{log,json}. Unset, the step records a SKIP. See
docs/BUILD.md, "Optional native compile check".

Code map refresh: after a landing succeeds, build/codemap.db (tools/codemap) is
refreshed incrementally at nice 10 under a time limit. It never fails a landing:
a refresh error or timeout is logged as a warning in build/landing/codemap.log.
AZURE_CODEMAP_REFRESH=0 skips it; unset, it runs only when the db already
exists; 1 also builds a missing db. AZURE_CODEMAP_TIMEOUT sets the limit in
seconds (default 600).
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import resource
import signal
import subprocess
import sys
import time

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
# Generic privacy patterns; personal strings (names, emails, private checkout names) are listed one per line in an
# untracked .scrub_patterns file (or $AZURE_SCRUB_PATTERNS) so the published tree never carries them.
PATTERNS = ('/'+'home/', 'claude.ai'+'/code')


def scrub_patterns(root):
    local = Path(os.environ.get('AZURE_SCRUB_PATTERNS') or root/'.scrub_patterns')
    extra = [l.strip() for l in local.read_text().splitlines()] if local.is_file() else []
    return PATTERNS + tuple(l for l in extra if l and not l.startswith('#'))


def command(argv, root):
    return subprocess.check_output(argv, cwd=root)


def scrub(root):
    changed = command(['git','diff','--name-only','-z','HEAD'], root).split(b'\0')
    changed += command(['git','ls-files','--others','--exclude-standard','-z'], root).split(b'\0')
    patterns = scrub_patterns(root)
    for name in sorted(set(changed)-{b''}):
        rel = os.fsdecode(name)
        p = root/rel
        if p.is_symlink():
            raise ValueError('landing refuses changed symlink: '+rel)
        if p.is_file():
            data = p.read_bytes()
            if any(pattern.encode() in data for pattern in patterns):
                raise ValueError('privacy scrub failed: '+rel)
            if b'\0' in data:
                raise ValueError('landing refuses binary file: '+rel)


# "No new debt" (owner 2026-10-16): changed C/headers may not add these beyond what HEAD had.
# Counted in code only (comments and string literals removed). asm is never waivable.
DEBT = {
    'asm': r'\b__asm__\b|\basm\s*(?:volatile\s*)?\(|\bINCLUDE_ASM\b|\bINCLUDE_RODATA\b',
    'volatile': r'\bvolatile\b',
    'NON_MATCHING': r'\bNON_MATCHING\b',
    'pragma': r'^\s*#\s*pragma\b',
    'goto': r'\bgoto\b',
    'm2c': r'\bM2C_\w+',
}
REPORT_ONLY = {'S_addr': r'\bS_[0-9A-Fa-f]{8}\w*'}
_COMMENT_OR_STRING = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|\'(?:\\.|[^\'\\\n])*\'', re.S)


def debt_counts(text):
    code = _COMMENT_OR_STRING.sub(lambda m: ' ' if m[0].startswith(('/', '"', "'")) else m[0], text)
    return {k: len(re.findall(v, code, re.M)) for k, v in {**DEBT, **REPORT_ONLY}.items()}


def debt_scan(root, allowed=()):
    """Compare debt in every changed src/ and include/ C file with its HEAD version."""
    changed = command(['git','diff','--name-only','-z','HEAD','--','src','include'], root).split(b'\0')
    changed += command(['git','ls-files','--others','--exclude-standard','-z','--','src','include'], root).split(b'\0')
    before, after, files = {}, {}, {}
    for name in sorted({os.fsdecode(n) for n in changed if n}):
        if not name.endswith(('.c', '.h')):
            continue
        try:
            old = subprocess.run(['git','show','HEAD:'+name], cwd=root, capture_output=True, check=True).stdout.decode('utf-8','replace')
        except subprocess.CalledProcessError:
            old = ''
        new = (root/name).read_text(errors='replace') if (root/name).is_file() else ''
        b, a = debt_counts(old), debt_counts(new)
        for k in b:
            before[k] = before.get(k, 0)+b[k]; after[k] = after.get(k, 0)+a[k]
        if a != b:
            files[name] = dict(before=b, after=a)
    report = dict(before=before, after=after, files=files, allowed=sorted(allowed))
    (root/'build/landing').mkdir(parents=True, exist_ok=True)
    (root/'build/landing/debt.json').write_text(json.dumps(report, indent=2, sort_keys=True)+'\n')
    grown = [k for k in DEBT if after.get(k, 0) > before.get(k, 0) and (k == 'asm' or k not in allowed)]
    if grown:
        raise ValueError('new debt in changed C: ' + ', '.join(f'{k} {before.get(k,0)}->{after[k]}' for k in grown)
                         + ' (build/landing/debt.json)')
    return report


NATIVE_PORT_ENV = 'AZURE_NATIVE_PORT'
NATIVE_CHECKER = Path('port/tools/natcheck.py')
NATIVE_PIN_DRIFT = 3  # natcheck: every unit compiles; only port-side source pins are stale


def native_check(root, jobs=4, require=False, allow_pin_drift=False, environ=None):
    """Run the configured native port's syntax check over every native consumer of this tree.

    Returns 'skipped', 'pass' or 'pin-drift'. Raises ValueError naming the
    failing units (first lines of build/landing/native-check.log) otherwise.
    """
    environ = os.environ if environ is None else environ
    root = Path(root)
    log_dir = root/'build/landing'
    log_dir.mkdir(parents=True, exist_ok=True)
    log = log_dir/'native-check.log'
    port = environ.get(NATIVE_PORT_ENV, '').strip()
    if not port:
        message = ('SKIP: no native port checkout configured; set '+NATIVE_PORT_ENV
                   +' to check native consumers (row facades, decoded TUs, runtime units)')
        log.write_text(message+'\n')
        print('native-check '+message)
        if require:
            raise ValueError('native check required but '+NATIVE_PORT_ENV+' is unset')
        return 'skipped'
    checker = Path(port).expanduser().resolve()/NATIVE_CHECKER
    if not checker.is_file():
        raise ValueError(NATIVE_PORT_ENV+' does not contain '+str(NATIVE_CHECKER))
    argv = [sys.executable, str(checker), '--root', str(root.resolve()), '--jobs', str(max(1, min(jobs, 4))),
            '--report', str(log_dir/'native-check.json')]
    with log.open('wb') as stream:
        code = subprocess.run(argv, cwd=root, stdout=stream, stderr=subprocess.STDOUT).returncode
    if code == 0:
        return 'pass'
    lines = log.read_text(errors='replace').splitlines()
    if code == NATIVE_PIN_DRIFT and allow_pin_drift:
        with log.open('a') as stream:
            stream.write('ACCEPTED: --allow-native-pin-drift; the native port must refresh these pins\n')
        return 'pin-drift'
    shown = []
    for i, line in enumerate(lines):
        if line.startswith(('natcheck: UNIT', 'natcheck: PIN', 'natcheck: ADAPTATION', 'NATCHECK')):
            shown.append(line)
            if line.startswith('natcheck: UNIT') and i+1 < len(lines) and lines[i+1].startswith('    '):
                shown.append(lines[i+1])  # the unit's first compiler error
    detail = '\n  '.join(shown[:16] + (['... '+str(len(shown)-16)+' more lines'] if len(shown) > 16 else []))
    hint = ' (pins only: --allow-native-pin-drift accepts this)' if code == NATIVE_PIN_DRIFT else ''
    raise ValueError('native check failed'+hint+' (see build/landing/native-check.log)'+('\n  '+detail if detail else ''))


CODEMAP_ENV = 'AZURE_CODEMAP_REFRESH'
CODEMAP_TIMEOUT_ENV = 'AZURE_CODEMAP_TIMEOUT'
CODEMAP_TIMEOUT = 600


def codemap_refresh(root, environ=None, timeout=None):
    """Refresh build/codemap.db after a successful landing. Never raises.

    Returns 'skipped', 'pass' or 'warning'; the reason is in build/landing/codemap.log.
    The refresh runs at nice 10 in its own process group, which is killed on timeout.
    """
    environ = os.environ if environ is None else environ
    root = Path(root)
    log = root/'build/landing/codemap.log'
    def finish(result, message):
        try:
            log.parent.mkdir(parents=True, exist_ok=True)
            with log.open('a') as stream:
                stream.write(message+'\n')
        except OSError:
            pass
        print('codemap-refresh '+message)
        return result
    try:
        log.parent.mkdir(parents=True, exist_ok=True)
        log.write_text('')
        mode = environ.get(CODEMAP_ENV, '').strip()
        if mode == '0':
            return finish('skipped', 'SKIP: '+CODEMAP_ENV+'=0')
        db = root/'build/codemap.db'
        if not db.exists() and mode != '1':
            return finish('skipped', 'SKIP: no build/codemap.db (codemap.py build creates it; '
                          +CODEMAP_ENV+'=1 builds it here)')
        tool = root/'tools/codemap/codemap.py'
        if not tool.is_file():
            return finish('warning', 'WARNING: tools/codemap/codemap.py is missing; map not refreshed')
        limit = timeout if timeout is not None else float(environ.get(CODEMAP_TIMEOUT_ENV) or CODEMAP_TIMEOUT)
        argv = ['nice', '-n', '10', sys.executable, str(tool), 'refresh', '--root', str(root.resolve())]
        started = time.monotonic()
        with log.open('ab') as stream:
            proc = subprocess.Popen(argv, cwd=root, stdout=stream, stderr=subprocess.STDOUT,
                                    start_new_session=True)
            try:
                code = proc.wait(timeout=limit)
            except subprocess.TimeoutExpired:
                # The refresh and its worker pool share the session this call created.
                os.killpg(proc.pid, signal.SIGTERM)
                try:
                    proc.wait(timeout=30)
                except subprocess.TimeoutExpired:
                    os.killpg(proc.pid, signal.SIGKILL)
                    proc.wait()
                return finish('warning', 'WARNING: refresh exceeded %gs and was stopped; the map is stale '
                              '(codemap.py refresh)' % limit)
        if code:
            return finish('warning', 'WARNING: refresh exited %d; the map may be stale (see this log)' % code)
        return finish('pass', 'PASS: refreshed in %.1fs' % (time.monotonic()-started))
    except Exception as exc:   # a landing never fails on its code map
        return finish('warning', 'WARNING: refresh not run: %s: %s' % (type(exc).__name__, exc))


def clean(root):
    """Cold proof: drop every object, link product and image so nothing stale can match."""
    import shutil
    for d in ('build/obj', 'build/.state/link', 'build/.state/native', 'build/.state/origins'):
        shutil.rmtree(root/d, ignore_errors=True)
    for f in (root/'build').glob('*.bin'):
        f.unlink()
    slus = root/'build_slus/build'
    if slus.is_dir():
        for f in slus.rglob('*.o'):
            f.unlink()
        for name in ('slus_006.14', 'slus_006.14.elf', 'slus_006.14.ok'):
            (slus/name).unlink(missing_ok=True)


def acknowledge_configuration(root):
    """Record successful verification for make's included-file mtime checks.

    Configure can verify identical generated bytes after an orchestration tool
    changes. A newer Makefile avoids repeating that verified generation during
    the build and check that follow. Object/input digest stamps are independent.
    """
    root = Path(root).resolve()
    path = root/'build/build.mk'
    if path.is_symlink() or not path.is_file() or not path.resolve().is_relative_to(root):
        raise ValueError('missing or unsafe generated Makefile after configure')
    path.touch()


def accounting(root, step):
    """Reuse deterministic accounting only with current image proof and exact outputs."""
    from tools.build import content_cache as C
    from tools.build.make_evidence import checked_receipt
    checked_receipt(root)
    # tools/status.py also regenerates the per-container source indexes (they carry each row's level): outputs.
    indexes = sorted(str(p.relative_to(root)) for p in (root/'src').glob('*/INDEX.md'))
    excluded = {'ledger/levels.jsonl', *indexes}
    def inputs():
        names = C.inventory(root, ('ledger', 'src', 'include', 'config', 'tools', 'docs'), excluded)
        names.add('build/check.json')
        return C.hashes(root, names)
    before = inputs()
    marker = root/'build/.state/accounting.json'
    previous = C.load(marker)
    outputs = ('ledger/levels.jsonl', 'STATUS.md', *indexes)
    if (previous.get('inputs') == before
            and previous.get('outputs') == C.hashes(root, outputs)
            and all(v is not None for v in previous['outputs'].values())):
        for name in ('levels', 'status'):
            step(name, action=lambda name=name: (root/'build/landing'/(name+'.log')).write_text(
                'SKIP: accounting inputs and output content unchanged; current make proof verified\n'))
        return
    step('levels', ['python3','tools/levels.py'])
    step('status', ['python3','tools/status.py'])
    if before != inputs():
        raise ValueError('accounting inputs changed during regeneration')
    checked_receipt(root)
    C.save(marker, dict(inputs=before, outputs=C.hashes(root, outputs)))


def main(argv=None, root=ROOT):
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--jobs', type=int, default=8)
    p.add_argument('--message', required=True)
    p.add_argument('--no-commit', action='store_true')
    p.add_argument('--require-genuine', action='store_true', help='retained for compatibility; genuine ASPSX is now required by default')
    p.add_argument('--allow-maspsx-only', action='store_true', help='accept a landing without the native genuine ASPSX comparison')
    p.add_argument('--incremental', action='store_true', help='normal landing mode with a current build/; default remains a cold rebuild')
    p.add_argument('--allow-debt', action='append', default=[], choices=sorted(set(DEBT)-{'asm'}),
                   help='accept growth of one debt category (recorded in debt.json); asm is never accepted')
    p.add_argument('--require-native-check', action='store_true',
                   help='fail instead of skipping when '+NATIVE_PORT_ENV+' is unset')
    p.add_argument('--allow-native-pin-drift', action='store_true',
                   help='accept a native check whose units all compile but whose port source pins are stale')
    p.add_argument('--test-module', action='append', default=[],
                   help='extra unittest module run after accounting (default: the make/lander tests)')
    p.add_argument('patches', nargs='+', type=Path)
    args = p.parse_args(argv)
    if args.jobs < 1:
        p.error('--jobs must be positive')
    if command(['git','status','--porcelain','--untracked-files=normal'],root).strip():
        raise ValueError('landing requires a clean worktree/index')
    patches = [q.resolve() for q in args.patches]
    for q in patches:
        if not q.is_file():
            raise ValueError('missing patch')
    steps = []
    log_dir = root/'build/landing'
    log_dir.mkdir(parents=True, exist_ok=True)
    def step(name, argv=None, action=None):
        start = time.monotonic(); cpu = resource.getrusage(resource.RUSAGE_CHILDREN); load = os.getloadavg()
        code = 0
        try:
            if action:
                action()
            else:
                with (log_dir/(name+'.log')).open('wb') as log:
                    code = subprocess.run(argv, cwd=root, stdout=log, stderr=subprocess.STDOUT).returncode
                if code:
                    raise ValueError('step failed: '+name+' (see build/landing/'+name+'.log)')
        except Exception:
            code = code or 1
            raise
        finally:
            after = resource.getrusage(resource.RUSAGE_CHILDREN)
            steps.append(dict(step=name, wall_seconds=time.monotonic()-start,
                              cpu_seconds=after.ru_utime+after.ru_stime-cpu.ru_utime-cpu.ru_stime,
                              returncode=code, load_start=list(load), load_end=list(os.getloadavg())))
            (log_dir/'timings.json').write_text(json.dumps(dict(steps=steps, complete=False),indent=2)+'\n')
    # A later patch may depend on an earlier one. Failures preserve the applied prefix.
    for i, patch in enumerate(patches):
        suffix = '' if len(patches)==1 else '_'+str(i+1)
        step('apply-check'+suffix, ['git','apply','--check',str(patch)])
        step('apply'+suffix, ['git','apply',str(patch)])
    step('scrub', action=lambda:scrub(root))
    step('debt', action=lambda:debt_scan(root, args.allow_debt))
    step('debt-baseline', [sys.executable, 'tools/lint/debt_check.py', '--check',
                           '--out', 'build/landing/readability-debt'])
    step('layout', ['python3','tools/source_layout.py','--root',str(root),'check'])
    step('registry', ['python3','tools/registry.py'])
    step('native-graph', ['python3','tools/gate/overlay_module_gate.py','--root',str(root),'--graph'])
    step('source-index', ['python3','tools/gen_src_index.py'])
    # Fail fast: about a minute cold, seconds warm, before the retail configure and build.
    native = {}
    step('native-check', action=lambda: native.update(result=native_check(
        root, args.jobs, args.require_native_check, args.allow_native_pin_drift)))
    step('configure', ['make','configure'])
    step('configure-mtime', action=lambda:acknowledge_configuration(root))
    if not args.incremental:
        step('clean', action=lambda:clean(root))
    step('build', ['make','-j'+str(args.jobs)])
    step('check', ['make','check'])
    if not args.allow_maspsx_only:
        def require():
            proof = json.loads((root/'build/check.json').read_text())
            if proof['assembler']['mode'] != 'genuine_aspsx_verified':
                raise ValueError('genuine ASPSX required; provision tools/setup.sh --psyq DIR')
        step('genuine', action=require)
    accounting(root, step)
    tests = ['tools.tests.test_mkbuild', 'tools.tests.test_land_make', 'tools.tests.test_make_negative'] + args.test_module
    env = dict(os.environ, PYTHONPATH=os.pathsep.join(str(root/d) for d in ('tools', 'tools/tests', '.')))
    def unit():
        with (log_dir/'unit.log').open('wb') as log:
            if subprocess.run([sys.executable,'-m','unittest',*tests], cwd=root, env=env, stdout=log, stderr=subprocess.STDOUT).returncode:
                raise ValueError('unit tests failed (see build/landing/unit.log)')
    step('unit', action=unit)
    step('final-scrub', action=lambda:scrub(root))
    # Accounting must not invalidate the checked source or image bytes.
    def freshness():
        import sys
        sys.path.insert(0,str(root/'tools'))
        from build.make_evidence import checked_receipt
        checked_receipt(root)
    step('final-proof', action=freshness)
    dirty = [os.fsdecode(n) for n in command(['git','diff','--name-only','-z','HEAD'],root).split(b'\0') if n]
    new = [os.fsdecode(n) for n in command(['git','ls-files','--others','--exclude-standard','-z'],root).split(b'\0') if n]
    staged = sorted(set(dirty+new))
    permitted = ('src/','include/','tools/','config/','docs/','ledger/','link/')  # link/ = byte maps / link lists
    if any(n not in ('Makefile','STATUS.md','.gitignore','README.md','CONTRIBUTING.md') and not n.startswith(permitted) for n in staged):
        raise ValueError('unexpected changed path outside landing trees')
    if not args.no_commit:
        if not staged:
            raise ValueError('empty landing')
        step('stage', ['git','add','--',*staged])
        step('commit', ['git','commit','-m',args.message])
    # The landing has succeeded; its code map refresh is advisory and never fails it.
    started, cpu, load = time.monotonic(), resource.getrusage(resource.RUSAGE_CHILDREN), os.getloadavg()
    codemap = codemap_refresh(root)
    after = resource.getrusage(resource.RUSAGE_CHILDREN)
    steps.append(dict(step='codemap', wall_seconds=time.monotonic()-started,
                      cpu_seconds=after.ru_utime+after.ru_stime-cpu.ru_utime-cpu.ru_stime,
                      returncode=0, load_start=list(load), load_end=list(os.getloadavg()), result=codemap))
    record = dict(complete=True, committed=not args.no_commit, steps=steps, native_check=native.get('result'),
                  codemap=codemap,
                  patches=[dict(name=q.name,sha256=hashlib.sha256(q.read_bytes()).hexdigest()) for q in patches],
                  changed_files=staged)
    (log_dir/'timings.json').write_text(json.dumps(record,indent=2)+'\n')
    print('LAND MAKE PASS'+(' (proof rehearsal; no commit)' if args.no_commit else ' (one commit)'))


if __name__ == '__main__':
    main()
