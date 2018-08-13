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

#include "DarkStyle.h"
#include <QJsonObject>
#include <QMessageBox>
#include <QJsonDocument>

//==============================================================================
DarkStyle::DarkStyle() :
	DarkStyle(styleBase())
{ }

//==============================================================================
DarkStyle::DarkStyle(QStyle *style) :
	QProxyStyle(style)
{
	mPalette.setColor(QPalette::Window, QColor(53, 53, 53));
	mPalette.setColor(QPalette::WindowText, Qt::white);
	mPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
	mPalette.setColor(QPalette::Base, QColor(42, 42, 42));
	mPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
	mPalette.setColor(QPalette::ToolTipBase, Qt::white);
	mPalette.setColor(QPalette::ToolTipText, QColor(53, 53, 53));
	mPalette.setColor(QPalette::Text, Qt::white);
	mPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
	mPalette.setColor(QPalette::Dark, QColor(35, 35, 35));
	mPalette.setColor(QPalette::Shadow, QColor(20, 20, 20));
	mPalette.setColor(QPalette::Button, QColor(53, 53, 53));
	mPalette.setColor(QPalette::ButtonText, Qt::white);
	mPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
	mPalette.setColor(QPalette::BrightText, Qt::red);
	mPalette.setColor(QPalette::Link, QColor(238, 135, 21));
	mPalette.setColor(QPalette::Highlight, QColor(238, 135, 21));
	mPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
	mPalette.setColor(QPalette::HighlightedText, Qt::white);
	mPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));
}

//==============================================================================
DarkStyle::DarkStyle(const QString& style_config) : DarkStyle(styleBase())
{
	fromJSON(style_config);
}

//==============================================================================
QStyle *DarkStyle::styleBase(QStyle *style) const {
	static QStyle *base = !style ? QStyleFactory::create(QStringLiteral("Fusion")) : style;
	return base;
}

//==============================================================================
void DarkStyle::toJSON(const QString& filename) const
{
	QJsonObject json;
	json["Window"] = jsonFromColor(mPalette.color(QPalette::Window));
	json["WindowText"] = jsonFromColor(mPalette.color(QPalette::WindowText));
	json["WindowTextDisabled"] = jsonFromColor(mPalette.color(QPalette::Disabled, QPalette::WindowText));
	json["Base"] = jsonFromColor(mPalette.color(QPalette::Base));
	json["AlternateBase"] = jsonFromColor(mPalette.color(QPalette::AlternateBase));
	json["ToolTipBase"] = jsonFromColor(mPalette.color(QPalette::ToolTipBase));
	json["ToolTipText"] = jsonFromColor(mPalette.color(QPalette::ToolTipText));
	json["Text"] = jsonFromColor(mPalette.color(QPalette::Text));
	json["TextDisabled"] = jsonFromColor(mPalette.color(QPalette::Disabled, QPalette::Text));
	json["Dark"] = jsonFromColor(mPalette.color(QPalette::Dark));
	json["Shadow"] = jsonFromColor(mPalette.color(QPalette::Shadow));
	json["Button"] = jsonFromColor(mPalette.color(QPalette::Button));
	json["ButtonText"] = jsonFromColor(mPalette.color(QPalette::ButtonText));
	json["ButtonTextDisabled"] = jsonFromColor(mPalette.color(QPalette::Disabled, QPalette::ButtonText));
	json["BrightText"] = jsonFromColor(mPalette.color(QPalette::BrightText));
	json["Link"] = jsonFromColor(mPalette.color(QPalette::Link));
	json["Highlight"] = jsonFromColor(mPalette.color(QPalette::Highlight));
	json["HighlightDisabled"] = jsonFromColor(mPalette.color(QPalette::Disabled, QPalette::Highlight));
	json["HighlightedText"] = jsonFromColor(mPalette.color(QPalette::HighlightedText));
	json["HighlightedTextDisabled"] = jsonFromColor(mPalette.color(QPalette::Disabled, QPalette::HighlightedText));

	QFile file(filename);
	file.open(QIODevice::WriteOnly);
	if (!file.isOpen()) {
		QMessageBox msgBox(QMessageBox::Critical, "Critical Error", "Could not save style config: " + filename);
		msgBox.exec();
		exit(-1);
	}

	QJsonDocument doc(json);

	file.write(doc.toJson(QJsonDocument::Indented));

	file.close();
}

