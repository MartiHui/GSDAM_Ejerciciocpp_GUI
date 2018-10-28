#ifndef DBSELECTOR_H
#define DBSELECTOR_H

#include <QDialog>
#include <vector>

#include "controller.h"
#include "database.h"

namespace Ui {
class DbSelector;
}

class DbSelector : public QDialog
{
    Q_OBJECT

public:
    explicit DbSelector(Controller *controller, QWidget *parent = nullptr);
    ~DbSelector();

    int getIdx();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_addDbBtn_clicked();

private:
    Ui::DbSelector *ui;
    int idx_ {-1};
    Controller *controller_;

    void fillCmb(); // Rellena el ComboBox con las bases de datos guardadas
};

#endif // DBSELECTOR_H
