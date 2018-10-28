#include <QDebug>
#include <QVector>
#include <QMessageBox>

#include "gui.h"
#include "ui_gui.h"
#include "m_utilities.h"
#include "dbselector.h"
#include "data.h"
#include "entrycreator.h"
#include "searchentry.h"

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

    if (dbs->exec()) {
        int idx = dbs->getIdx();
        if (idx >= 0) {
            controller_->currentDatabase_ = &controller_->databases_[idx];
            controller_->currentDatabase_->loadFileEntries();
        }
        displayDbData();
    }

    delete dbs;
}

void GUI::displayDbData() {
    ui->databaseNameLbl->setText(QString::fromStdString(controller_->currentDatabase_->getDatabaseName()));
    displayAllEntries();
}

void GUI::displayEntries(QVector<Data> &entries) {
    ui->entryList->clear();

    DataTemplate dt = controller_->currentDatabase_->getTemplate();

    for (int i = 0; i < entries.size(); i++) {
        ui->entryList->append(QString::number(i+1) + ":");
        for (int j = 0; j < dt.getNumFields(); j++) {
            ui->entryList->append(QString::fromStdString("    " + dt.getField(j).first + ": "
                                                         + entries[i].getInformation(j)));
        }
        ui->entryList->append("");
    }
}

void GUI::displayAllEntries() {
    QVector<Data> entries = QVector<Data>::fromStdVector(controller_->currentDatabase_->getEntries());
    displayEntries(entries);
}

void GUI::on_newEntryBtn_clicked()
{
    if (controller_->currentDatabase_) {
        DataTemplate dt = controller_->currentDatabase_->getTemplate();
        EntryCreator *ec = new EntryCreator(&dt);

        if (ec->exec()) {
            Data entry = ec->getEntry();
            controller_->currentDatabase_->addEntry(entry);
            displayAllEntries();
        }

        delete ec;
    } else {
        noDatabaseAlert();
    }
}

void GUI::on_showEntriesBtn_clicked()
{
    if (controller_->currentDatabase_) {
        displayAllEntries();
    } else {
        noDatabaseAlert();
    }
}

void GUI::on_searchEntryBtn_clicked()
{
    if (controller_->currentDatabase_) {
        SearchEntry *se = new SearchEntry(controller_->currentDatabase_);

        if (se->exec()) {
            QVector<Data> entries = QVector<Data>::fromStdVector(se->searchEntries());
            displayEntries(entries);
        } else {
            displayAllEntries();
        }

        delete se;
    } else {
        noDatabaseAlert();
    }
}

void GUI::noDatabaseAlert() {
    QMessageBox msgBox;
    msgBox.setText("No hay ninguna base de datos seleccionada.");
    msgBox.exec();
}
