#ifndef ENTRYCREATOR_H
#define ENTRYCREATOR_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QVector>

#include "datatemplate.h"
#include "data.h"

namespace Ui {
class EntryCreator;
}

class EntryCreator : public QDialog
{
    Q_OBJECT

public:
    explicit EntryCreator(DataTemplate *dt, QWidget *parent = nullptr);
    ~EntryCreator();

    Data getEntry();

protected:
    void accept() override;

private:
    Ui::EntryCreator *ui;
    QVector<QLabel*> labelList_;
    QVector<QLineEdit*> lineEditList_;
    DataTemplate *dt_;

    void generateFieldsForm();
    bool fieldsCorrect();
};

#endif // ENTRYCREATOR_H
