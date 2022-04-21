/********************************************************************************
** Form generated from reading UI file 'colectivos.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COLECTIVOS_H
#define UI_COLECTIVOS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Colectivos
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QComboBox *PuntoInicial;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *PuntoFinal;
    QTextBrowser *Texto;
    QPushButton *Calcular;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Colectivos)
    {
        if (Colectivos->objectName().isEmpty())
            Colectivos->setObjectName(QStringLiteral("Colectivos"));
        Colectivos->setEnabled(true);
        Colectivos->resize(771, 635);
        Colectivos->setAcceptDrops(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/52258550-icono-de-autob-s-bot-n-redondo-de-color-negro-brillante.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        Colectivos->setWindowIcon(icon);
        centralWidget = new QWidget(Colectivos);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setEnabled(true);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 10, 771, 491));
        label->setPixmap(QPixmap(QString::fromUtf8(":/mapa.bmp")));
        label->setScaledContents(true);
        PuntoInicial = new QComboBox(centralWidget);
        PuntoInicial->setObjectName(QStringLiteral("PuntoInicial"));
        PuntoInicial->setGeometry(QRect(90, 500, 69, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 500, 51, 16));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 540, 51, 16));
        PuntoFinal = new QComboBox(centralWidget);
        PuntoFinal->setObjectName(QStringLiteral("PuntoFinal"));
        PuntoFinal->setGeometry(QRect(90, 540, 69, 22));
        Texto = new QTextBrowser(centralWidget);
        Texto->setObjectName(QStringLiteral("Texto"));
        Texto->setGeometry(QRect(190, 510, 581, 111));
        Calcular = new QPushButton(centralWidget);
        Calcular->setObjectName(QStringLiteral("Calcular"));
        Calcular->setGeometry(QRect(50, 580, 75, 23));
        Colectivos->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Colectivos);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 771, 17));
        Colectivos->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Colectivos);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Colectivos->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Colectivos);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Colectivos->setStatusBar(statusBar);

        retranslateUi(Colectivos);

        QMetaObject::connectSlotsByName(Colectivos);
    } // setupUi

    void retranslateUi(QMainWindow *Colectivos)
    {
        Colectivos->setWindowTitle(QApplication::translate("Colectivos", "ComoLlego", 0));
        label->setText(QString());
        PuntoInicial->clear();
        PuntoInicial->insertItems(0, QStringList()
         << QApplication::translate("Colectivos", "1", 0)
         << QApplication::translate("Colectivos", "2", 0)
         << QApplication::translate("Colectivos", "3", 0)
         << QApplication::translate("Colectivos", "4", 0)
         << QApplication::translate("Colectivos", "5", 0)
         << QApplication::translate("Colectivos", "6", 0)
         << QApplication::translate("Colectivos", "7", 0)
         << QApplication::translate("Colectivos", "8", 0)
         << QApplication::translate("Colectivos", "9", 0)
         << QApplication::translate("Colectivos", "10", 0)
         << QApplication::translate("Colectivos", "11", 0)
         << QApplication::translate("Colectivos", "12", 0)
         << QApplication::translate("Colectivos", "13", 0)
         << QApplication::translate("Colectivos", "14", 0)
         << QApplication::translate("Colectivos", "15", 0)
         << QApplication::translate("Colectivos", "16", 0)
         << QApplication::translate("Colectivos", "17", 0)
         << QApplication::translate("Colectivos", "18", 0)
         << QApplication::translate("Colectivos", "19", 0)
         << QApplication::translate("Colectivos", "20", 0)
         << QApplication::translate("Colectivos", "21", 0)
         << QApplication::translate("Colectivos", "22", 0)
         << QApplication::translate("Colectivos", "23", 0)
         << QApplication::translate("Colectivos", "24", 0)
         << QApplication::translate("Colectivos", "25", 0)
         << QApplication::translate("Colectivos", "26", 0)
         << QApplication::translate("Colectivos", "27", 0)
         << QApplication::translate("Colectivos", "28", 0)
         << QApplication::translate("Colectivos", "29", 0)
         << QApplication::translate("Colectivos", "30", 0)
         << QApplication::translate("Colectivos", "31", 0)
        );
        label_2->setText(QApplication::translate("Colectivos", "Origen", 0));
        label_3->setText(QApplication::translate("Colectivos", "Destino", 0));
        PuntoFinal->clear();
        PuntoFinal->insertItems(0, QStringList()
         << QApplication::translate("Colectivos", "1", 0)
         << QApplication::translate("Colectivos", "2", 0)
         << QApplication::translate("Colectivos", "3", 0)
         << QApplication::translate("Colectivos", "4", 0)
         << QApplication::translate("Colectivos", "5", 0)
         << QApplication::translate("Colectivos", "6", 0)
         << QApplication::translate("Colectivos", "7", 0)
         << QApplication::translate("Colectivos", "8", 0)
         << QApplication::translate("Colectivos", "9", 0)
         << QApplication::translate("Colectivos", "10", 0)
         << QApplication::translate("Colectivos", "11", 0)
         << QApplication::translate("Colectivos", "12", 0)
         << QApplication::translate("Colectivos", "13", 0)
         << QApplication::translate("Colectivos", "14", 0)
         << QApplication::translate("Colectivos", "15", 0)
         << QApplication::translate("Colectivos", "16", 0)
         << QApplication::translate("Colectivos", "17", 0)
         << QApplication::translate("Colectivos", "18", 0)
         << QApplication::translate("Colectivos", "19", 0)
         << QApplication::translate("Colectivos", "20", 0)
         << QApplication::translate("Colectivos", "21", 0)
         << QApplication::translate("Colectivos", "22", 0)
         << QApplication::translate("Colectivos", "23", 0)
         << QApplication::translate("Colectivos", "24", 0)
         << QApplication::translate("Colectivos", "25", 0)
         << QApplication::translate("Colectivos", "26", 0)
         << QApplication::translate("Colectivos", "27", 0)
         << QApplication::translate("Colectivos", "28", 0)
         << QApplication::translate("Colectivos", "29", 0)
         << QApplication::translate("Colectivos", "30", 0)
         << QApplication::translate("Colectivos", "31", 0)
        );
        Calcular->setText(QApplication::translate("Colectivos", "Buscar", 0));
    } // retranslateUi

};

namespace Ui {
    class Colectivos: public Ui_Colectivos {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COLECTIVOS_H
