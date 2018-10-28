#ifndef DBCREATOR_H
#define DBCREATOR_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QVector>
#include <vector>

#include "database.h"

namespace Ui {
class DbCreator;
}

class DbCreator : public QDialog
{
    Q_OBJECT

public:
    explicit DbCreator(std::vector<Database> *databases, QWidget *parent = nullptr);
    ~DbCreator();

    Database getDatabase();

private slots:
    void on_numFields_valueChanged(int arg1);

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DbCreator *ui;
    QVector<QLabel*> labelList_;
    QVector<QLineEdit*> lineEditList_;
    QVector<QSpinBox*> spinBoxList_;
    std::vector<Database> *databases_;

    void generateFieldsForm(int numFields);
    void cleanScrollArea();
    bool fieldsCorrect();
};

#endif // DBCREATOR_H
