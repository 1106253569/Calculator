
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include <QMessageBox>
#include <QStack>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget

{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_commitButton_clicked();

    void on_number_0_clicked();
    void on_number_1_clicked();
    void on_number_2_clicked();
    void on_number_3_clicked();
    void on_number_4_clicked();
    void on_number_5_clicked();
    void on_number_6_clicked();
    void on_number_7_clicked();
    void on_number_8_clicked();
    void on_number_9_clicked();

    void on_deleteButton_clicked();

    void on_addButton_clicked();
    void on_divButton_clicked();
    void on_mulButton_clicked();
    void on_subButton_clicked();
    void on_rightButton_clicked();
    void on_leftButton_clicked();

    void on_modButton_clicked();

private:
    QString expression;
    Ui::Widget *ui;
    int precedence(const QChar &op);
    QString infixToPostfix(const QString &infix);
    double evaluatePostfix(const QString &postfix);
    bool isOperator(const QChar &c);
};

#endif // WIDGET_H
