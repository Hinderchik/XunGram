---
tags: [xungram, python]
---
# Python SDK

Пакет `sdk/xungram/` — публичный API v1 для [[Движок плагинов|плагинов]].

## Модули
| Модуль | Содержимое |
|---|---|
| `__init__.py` | экспорт верхнего уровня |
| `plugin.py` | `BasePlugin`, `Message`, `MessageContext` |
| `hooks.py` | декораторы + `replace_text` / `cancel_read` |
| `manifest.py` | `Manifest`, `load`, `ManifestError` |
| `loader.py` | `load_plugin` |

## Примеры
- `plugins/hello/` — `manifest.json` + `main.py`
- `plugins/translate/` — `manifest.json` + `main.py`

## Тесты
`sdk/tests/test_sdk.py` — **8 тестов проходят** (python3, без pytest).

## Упаковка
`sdk/pyproject.toml` (setuptools), `py.typed`.

## Связанные заметки
- [[Движок плагинов]]
- [[Вехи]]
- [[Журнал работ]]
