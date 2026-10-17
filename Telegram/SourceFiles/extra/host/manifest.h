/*
This file is part of XunGram,
a Telegram desktop client with an open plugin system.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <optional>

namespace Extra::Host {

inline constexpr int kApiVersion = 1;

struct Manifest {
	QString id;
	QString name;
	QString version;
	int apiVersion = 0;
	QString author;
	QString entry;
	QStringList permissions;
	QString path;
};

[[nodiscard]] std::optional<Manifest> ParseManifest(
	const QString &directory,
	QString *error);

} // namespace Extra::Host
