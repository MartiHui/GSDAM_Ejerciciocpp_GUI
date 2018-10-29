#ifndef GUI_H
#define GUI_H

#include <QMainWindow>
#include <QVector>

#include "controller.h"
#include "datatemplate.h"
#include "data.h"

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

    void on_newEntryBtn_clicked();

    void on_showEntriesBtn_clicked();

    void on_searchEntryBtn_clicked();

private:
    Ui::GUI *ui;

    void displayDbData();
    void displayEntries(QVector<Data> &entries);
    void displayAllEntries();
    void noDatabaseAlert(); // Avisamos en caso de que se intente realizar alguna accion sobre la base de datos
                            // cuando aun no ha seleccionado alguna base de datos
};

#endif // GUI_H
