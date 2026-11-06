#include "palettebutton.h"
#include <QDebug>

PaletteButton::PaletteButton(const QColor& color, QWidget* parent)
    : QPushButton(parent)
    , m_color(color)
{
    // Подпись = hex-код цвета, чтобы видеть, какой цвет добавляем
    setText(color.name());
    setToolTip(QStringLiteral("Добавить этот цвет в палитру холста"));
    qDebug() << "[CREATE] PaletteButton" << color.name();
}

PaletteButton::~PaletteButton()
{
    // Логируем удаление — подтверждает жизненный цикл динамических объектов
    qDebug() << "[DESTROY] PaletteButton" << m_color.name();
}