/*
This file is part of XunGram,
a Telegram desktop client with an open plugin system.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#include "extra/host/engine.h"

#include "base/debug_log.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>

namespace Extra::Host {
namespace {

[[nodiscard]] QString PluginsRoot() {
	return QStandardPaths::writableLocation(
		QStandardPaths::AppDataLocation) + u"/plugins"_q;
}

} // namespace

Engine::Engine() = default;

Engine::~Engine() = default;

void Engine::initialize() {
	discover();
	LOG(("XunGram: found %1 plugin(s)").arg(QString::number(_plugins.size())));
}

void Engine::discover() {
	_plugins.clear();
	auto directory = QDir(PluginsRoot());
	if (!directory.exists()) {
		return;
	}
	const auto entries = directory.entryInfoList(
		QDir::Dirs | QDir::NoDotAndDotDot,
		QDir::Name);
	for (const auto &entry : entries) {
		auto error = QString();
		auto manifest = ParseManifest(entry.absoluteFilePath(), &error);
		if (manifest) {
			_plugins.push_back(*manifest);
		} else {
			LOG(("XunGram: plugin skipped (%1): %2"
				).arg(entry.fileName(), error));
		}
	}
}

} // namespace Extra::Host