//==============================================================================
void DarkStyle::fromJSON(const QString& filename)
{

	QFile file(filename);
	file.open(QIODevice::ReadOnly);
	if (!file.isOpen()) {
		QMessageBox msgBox(QMessageBox::Critical, "Critical Error", "Could not load style config: " + filename);
		msgBox.exec();
		exit(-1);
	}

	QByteArray data = file.readAll();

	QJsonDocument doc(QJsonDocument::fromJson(data));
	QJsonObject json = doc.object();

	if (json.contains("Window") && json["Window"].isObject())
		mPalette.setColor(QPalette::Window, colorFromJSON(json["Window"].toObject()));
	if (json.contains("WindowText") && json["WindowText"].isObject())
		mPalette.setColor(QPalette::WindowText, colorFromJSON(json["WindowText"].toObject()));
	if (json.contains("WindowTextDisabled") && json["WindowTextDisabled"].isObject())
		mPalette.setColor(QPalette::Disabled, QPalette::WindowText, colorFromJSON(json["WindowTextDisabled"].toObject()));
	if (json.contains("Base") && json["Base"].isObject())
		mPalette.setColor(QPalette::Base, colorFromJSON(json["Base"].toObject()));
	if (json.contains("AlternateBase") && json["AlternateBase"].isObject())
		mPalette.setColor(QPalette::AlternateBase, colorFromJSON(json["AlternateBase"].toObject()));
	if (json.contains("ToolTipBase") && json["ToolTipBase"].isObject())
		mPalette.setColor(QPalette::ToolTipBase, colorFromJSON(json["ToolTipBase"].toObject()));
	if (json.contains("ToolTipText") && json["ToolTipText"].isObject())
		mPalette.setColor(QPalette::ToolTipText, colorFromJSON(json["ToolTipText"].toObject()));
	if (json.contains("Text") && json["Text"].isObject())
		mPalette.setColor(QPalette::Text, colorFromJSON(json["Text"].toObject()));
	if (json.contains("TextDisabled") && json["TextDisabled"].isObject())
		mPalette.setColor(QPalette::Disabled, QPalette::Text, colorFromJSON(json["TextDisabled"].toObject()));
	if (json.contains("Dark") && json["Dark"].isObject())
		mPalette.setColor(QPalette::Dark, colorFromJSON(json["Dark"].toObject()));
	if (json.contains("Shadow") && json["Shadow"].isObject())
		mPalette.setColor(QPalette::Shadow, colorFromJSON(json["Shadow"].toObject()));
	if (json.contains("Button") && json["Button"].isObject())
		mPalette.setColor(QPalette::Button, colorFromJSON(json["Button"].toObject()));
	if (json.contains("ButtonText") && json["ButtonText"].isObject())
		mPalette.setColor(QPalette::ButtonText, colorFromJSON(json["ButtonText"].toObject()));
	if (json.contains("ButtonTextDisabled") && json["ButtonTextDisabled"].isObject())
		mPalette.setColor(QPalette::Disabled, QPalette::ButtonText, colorFromJSON(json["ButtonTextDisabled"].toObject()));
	if (json.contains("BrightText") && json["BrightText"].isObject())
		mPalette.setColor(QPalette::BrightText, colorFromJSON(json["BrightText"].toObject()));
	if (json.contains("Link") && json["Link"].isObject())
		mPalette.setColor(QPalette::Link, colorFromJSON(json["Link"].toObject()));
	if (json.contains("Highlight") && json["Highlight"].isObject())
		mPalette.setColor(QPalette::Highlight, colorFromJSON(json["Highlight"].toObject()));
	if (json.contains("HighlightDisabled") && json["HighlightDisabled"].isObject())
		mPalette.setColor(QPalette::Disabled, QPalette::Highlight, colorFromJSON(json["HighlightDisabled"].toObject()));
	if (json.contains("HighlightedText") && json["HighlightedText"].isObject())
		mPalette.setColor(QPalette::HighlightedText, colorFromJSON(json["HighlightedText"].toObject()));
	if (json.contains("HighlightedTextDisabled") && json["HighlightedTextDisabled"].isObject())
		mPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, colorFromJSON(json["HighlightedTextDisabled"].toObject()));
}

//==============================================================================
QJsonObject DarkStyle::jsonFromColor(const QColor& color)
{
	QJsonObject json;
	json["r"] = color.redF();
	json["g"] = color.greenF();
	json["b"] = color.blueF();
	json["a"] = color.alphaF();
	return json;
}

//==============================================================================
QColor DarkStyle::colorFromJSON(const QJsonObject &json)
{
	QColor color;
	if (json.contains("r") && json["r"].isDouble())
		color.setRedF(json["r"].toDouble());
	if (json.contains("g") && json["g"].isDouble())
		color.setGreenF(json["g"].toDouble());
	if (json.contains("b") && json["b"].isDouble())
		color.setBlueF(json["b"].toDouble());
	if (json.contains("a") && json["a"].isDouble())
		color.setAlphaF(json["a"].toDouble());
	return color;
}

//==============================================================================
QStyle *DarkStyle::baseStyle() const
{
	return styleBase();
}

//==============================================================================
void DarkStyle::polish(QPalette &palette)
{
	palette = mPalette;
	// modify palette to dark

}

//==============================================================================
void DarkStyle::polish(QApplication *app)
{
	if (!app) return;

	// increase font size for better reading,
	// setPointSize was reduced from +2 because when applied this way in Qt5, the font is larger than intended for some reason
	QFont defaultFont = QApplication::font();
	defaultFont.setPointSize(defaultFont.pointSize() + 1);
	app->setFont(defaultFont);

	// loadstylesheet
	QFile qfDarkstyle(QStringLiteral(":/darkstyle/darkstyle.qss"));
	if (qfDarkstyle.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		// set stylesheet
		QString qsStylesheet = QString::fromLatin1(qfDarkstyle.readAll());
		app->setStyleSheet(qsStylesheet);
		qfDarkstyle.close();
	}

}
