#include <vector>

#include "searchentry.h"
#include "ui_searchentry.h"

SearchEntry::SearchEntry(Database *ds, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SearchEntry)
{
    ui->setupUi(this);
    ds_ = ds;

    for (int i = 0; i < ds->getTemplate().getNumFields(); i++) {
        ui->fieldsCmb->addItem(QString::fromStdString(ds->getTemplate().getField(i).first));
    }
}

SearchEntry::~SearchEntry()
{
    delete ui;
}

void SearchEntry::setMaxLengthLineEdit(int i) {
    int max = ds_->getTemplate().getField(i).second;
    ui->searchLine->setMaxLength(max);
}

std::vector<Data> SearchEntry::searchEntries() {
    int idx = ui->fieldsCmb->currentIndex();
    std::string word = ui->searchLine->text().toStdString();
    return ds_->searchEntries(idx, word);
}

void SearchEntry::on_fieldsCmb_currentIndexChanged(int index)
{
    setMaxLengthLineEdit(index);
}

void SearchEntry::accept() {
    if (ui->searchLine->text() == "") {
        QDialog::reject();
    } else {
        QDialog::accept();
    }
}
