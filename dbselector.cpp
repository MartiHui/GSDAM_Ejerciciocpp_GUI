#include <vector>
#include <QDebug>

#include "dbselector.h"
#include "ui_dbselector.h"
#include "database.h"
#include "m_utilities.h"
#include "dbcreator.h"

DbSelector::DbSelector(Controller *controller, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbSelector)
{
    ui->setupUi(this);
    controller_ = controller;

    fillCmb();
}

DbSelector::~DbSelector()
{
    delete ui;
}

void DbSelector::fillCmb() {
    ui->dbListCmb->clear();

    for (unsigned int i = 0; i < controller_->databases_.size(); i++) {
        QString name = QString::fromStdString(controller_->databases_[i].getDatabaseName());
        ui->dbListCmb->addItem(name);
    }
}

void DbSelector::on_buttonBox_rejected()
{
    close();
}

void DbSelector::on_buttonBox_accepted()
{
    idx_ = ui->dbListCmb->currentIndex();
    close();
}

int DbSelector::getIdx() {
    return idx_;
}

void DbSelector::on_addDbBtn_clicked()
{
    DbCreator *dbCreator = new DbCreator(&controller_->databases_);
    dbCreator->show();
    if (dbCreator->exec()) {
        Database db = dbCreator->getDatabase();
        controller_->saveDatabase(db);
    }
    delete dbCreator;

    fillCmb();
}
