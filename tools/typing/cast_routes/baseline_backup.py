"""Preserve production baseline objects and receipts across failed batch proofs."""
import importlib.util
import json
from pathlib import Path
import shutil


class BaselineBackup:
    def __init__(self, root, directory, files):
        self.root=Path(root).resolve()
        self.directory=Path(directory)
        self.directory.mkdir(parents=True,exist_ok=True)
        (self.directory/'.ignore').write_text('*\n')
        self.files=sorted(set(files))
        self.present=[]
        for file in self.files:
            source=self.root/file
            assert source.resolve().is_relative_to(self.root), ('outside_root',file)
            exists=source.exists()
            self.present.append(exists)
            if exists:
                target=self.directory/file
                target.parent.mkdir(parents=True,exist_ok=True)
                shutil.copy2(source,target)
        (self.directory/'manifest.json').write_text(json.dumps(dict(files=self.files,present=self.present),indent=2)+'\n')

    @classmethod
    def for_sources(cls,root,directory,sources):
        spec=importlib.util.spec_from_file_location('lane_affected',Path(root)/'tools/build/affected.py')
        module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
        graph=module.Graph(root)
        scope=module.affected_set(root,sources,graph)
        files=[]
        baseline=module.Baseline(Path(root),Path(root),set(sources))
        for rid in scope['recipes']+scope['slus_recipes']:
            recipe=graph.recipes[rid]
            blob,problem=baseline.object(recipe)
            assert not problem, ('repair_baseline_before_batch',rid,problem)
            output=Path(recipe['output'])
            files.extend([output.as_posix(),output.with_suffix('.proof.json').as_posix()])
            if recipe.get('name_input'):
                files.append(recipe['name_input'])
        return cls(root,directory,files)

    def restore(self):
        for file,exists in zip(self.files,self.present):
            target=self.root/file
            if exists:
                target.parent.mkdir(parents=True,exist_ok=True)
                shutil.copy2(self.directory/file,target)
            else:
                target.unlink(missing_ok=True)
