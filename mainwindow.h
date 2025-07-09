#include <vector>
#include <string>

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets/QPushButton>

enum class Action
{
    None,
    Plus,
    Minus,
    Multiply,
    Divide,
    Modulus,
    Sqrt
};

struct Operation
{
    Action action = Action::None;
    double number = 0.0f;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *m_UI;
    bool m_IsPeriod = false;
    bool m_IsOperation = false;
    QString m_CurrentNumber;
    std::vector<Operation> m_Operations;
    std::vector<QPushButton*> m_Buttons;
};
#endif // MAINWINDOW_H
