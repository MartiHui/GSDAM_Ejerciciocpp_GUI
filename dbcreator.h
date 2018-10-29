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

protected:
    void accept() override;

private slots:
    void on_numFields_valueChanged(int arg1);

private:
    Ui::DbCreator *ui;
    QVector<QLabel*> labelList_;
    QVector<QLineEdit*> lineEditList_;
    QVector<QSpinBox*> spinBoxList_;
    std::vector<Database> *databases_;

    void generateFieldsForm(int numFields);
    void cleanScrollArea(); // Borramos los Widgets generados en el QScrollArea
    bool fieldsCorrect(); // Comprobamos si se han rellenado todos los campos correctamente
};

#endif // DBCREATOR_H
