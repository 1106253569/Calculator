
#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("计算器");

    ui->mainLineEdit->setEnabled(false);

    connect(ui->mainLineEdit,SIGNAL(returnPressed()),this,SLOT(on_commitButton_clicked()));

    //Lamada
    connect(ui->cancelButton,&QPushButton::clicked,this,[this](){
        if(QMessageBox::question(this,"NOTE","确定清空?")==QMessageBox::Yes)
        {
            expression.clear();
            ui->mainLineEdit->clear();

        }
    });
}

Widget::~Widget()
{
    delete ui;
}



void Widget::on_commitButton_clicked()
{
    QString postfixExpression = infixToPostfix(expression);

    double result = evaluatePostfix(postfixExpression);
    qDebug() << "Result:" << result;

    expression=QString::number(result);
    ui->mainLineEdit->setText(expression);

}


void Widget::on_number_0_clicked()
{
    expression+="0";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_1_clicked()
{
    expression+="1";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_2_clicked()
{
    expression+="2";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_3_clicked()
{
    expression+="3";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_4_clicked()
{
    expression+="4";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_5_clicked()
{
    expression+="5";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_6_clicked()
{
    expression+="6";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_7_clicked()
{
    expression+="7";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_8_clicked()
{
    expression+="8";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_number_9_clicked()
{
    expression+="9";
    ui->mainLineEdit->setText(expression);
}
void Widget::on_deleteButton_clicked()
{
    expression.chop(1);
    ui->mainLineEdit->setText(expression);
}

void Widget::on_addButton_clicked()
{
    expression+="+";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_divButton_clicked()
{
    expression+="/";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_mulButton_clicked()
{
    expression+="*";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_subButton_clicked()
{
    expression+="-";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_rightButton_clicked()
{
    expression+=")";
    ui->mainLineEdit->setText(expression);
}


void Widget::on_leftButton_clicked()
{
    expression+="(";
    ui->mainLineEdit->setText(expression);
}

void Widget::on_modButton_clicked()
{
    expression+="%";
    ui->mainLineEdit->setText(expression);
}

bool  Widget::isOperator(const QChar &c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}

int Widget::precedence(const QChar &op)
{
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/' || op == '%')
        return 2;
    return 0;
}

QString Widget::infixToPostfix(const QString &infix) {
    QString postfix;
    QStack<QChar> operatorStack;

    for (const QChar &c : infix) {
        if (c.isDigit() || c == '.') {
            postfix += c;
        } else if (isOperator(c)) {
            while (!operatorStack.isEmpty() && precedence(operatorStack.top()) >= precedence(c)) {
                postfix += operatorStack.pop();
            }
            operatorStack.push(c);
        } else if (c == '(') {
            operatorStack.push(c);
        } else if (c == ')') {
            while (!operatorStack.isEmpty() && operatorStack.top() != '(') {
                postfix += operatorStack.pop();
            }
            operatorStack.pop(); // Pop '('
        }
    }

    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.pop();
    }

    return postfix;
}

double Widget::evaluatePostfix(const QString &postfix) {
    QStack<double> operandStack;

    for (const QChar &c : postfix) {
        if (c.isDigit() || c == '.') {
            operandStack.push(c.digitValue());
        } else if (isOperator(c)) {
            double operand2 = operandStack.pop();
            double operand1 = operandStack.pop();
            double result = 0;
            switch (c.toLatin1()) {
            case '+':
                result = operand1 + operand2;
                break;
            case '-':
                result = operand1 - operand2;
                break;
            case '*':
                result = operand1 * operand2;
                break;
            case '/':
                result = operand1 / operand2;
                break;
            case '%':
                result = static_cast<int>(operand1) % static_cast<int>(operand2);
                break;
            }
            operandStack.push(result);
        }
    }

    return operandStack.pop();
}

