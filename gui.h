#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include "controller.h"

namespace Ui {
class GUI;
}

class GUI : public QMainWindow
{
    Q_OBJECT

public:
    Controller* controller_;

    explicit GUI(QWidget *parent = nullptr);
    ~GUI();

private slots:
    void on_selectDatabaseBtn_clicked();

private:
    Ui::GUI *ui;

    void displayDbData();
};

#endif // GUI_H
