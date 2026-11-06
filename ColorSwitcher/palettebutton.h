#ifndef PALETTEBUTTON_H
#define PALETTEBUTTON_H

#include <QColor>
#include <QPushButton>

// Кнопка-цвет. Создаётся динамически (в рантайме),
// хранит свой QColor. При нажатии добавляет цвет в палитру холста.
class PaletteButton : public QPushButton
{
    Q_OBJECT

public:
    explicit PaletteButton(const QColor& color, QWidget* parent = nullptr);
    ~PaletteButton() override;

    // Геттер с телом в заголовке — неявный inline. Это допустимо, потому что реализация одна и та же во всех .cpp.
    QColor color() const { return m_color; }

private:
    QColor m_color;
};

#endif 