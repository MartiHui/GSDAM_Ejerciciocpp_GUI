#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QDebug>
#include <QMessageBox>
#include <QCloseEvent>

#include "dbcreator.h"
#include "ui_dbcreator.h"
#include "dimensions.h"
#include "m_utilities.h"
#include "database.h"
#include "datatemplate.h"

DbCreator::DbCreator(std::vector<Database> *databases, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbCreator)
{
    databases_ = databases;

    ui->setupUi(this);
    generateFieldsForm(1);
}

DbCreator::~DbCreator()
{
    delete ui;
}

void DbCreator::on_numFields_valueChanged(int arg1)
{
    generateFieldsForm(arg1);
}

void DbCreator::generateFieldsForm(int numFields) {
    cleanScrollArea();

    QWidget *container = new QWidget();
    container->setGeometry(0, 0, 298, 273);
    QLabel *label1 = new QLabel(container);
    label1->setGeometry(80, 10, 100, 15);
    label1->setText("Nombre");
    QLabel *label2 = new QLabel(container);
    label2->setGeometry(200, 10, 100, 15);
    label2->setText("Longitud");

    Dimensions labelDim(20, 30, 50, 15, 10);
    Dimensions lineEditDim(80, 30, 100, 15, 10);
    Dimensions spinBoxDim(200, 30, 40, 15, 10);

    for (int i = 0; i < numFields; i++) {
        QLabel *label = new QLabel(container);
        label->setGeometry(labelDim.posX_, labelDim.getPosY(i), labelDim.width_, labelDim.height_);
        label->setText("Campo " + QString::number(i+1));
        labelList_.push_back(label);

        QLineEdit *lineEdit = new QLineEdit(container);
        lineEdit->setGeometry(lineEditDim.posX_, lineEditDim.getPosY(i), lineEditDim.width_, lineEditDim.height_);
        lineEditList_.push_back(lineEdit);

        QSpinBox *spinBox = new QSpinBox(container);
        spinBox->setGeometry(spinBoxDim.posX_, spinBoxDim.getPosY(i), spinBoxDim.width_, spinBoxDim.height_);
        spinBox->setMinimum(1);
        spinBox->setMaximum(50);
        spinBoxList_.push_back(spinBox);
    }

    ui->fieldsForm->setWidget(container);
}

void DbCreator::cleanScrollArea() {
    labelList_.clear();
    lineEditList_.clear();
    spinBoxList_.clear();
    delete ui->fieldsForm->takeWidget();
}

Database DbCreator::getDatabase() {
    Database db;
    DataTemplate dt;

    db.setDatabaseName(ui->dbName->text().toStdString());

    int num = ui->numFields->value();
    dt.setNumFields(num);
    for (int i = 0; i < num; i++) {
        dt.addField(lineEditList_[i]->text().toStdString(), spinBoxList_[i]->value());
    }
    db.setTemplate(dt);

    return db;
}

bool DbCreator::fieldsCorrect() {
    bool allCorrect = true;
    for (int i = 0; i < ui->numFields->value(); i++) {
        if (lineEditList_[i]->text() == "") {
            allCorrect = false;
            break;
        }
    }

    return allCorrect;
}

void DbCreator::accept() {
    if(!isNewName(*databases_, ui->dbName->text().toStdString())) {
        QMessageBox msgBox;
        msgBox.setText("Ya existe una base de datos con este nombre.");
        msgBox.exec();
    } else if (ui->dbName->text() == "") {
        QMessageBox msgBox;
        msgBox.setText("Intorduce el nombre de la base de datos.");
        msgBox.exec();
    } else if (!fieldsCorrect()) {
        QMessageBox msgBox;
        msgBox.setText("Todos los campos necesitan un nombre.");
        msgBox.exec();
    } else {
        QDialog::accept();
    }
}
