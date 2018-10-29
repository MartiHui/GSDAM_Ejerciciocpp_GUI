#include <QMessageBox>
#include <string>

#include "entrycreator.h"
#include "ui_entrycreator.h"
#include "dimensions.h"

EntryCreator::EntryCreator(DataTemplate *dt, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EntryCreator) {
    ui->setupUi(this);
    ui->fieldsArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // EL tamaño horizontal no cambiara
    dt_ = dt;

    generateFieldsForm();
}

EntryCreator::~EntryCreator() {
    delete ui;
}

void EntryCreator::generateFieldsForm() {
    delete ui->fieldsArea->takeWidget();

    QWidget *container = new QWidget;
    container->setGeometry(0, 0, 198, 178);

    Dimensions labelDim(20, 10, 150, 15, 30);
    Dimensions lineEditDim(20, 30, 150, 15, 30);
    // Indicamos cual es el tamaño que tendra para que genere las scrollbar correctamente
    container->setMinimumSize(198, labelDim.getPosY(dt_->getNumFields()));

    for (int i = 0; i < dt_->getNumFields(); i++) {
        QLabel *label = new QLabel(container);
        label->setGeometry(labelDim.posX_, labelDim.getPosY(i), labelDim.width_, labelDim.height_);
        label->setText(QString::fromStdString(dt_->getField(i).first) + ": ");
        labelList_.push_back(label);

        QLineEdit *lineEdit = new QLineEdit(container);
        lineEdit->setGeometry(lineEditDim.posX_, lineEditDim.getPosY(i), lineEditDim.width_, lineEditDim.height_);
        lineEdit->setPlaceholderText("Máximo " + QString::number(dt_->getField(i).second) + " carácteres");
        lineEdit->setMaxLength(dt_->getField(i).second);
        lineEditList_.push_back(lineEdit);
    }

    ui->fieldsArea->setWidget(container);
}

bool EntryCreator::fieldsCorrect() {
    bool allCorrect = true;

    for (int i = 0; i < lineEditList_.size(); i++) {
        if (lineEditList_[i]->text() == "") {
            allCorrect = false;
            break;
        }
    }

    return allCorrect;
}

Data EntryCreator::getEntry() {
    Data data;
    data.setTemplate(*dt_);

    for (int i = 0; i < lineEditList_.size(); i++) {
        std::string info = lineEditList_[i]->text().toStdString();
        info.resize(dt_->getField(i).second, '\0');

        data.addInformation(info);
    }

    return data;
}



void EntryCreator::accept() {
    if (!fieldsCorrect()) {
        QMessageBox msgBox;
        msgBox.setText("No has rellenado todos los campos.");
        msgBox.exec();
    } else {
        QDialog::accept();
    }
}


