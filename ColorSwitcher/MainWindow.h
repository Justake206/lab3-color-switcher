#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMetaObject>   // для QMetaObject::Connection
#include <QPointer>      // для безопасных указателей на кнопки
#include <QTimer>
#include <QWidget>
#include "colorwidget.h"
#include "palettebutton.h"

class QLabel;
class QVBoxLayout;
class QGridLayout;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void toggleTimer();            // старт/стоп таймера
    void decreaseInterval();       // медленнее
    void increaseInterval();       // быстрее
    void cycleMode();              // цикл/случайный/мигание
    void addColorButton();         // динамическое создание кнопки-цвета
    void clearPaletteButtons();    // очистка динамических кнопок
    void toggleClickHandler();     // переподключение обработчика клика

private:
    enum class Mode { Cycle, Random, Blink };

    void setupUi();
    void rebuildTimeoutConnection();  // пересоздать соединение timeout
    void reconnectCanvasHandler();    // пересоздать соединение colorChanged
    void setStatus(const QString& text);
    void updateIntervalLabel();
    void updateModelLabel();
    QString modeName() const;

    QTimer m_timer;           // таймер — член класса (живёт всё время)
    ColorWidget m_canvas;     // холст — тоже член класса
    Mode m_mode;              // текущий режим
    bool m_clickHandlerAlt;   // какой обработчик клика выбран

    // Соединения, которые можно разорвать вручную через disconnect()
    QMetaObject::Connection m_timeoutConn;
    QMetaObject::Connection m_clickConn;

    QVBoxLayout* m_rootLayout = nullptr;
    QGridLayout* m_paletteGrid = nullptr;
    QLabel* m_statusLabel = nullptr;
    QLabel* m_intervalLabel = nullptr;
    QLabel* m_modeLabel = nullptr;

    // QPointer защищает от висячих указателей — кнопки удаляются deleteLater
    QList<QPointer<PaletteButton>> m_paletteButtons;
    QList<QMetaObject::Connection> m_dynamicConnections;
};

#endif 