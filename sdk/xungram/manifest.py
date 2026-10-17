import json
import os

REQUIRED = ("id", "name", "version", "api_version")


class ManifestError(Exception):
    pass


class Manifest:
    def __init__(self, data, path):
        for key in REQUIRED:
            if key not in data:
                raise ManifestError(f"manifest.json missing '{key}'")
        self.data = data
        self.path = path
        self.id = data["id"]
        self.name = data["name"]
        self.version = data["version"]
        self.api_version = int(data["api_version"])
        self.author = data.get("author", "")
        self.entry = data.get("entry", "main.py")
        self.permissions = list(data.get("permissions", []))

    @property
    def entry_path(self):
        return os.path.join(self.path, self.entry)


def load(directory):
    path = os.path.join(directory, "manifest.json")
    try:
        with open(path, "r", encoding="utf-8") as f:
            data = json.load(f)
    except FileNotFoundError:
        raise ManifestError(f"not found: {path}")
    except json.JSONDecodeError as error:
        raise ManifestError(f"invalid json: {error}")
    manifest = Manifest(data, directory)
    if not os.path.isfile(manifest.entry_path):
        raise ManifestError(f"entry not found: {manifest.entry_path}")
    return manifest
