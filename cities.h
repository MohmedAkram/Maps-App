#ifndef CITIES_H
#define CITIES_H

#include <QDialog>

namespace Ui {
class Cities;
}

class Cities : public QDialog
{
    Q_OBJECT

public:
    explicit Cities(QWidget *parent = nullptr);
    ~Cities();

    void loadList();
    void saveList();

private slots:
    void on_back_clicked();

    void on_addcity_clicked();

    void on_deletecity_clicked();

    void on_delete1_clicked();

    void on_add_clicked();

    void on_cancel_clicked();

private:
    Ui::Cities *ui;
};

#endif // CITIES_H
