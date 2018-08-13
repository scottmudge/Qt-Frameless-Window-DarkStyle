/*
###############################################################################
#                                                                             #
# The MIT License                                                             #
#                                                                             #
# Copyright (C) 2017 by Juergen Skrotzky (JorgenVikingGod@gmail.com)          #
#               >> https://github.com/Jorgen-VikingGod                        #
#                                                                             #
# Sources: https://github.com/Jorgen-VikingGod/Qt-Frameless-Window-DarkStyle  #
#                                                                             #
###############################################################################
*/

#ifndef _DarkStyle_HPP
#define _DarkStyle_HPP

#include <QApplication>
#include <QProxyStyle>
#include <QStyleFactory>
#include <QFont>
#include <QFile>


class DarkStyle : public QProxyStyle
{
	Q_OBJECT

public:
	DarkStyle();
	explicit DarkStyle(QStyle *style);
	explicit DarkStyle(const QString& style_config);


	QStyle *baseStyle() const;

	void polish(QPalette &palette) override;
	void polish(QApplication *app) override;

private:
	QPalette mPalette;
	QStyle *styleBase(QStyle *style = Q_NULLPTR) const;

	void toJSON(const QString& filename) const;
	void fromJSON(const QString& filename);

	static QJsonObject jsonFromColor(const QColor& color);

	static QColor colorFromJSON(const QJsonObject &json);
};

#endif  // _DarkStyle_HPP
