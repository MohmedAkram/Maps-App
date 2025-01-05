#ifndef NAVIGATE_H
#define NAVIGATE_H

#include <QDialog>

namespace Ui {
class Navigate;
}

class Navigate : public QDialog
{
    Q_OBJECT

public:
    explicit Navigate(QWidget *parent = nullptr);
    ~Navigate();

private slots:
    void on_back_clicked();

    void on_go_clicked();

private:
    QString location, destination;
    Ui::Navigate *ui;
};

#endif // NAVIGATE_H
