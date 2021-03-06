#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QSerialPort>
#include "turnstile_manager.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_serial=new QSerialPort();
    my_timer=new QTimer(this);
    connect(my_timer,SIGNAL(timeout()),this,SLOT(this));
    m_serial->setPortName("...");
    m_serial->setBaudRate(QSerialPort::Baud9600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    m_serial->open(QIODevice::ReadWrite);

    send_serial_cb = send_over_serial;
    recived_serial_cb=recived_over_serial;
}

Widget::~Widget()
{
    m_serial->close();
    delete ui;
}


QSerialPort* Widget::m_serial = 0;

QByteArray  output;
QByteArray Read_buf;


void Widget::handleTimeout()
{
    my_timer->start(200);
    my_timer->stop();
}

const char* Widget::recived_over_serial(void){

   Widget handleTimeout;
   Read_buf= m_serial->readAll();

   return Read_buf;
}

int Widget::send_over_serial(const char* data,int size)
{
    return m_serial->write(data, size);
}

void Widget::on_pushButton_clicked()
{
    if(send_packet(TURNSTILE_VERSION_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_2_clicked()
{
    if(send_packet(TURNSTILE_SERIAL_NUMBER_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_3_clicked()
{
    if(send_packet(TURNSTILE_MOD_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_4_clicked()
{
    if(send_packet(TURNSTILE_FOTOSEL_STATE_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_5_clicked()
{
    if(send_packet(TURNSTILE_PASS_STATE_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_6_clicked()
{
    if(send_packet(TURNSTILE_TIME_RESTRICTED_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_7_clicked()
{
    if(send_packet(TURNSTILE_TIMEOUT_READ_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_8_clicked()
{
    if(send_packet(TURNSTILE_FREE_PASS_REQ_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}

void Widget::on_pushButton_9_clicked()
{
    if(send_packet(TURNSTILE_FLAP_STATE_CMD))
    qDebug()<<"Send packet is: well-done";
    else
    qDebug()<<"Send packet is failed :";
}


