#include <QDebug>

#include "gui.h"
#include "ui_gui.h"
#include "m_utilities.h"
#include "dbselector.h"

GUI::GUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GUI)
{
    ui->setupUi(this);
    controller_ = new Controller;
}

GUI::~GUI()
{
    delete ui;
    delete controller_;
}

void GUI::on_selectDatabaseBtn_clicked()
{
    DbSelector *dbs = new DbSelector(controller_);
    dbs->show();

    if (dbs->exec()) {
        int idx = dbs->getIdx();
        if (idx >= 0) {
            controller_->currentDatabase_ = &controller_->databases_[idx];
        }
    }

    delete dbs;
    displayDbData();
}

void GUI::displayDbData() {
    ui->databaseNameLbl->setText(QString::fromStdString(controller_->currentDatabase_->getDatabaseName()));
}
