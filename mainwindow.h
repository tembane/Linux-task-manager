#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QProgressBar>
#include <QLayoutItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGridLayout>
#include <QTableWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QPixmap>
#include <QIcon>

#include "parse.h"
#include "processes.h"
#include "processinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void load_process_into_label();

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
private:
    std::vector<QLabel*> pids_label_vec;
    std::vector<QLabel*> threads_label_vec;
    std::vector<QLabel*> memory_label_vec;
    std::vector<QLabel*> username_label_vec;
    std::vector<QLabel*> processname_label_vec;
    int search_type = 0;
    int sorting_type = 0;
    QGridLayout *g = new QGridLayout();
    std::vector<QHBoxLayout*> h;
    Processes processes;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
