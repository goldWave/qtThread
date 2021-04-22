#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "jrunnable.h"
#include <vector>

using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    JRunnable *m_jrun = nullptr;

  public slots:
    void thOver();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    vector<void *>m_vec;
};
#endif // MAINWINDOW_H
