---
tags: [xungram, log]
---
# Журнал работ

Хронология изменений. Связь: [[XunGram]].

## 2026-10-12
### Документы
- Спецификация: `docs/superpowers/specs/2026-10-12-xungram-design.md` ✅
- План: `docs/superpowers/plans/2026-10-12-xungram-implementation.md` ✅

### M0.4 — слой кода
- Создан `extra/` ([[Слой Extra]]) + изолированный CMake-блок. ✅

### M0.5 — первый шов
- `Extra::Hooks::OnUpdate()` в `api/api_updates.cpp` — [[Швы|seam.update-dispatch]]. ✅
- Создан `SEAMS.md`.

### M1 — каркас движка
- C++: `host/manifest.*`, `host/engine.*`; `Extra::Initialize()` в `core/application.cpp`
  — [[Швы|seam.app-startup]]. ✅

### Python
- [[Python SDK]] (`plugin/hooks/manifest/loader`) ✅
- Примеры `hello`, `translate` ✅
- Тесты: **8 проходят** ✅

### Нативная сборка ([[Сборка нативный Arch]])
- Собраны [[tde2e]], [[tdesktop_rust]], [[tg_owt]] → `.deps/*`.
- Починен последний блокер configure: `gdbus-codegen` — собран из исходников
  GNOME/glib → `.deps/gdbus-codegen` (см. [[Исправления сборки]]).
- **Configure tdesktop ✅**; запущена сборка (2292 шага, `-j3`).
- Починен блокер `g-ir-scanner` из-за **пробела в пути**: папка переименована
  в `/home/xunkal1/telegram-client` (старое имя — symlink). GIR-шаги проходят ✅.

## Связанные заметки
- [[Исправления сборки]]
- [[Вехи]]
