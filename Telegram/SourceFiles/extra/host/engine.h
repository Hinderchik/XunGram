/*
This file is part of XunGram,
a Telegram desktop client with an open plugin system.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "extra/host/manifest.h"

#include <QtCore/QVector>

namespace Extra::Host {

class Engine final {
public:
	Engine();
	~Engine();

	void initialize();

	[[nodiscard]] const QVector<Manifest> &plugins() const {
		return _plugins;
	}

private:
	void discover();

	QVector<Manifest> _plugins;
};

} // namespace Extra::Host
