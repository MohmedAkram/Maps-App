#ifndef WELCOMEPAGE_H
#define WELCOMEPAGE_H

#include <QDialog>

namespace Ui {
class welcomePage;
}

class welcomePage : public QDialog
{
    Q_OBJECT

public:
    explicit welcomePage(QWidget *parent = nullptr);
    // void setName(QString name);
    ~welcomePage();

private slots:
    void on_cities_clicked();

    void on_paths_clicked();

    void on_navigate_clicked();

    void on_quit_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::welcomePage *ui;
};

#endif // WELCOMEPAGE_H
