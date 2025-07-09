#include <cmath>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_UI(new Ui::MainWindow)
{
    m_UI->setupUi(this);

    QObject::connect(m_UI->Num0, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "0";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num1, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "1";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num2, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "2";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num3, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "3";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num4, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "4";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num5, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "5";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num6, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "6";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num7, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "7";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num8, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "8";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Num9, &QPushButton::clicked, [&]()
    {
        m_IsOperation = false;
        m_CurrentNumber += "9";
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Period, &QPushButton::clicked, [&]()
    {
        if (!m_IsPeriod)
        {
            m_CurrentNumber += ".";
            m_UI->ResultLine->setText(m_CurrentNumber);
            m_IsPeriod = true;
            m_IsOperation = false;
        }
    });
    QObject::connect(m_UI->OpPlus, &QPushButton::clicked, [&]()
    {
        if (!m_IsOperation && !m_CurrentNumber.isEmpty())
        {
            m_Operations.push_back({Action::Plus, std::stod(m_CurrentNumber.toStdString())});
            m_IsOperation = true;
            m_CurrentNumber.clear();
            m_UI->ResultLine->clear();
            m_IsPeriod = false;
        }
        else if (!m_Operations.empty())
        {
            m_Operations.back().action = Action::Plus;
        }
    });
    QObject::connect(m_UI->OpMinus, &QPushButton::clicked, [&]()
    {
        if (!m_IsOperation && !m_CurrentNumber.isEmpty())
        {
            m_Operations.push_back({Action::Minus, std::stod(m_CurrentNumber.toStdString())});
            m_IsOperation = true;
            m_CurrentNumber.clear();
            m_UI->ResultLine->clear();
            m_IsPeriod = false;
        }
        else if (!m_Operations.empty())
        {
            m_Operations.back().action = Action::Minus;
        }
    });
    QObject::connect(m_UI->OpDivide, &QPushButton::clicked, [&]()
    {
        if (!m_IsOperation && !m_CurrentNumber.isEmpty())
        {
            m_Operations.push_back({Action::Divide, std::stod(m_CurrentNumber.toStdString())});
            m_IsOperation = true;
            m_CurrentNumber.clear();
            m_UI->ResultLine->clear();
            m_IsPeriod = false;
        }
        else if (!m_Operations.empty())
        {
            m_Operations.back().action = Action::Divide;
        }
    });
    QObject::connect(m_UI->OpMultiply, &QPushButton::clicked, [&]()
    {
        if (!m_IsOperation && !m_CurrentNumber.isEmpty())
        {
            m_Operations.push_back({Action::Multiply, std::stod(m_CurrentNumber.toStdString())});
            m_IsOperation = true;
            m_CurrentNumber.clear();
            m_UI->ResultLine->clear();
            m_IsPeriod = false;
        }
        else if (!m_Operations.empty())
        {
            m_Operations.back().action = Action::Multiply;
        }
    });
    QObject::connect(m_UI->OpModulus, &QPushButton::clicked, [&]()
    {
        if (!m_IsOperation && !m_CurrentNumber.isEmpty())
        {
            m_Operations.push_back({Action::Modulus, std::stod(m_CurrentNumber.toStdString())});
            m_IsOperation = true;
            m_CurrentNumber.clear();
            m_UI->ResultLine->clear();
            m_IsPeriod = false;
        }
        else if (!m_Operations.empty())
        {
            m_Operations.back().action = Action::Modulus;
        }
    });
    QObject::connect(m_UI->Sign, &QPushButton::clicked, [&]()
    {
        if (m_CurrentNumber.front() == '-')
            m_CurrentNumber.erase(m_CurrentNumber.begin(), m_CurrentNumber.begin() + 1);
        else
            m_CurrentNumber.push_front('-');
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
    QObject::connect(m_UI->Equals, &QPushButton::clicked, [&]()
    {
        m_IsPeriod = false;
        m_IsOperation = false;
        if (m_Operations.empty())
        {
            m_CurrentNumber.clear();
            m_UI->ResultLine->clear();
            m_Operations.clear();
            return;
        }

        if (m_Operations.back().action != Action::None && m_CurrentNumber.isEmpty())
        {
            m_Operations.back().action = Action::None;
        }
        else
        {
            m_Operations.push_back({Action::None, std::stod(m_CurrentNumber.toStdString())});
            m_CurrentNumber.clear();
        }

        double result = 0.0f;
        int i = 0;
        while (!m_Operations.empty())
        {
            switch(m_Operations[i].action)
            {
            case Action::Divide:
            {
                if (m_Operations[i + 1].number == 0.0f)
                {
                    m_UI->ResultLine->setText("Invalid");
                    m_Operations.clear();
                    return;
                }
                else
                {
                    m_Operations[i + 1].number = m_Operations[i].number / m_Operations[i + 1].number;
                    m_Operations.erase(m_Operations.begin() + i);
                    i = 0;
                    break;
                }
            }
            case Action::Multiply:
            {
                m_Operations[i + 1].number = m_Operations[i].number * m_Operations[i + 1].number;
                m_Operations.erase(m_Operations.begin() + i);
                i = 0;
                break;
            }
            case Action::Modulus:
            {
                m_Operations[i + 1].number = std::fmod(m_Operations[i].number, m_Operations[i + 1].number);
                m_Operations.erase(m_Operations.begin() + i);
                i = 0;
                break;
            }
            case Action::Plus:
            {
                if (m_Operations[i + 1].action == Action::Divide || m_Operations[i + 1].action == Action::Multiply)
                {
                    i++;
                    break;
                }
                else
                {
                    m_Operations[i + 1].number = m_Operations[i].number + m_Operations[i + 1].number;
                    m_Operations.erase(m_Operations.begin() + i);
                    break;
                }
            }
            case Action::Minus:
            {
                if (m_Operations[i + 1].action == Action::Divide || m_Operations[i + 1].action == Action::Multiply)
                {
                    i++;
                    break;
                }
                else
                {
                    m_Operations[i + 1].number = m_Operations[i].number - m_Operations[i + 1].number;
                    m_Operations.erase(m_Operations.begin() + i);
                    break;
                }
            }
            case Action::None:
            {
                result = m_Operations[i].number;
                QString resultStr = "=";
                if (std::floor(result) == result)
                    resultStr.append(std::to_string(static_cast<int>(result)));
                else
                    resultStr.append(std::to_string(result));
                m_UI->ResultLine->setText(resultStr);
                m_Operations.clear();
                break;
            }
            }
        }
    });
    QObject::connect(m_UI->OpSqrt, &QPushButton::clicked, [&]()
    {
        m_IsPeriod = false;
        m_IsOperation = false;

        if (m_Operations.empty())
        {
            if (!m_CurrentNumber.isEmpty())
            {
                QString resultStr = "=";
                double number = std::sqrt(m_CurrentNumber.toDouble());
                if (std::floor(number) == number)
                    resultStr.append(std::to_string(static_cast<int>(number)));
                else
                    resultStr.append(std::to_string(number));
                m_UI->ResultLine->setText(resultStr);
            }
            else
            {
                m_UI->ResultLine->clear();
            }
            m_CurrentNumber.clear();
            m_Operations.clear();
            return;
        }

        if (m_Operations.back().action != Action::None && m_CurrentNumber.isEmpty())
        {
            m_Operations.back().action = Action::None;
        }
        else
        {
            m_Operations.push_back({Action::None, std::stod(m_CurrentNumber.toStdString())});
            m_CurrentNumber.clear();
        }

        double result = 0.0f;
        int i = 0;
        while (!m_Operations.empty())
        {
            switch(m_Operations[i].action)
            {
            case Action::Divide:
            {
                if (m_Operations[i + 1].number == 0.0f)
                {
                    m_UI->ResultLine->setText("Invalid");
                    m_Operations.clear();
                    return;
                }
                else
                {
                    m_Operations[i + 1].number = m_Operations[i].number / m_Operations[i + 1].number;
                    m_Operations.erase(m_Operations.begin() + i);
                    i = 0;
                    break;
                }
            }
            case Action::Multiply:
            {
                m_Operations[i + 1].number = m_Operations[i].number * m_Operations[i + 1].number;
                m_Operations.erase(m_Operations.begin() + i);
                i = 0;
                break;
            }
            case Action::Modulus:
            {
                m_Operations[i + 1].number = std::fmod(m_Operations[i].number, m_Operations[i + 1].number);
                m_Operations.erase(m_Operations.begin() + i);
                i = 0;
                break;
            }
            case Action::Plus:
            {
                if (m_Operations[i + 1].action == Action::Divide || m_Operations[i + 1].action == Action::Multiply)
                {
                    i++;
                    break;
                }
                else
                {
                    m_Operations[i + 1].number = m_Operations[i].number + m_Operations[i + 1].number;
                    m_Operations.erase(m_Operations.begin() + i);
                    break;
                }
            }
            case Action::Minus:
            {
                if (m_Operations[i + 1].action == Action::Divide || m_Operations[i + 1].action == Action::Multiply)
                {
                    i++;
                    break;
                }
                else
                {
                    m_Operations[i + 1].number = m_Operations[i].number - m_Operations[i + 1].number;
                    m_Operations.erase(m_Operations.begin() + i);
                    break;
                }
            }
            case Action::None:
            {
                result = std::sqrt(m_Operations[i].number);
                QString resultStr = "=";
                if (std::floor(result) == result)
                    resultStr.append(std::to_string(static_cast<int>(result)));
                else
                    resultStr.append(std::to_string(result));
                m_UI->ResultLine->setText(resultStr);
                m_Operations.clear();
                break;
            }
            }
        }
    });
    QObject::connect(m_UI->Cancel, &QPushButton::clicked, [&]()
    {
        m_IsPeriod = false;
        m_IsOperation = false;
        m_CurrentNumber.clear();
        m_Operations.clear();
        m_UI->ResultLine->clear();
    });
    QObject::connect(m_UI->Delete, &QPushButton::clicked, [&]()
    {
        if (m_CurrentNumber.isEmpty())
            return;

        if (m_CurrentNumber.back() == '.')
            m_IsPeriod = false;

        m_IsOperation = false;
        m_CurrentNumber.erase(m_CurrentNumber.end() - 1, m_CurrentNumber.end());
        m_UI->ResultLine->setText(m_CurrentNumber);
    });
}

MainWindow::~MainWindow()
{
    delete m_UI;
}
