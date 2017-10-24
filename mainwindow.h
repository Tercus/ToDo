#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_pushButton_connect_clicked();

    void on_pushButton_parse_clicked();

    void on_pushButton_table_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
