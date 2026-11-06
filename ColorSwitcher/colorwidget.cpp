#include "colorwidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QRandomGenerator>

ColorWidget::ColorWidget(QWidget* parent)
    : QWidget(parent)
    , m_palette(defaultPalette())
    , m_index(0)
    , m_blinkOn(false)
    , m_blinkBackup(Qt::black)
{
    setMinimumSize(320, 220);
    setAutoFillBackground(true);
    qDebug() << "[CREATE] ColorWidget";
}

ColorWidget::~ColorWidget()
{
    qDebug() << "[DESTROY] ColorWidget";
}

QVector<QColor> ColorWidget::defaultPalette()
{
    // 6 базовых цветов — с них стартует палитра
    return {
        QColor("#e74c3c"),
        QColor("#e67e22"),
        QColor("#f1c40f"),
        QColor("#2ecc71"),
        QColor("#3498db"),
        QColor("#9b59b6")
    };
}

QColor ColorWidget::currentColor() const
{
    if (m_palette.isEmpty())
        return Qt::gray;
    return m_palette.at(m_index % m_palette.size());
}

void ColorWidget::addColor(const QColor& c)
{
    m_palette.push_back(c);
    qDebug() << "[PALETTE] Добавлен цвет" << c.name()
        << ", всего:" << m_palette.size();
}

void ColorWidget::resetPalette()
{
    m_palette = defaultPalette();
    m_index = 0;
    m_blinkOn = false;
    update();          // запросить перерисовку
    emitCurrent();
}

void ColorWidget::stepForward()
{
    if (m_palette.isEmpty()) return;
    // Переход к следующему цвету по кругу
    m_index = (m_index + 1) % m_palette.size();
    m_blinkOn = false;
    update();
    emitCurrent();
}

void ColorWidget::stepBackward()
{
    if (m_palette.isEmpty()) return;
    // Переход к предыдущему цвету с учётом отрицательного индекса
    m_index = (m_index - 1 + m_palette.size()) % m_palette.size();
    m_blinkOn = false;
    update();
    emitCurrent();
}

void ColorWidget::setRandomColor()
{
    if (m_palette.isEmpty()) return;
    m_index = QRandomGenerator::global()->bounded(m_palette.size());
    m_blinkOn = false;
    update();
    emitCurrent();
}

void ColorWidget::toggleBlink()
{
    if (m_blinkOn) {
        m_blinkOn = false;   // выключаем мигание — возвращаем исходный цвет
    }
    else {
        m_blinkBackup = currentColor();  // запоминаем цвет
        m_blinkOn = true;
    }
    update();
    emitCurrent();
}

void ColorWidget::emitCurrent()
{
    // Единая точка излучения сигнала — чтобы не забыть в каждом методе
    emit colorChanged(currentColor());
}

void ColorWidget::paintEvent(QPaintEvent* /*event*/)
{
    QPainter p(this);
    // При мигании рисуем чёрный, иначе — текущий цвет
    const QColor fill = m_blinkOn ? QColor(0, 0, 0) : currentColor();
    p.fillRect(rect(), fill);

    // Контрастный текст (белый на тёмном, чёрный на светлом)
    p.setPen(fill.lightness() > 128 ? Qt::black : Qt::white);
    p.drawText(rect(), Qt::AlignCenter, fill.name());
}

void ColorWidget::mousePressEvent(QMouseEvent* event)
{
    // Событие мыши переопределяет базовую обработку QWidget.
    // Левый клик — вперёд, правый — назад.
    if (event->button() == Qt::LeftButton) {
        qDebug() << "[MOUSE] Левый клик по холсту";
        stepForward();
    }
    else if (event->button() == Qt::RightButton) {
        qDebug() << "[MOUSE] Правый клик по холсту";
        stepBackward();
    }
    QWidget::mousePressEvent(event);  // передаём базовой обработке
}