#ifndef WIDGET_H
#define WIDGET_H
#include <QSerialPort>
#include <QWidget>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    static QSerialPort* m_serial;
     QTimer *my_timer;

    static int send_over_serial(const char* data, int size);
    static const  char *recived_over_serial(void);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();
public slots:
    void handleTimeout();



private:
    Ui::Widget *ui;

};
#endif // WIDGET_H
