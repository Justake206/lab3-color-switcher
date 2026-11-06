#ifndef COLORWIDGET_H
#define COLORWIDGET_H

#include <QColor>
#include <QVector>
#include <QWidget>

// ColorWidget — холст, который рисует цвет и реагирует на мышь.
// Хранит палитру цветов и текущий индекс. При изменении цвета излучает
// собственный сигнал colorChanged(QColor) — мост между событием и сигналом.
class ColorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ColorWidget(QWidget* parent = nullptr);
    ~ColorWidget() override;

    void addColor(const QColor& c);    // добавить цвет в палитру
    void resetPalette();               // вернуть базовую палитру
    QColor currentColor() const;       // текущий цвет

    void stepForward();                // следующий цвет
    void stepBackward();               // предыдущий цвет
    void setRandomColor();             // случайный цвет
    void toggleBlink();                // мигание (чёрный/текущий)

signals:
    // Собственный сигнал: цвет изменился.
    // Демонстрирует связку "событие мыши -> сигнал для других объектов".
    void colorChanged(const QColor& color);

protected:
    void paintEvent(QPaintEvent* event) override;       // рисуем холст
    void mousePressEvent(QMouseEvent* event) override;  // клик мышью

private:
    QVector<QColor> m_palette;   // палитра цветов
    int m_index;                 // текущий индекс в палитре
    bool m_blinkOn;              // режим мигания включён?
    QColor m_blinkBackup;        // цвет, который запомнили перед миганием

    static QVector<QColor> defaultPalette();  // базовая палитра
    void emitCurrent();                       // излучить colorChanged
};

#endif