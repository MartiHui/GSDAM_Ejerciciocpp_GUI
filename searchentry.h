#ifndef SEARCHENTRY_H
#define SEARCHENTRY_H

#include <QDialog>
#include <vector>

#include "datatemplate.h"
#include "database.h"
#include "data.h"

namespace Ui {
class SearchEntry;
}

class SearchEntry : public QDialog
{
    Q_OBJECT

public:
    explicit SearchEntry(Database *ds, QWidget *parent = nullptr);
    ~SearchEntry();

    std::vector<Data> searchEntries();
    void setMaxLengthLineEdit(int i);

protected:
    void accept() override;

private slots:
    void on_fieldsCmb_currentIndexChanged(int index);

private:
    Ui::SearchEntry *ui;
    Database *ds_;
};

#endif // SEARCHENTRY_H
