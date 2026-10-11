"""Python test audit hook, installed as sitecustomize by the landing preflight.

This is an accidental-access tripwire for trusted tests, not a hostile-code
sandbox. Refuse canonical managed inputs even through aliases. Propagate into
Python subprocesses and reject commands/cwds naming the canonical checkout.
"""
import json
import os
from pathlib import Path
import sys

allowed=os.environ.get('LAND_TEST_ROOT')
forbidden=os.environ.get('LAND_TEST_FORBIDDEN')
audit=os.environ.get('LAND_TEST_AUDIT')
if allowed and forbidden and audit:
    allowed=Path(allowed).resolve();forbidden=Path(forbidden).resolve()
    shared=[forbidden/n for n in ('toolchain','.venv','baserom','bin')]
    # The compiler bundle's maspsx entry is a symlink into tools/maspsx.
    # It is an explicitly shared compiler input, not a canonical row/gate root.
    shared.append((forbidden/'toolchain/maspsx').resolve())
    checking=False
    def bad_path(value):
        if not isinstance(value,(str,bytes,os.PathLike)):return False
        path=Path(os.fsdecode(value)).resolve()
        return path.is_relative_to(forbidden) and not (allowed.is_relative_to(forbidden) and path.is_relative_to(allowed)) and not any(path.is_relative_to(p) for p in shared)
    def deny(event,value):
        with open(audit,'a') as f:f.write(json.dumps({'event':event,'path':str(value)})+'\n')
        raise PermissionError('test touched canonical root: '+str(value))
    def hook(event,args):
        global checking
        if checking:return
        checking=True
        try:
            if event in ('open','os.listdir','os.scandir','os.chdir','os.remove','os.rmdir','os.mkdir','os.chmod','os.truncate','os.utime'):
                if args and bad_path(args[0]):deny(event,args[0])
            if event in ('os.rename','os.link','os.symlink'):
                for arg in args[:2]:
                    if bad_path(arg):deny(event,arg)
            if event=='subprocess.Popen':
                exe,argv,cwd,_=args
                if cwd is not None and bad_path(cwd):deny(event,cwd)
                for value in (argv if isinstance(argv,(list,tuple)) else [argv]):
                    text=os.fsdecode(value)
                    # Remove allowed subtree references before detecting a shell
                    # command or --root argument with an absolute canonical path.
                    if allowed.is_relative_to(forbidden):text=text.replace(str(allowed),'')
                    for p in shared:text=text.replace(str(p),'')
                    if str(forbidden) in text:deny(event,value)
            if event=='os.system':
                text=os.fsdecode(args[0])
                if allowed.is_relative_to(forbidden):text=text.replace(str(allowed),'')
                if str(forbidden) in text:deny(event,args[0])
        finally:checking=False
    sys.addaudithook(hook)
