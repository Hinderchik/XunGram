---
tags: [xungram, milestones]
---
# Вехи

План: `docs/superpowers/plans/2026-10-12-xungram-implementation.md`.

## Прогресс
```mermaid
graph LR
  M0[M0 Фундамент] --> M1[M1 Движок плагинов]
  M1 --> M2[M2 API v1]
  M2 --> M3[M3 Фичи]
  M3 --> M4[M4 Дистрибуция]
  style M0 fill:#2e7d32,color:#fff
  style M1 fill:#f9a825,color:#000
```

| Веха | Что | Статус |
|---|---|---|
| M0 | Фундамент: [[Слой Extra]], [[Швы]], [[Python SDK]] | ✅ почти (M0.1–M0.3 ждут пользователя) |
| M1 | Движок: CPython+pybind11, загрузка, изоляция, UI | 🟡 частично (C++ каркас есть) |
| M2 | [[Python SDK\|API v1]] + сопоставление C++ хост ↔ контракт | ⬜ |
| M3 | [[Фичи]] | ⬜ |
| M4 | Дистрибуция (AppImage/.deb/.rpm/Flatpak/AUR) | ⬜ |

## M0 детали
- M0.4 — слой `extra/` + [[Слой Extra|CMake-блок]] ✅
- M0.5 — первый [[Швы|шов]] (`seam.update-dispatch`) ✅
- M0.1–M0.3 — форк+remote, baseline-сборка, `api_id`/`api_hash` — ⛔ нужен пользователь.

## Связанные заметки
- [[Журнал работ]]
- [[Архитектура]]
