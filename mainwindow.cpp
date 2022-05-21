#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    load_process_into_label();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_process_into_label(){
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(processes.get_process_array().size());
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,250);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->setColumnWidth(3,50);
    ui->tableWidget->setColumnWidth(4,100);

    ui->tableWidget->verticalHeader()->setVisible(0);

    switch (sorting_type) {
    case 0:
        processes.sort_process_array();
        break;
    case 1:
        processes.sort_process_array_by_name();
        break;
    case 2:
        processes.sort_process_array_by_mem();
        break;
    case 3:
        processes.sort_procrss_array_by_thread_numb();
        break;
    default:
        break;
    }

    for(int i = 0; i < processes.get_process_array().size(); ++i){
        QString pid_str, name_str, mem_str, thread_str, username_str;

        QTableWidgetItem *pid_item = new QTableWidgetItem();
        QTableWidgetItem *name_item = new QTableWidgetItem();
        QTableWidgetItem *mem_item = new QTableWidgetItem();
        QTableWidgetItem *thread_item = new QTableWidgetItem();
        QTableWidgetItem *username_item = new QTableWidgetItem();

        pid_str = QString::fromStdString(Parse::itoa(processes.get_process_array()[i].get_pid()));
        pid_item->setText(pid_str);
        ui->tableWidget->setItem(i, 0, pid_item);

        name_str = QString::fromStdString(processes.get_process_array()[i].get_name());
        name_item->setText(name_str);
        ui->tableWidget->setItem(i, 1, name_item);

        mem_str = QString::fromStdString(Parse::itomem(processes.get_process_array()[i].get_mem()));
        mem_item->setText(mem_str);
        ui->tableWidget->setItem(i, 2, mem_item);

        thread_str = QString::fromStdString(Parse::itoa(processes.get_process_array()[i].get_threads()));
        thread_item->setText(thread_str);
        ui->tableWidget->setItem(i, 3, thread_item);

        username_str = QString::fromStdString(processes.get_process_array()[i].get_username());
        username_item->setText(username_str);
        ui->tableWidget->setItem(i, 4, username_item);
    }
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1.toStdString() == "PID"){
        sorting_type = 0;
        load_process_into_label();
    }
    if(arg1.toStdString() == "Name"){
        sorting_type = 1;
        load_process_into_label();
    }
    if(arg1.toStdString() == "Memory"){
        sorting_type = 2;
        load_process_into_label();
    }
    if(arg1.toStdString() == "Thread"){
        sorting_type = 3;
        load_process_into_label();
    }
}

void MainWindow::on_pushButton_clicked()
{
    processes.get_process_array().clear();
    processes.get_process_array();
    load_process_into_label();
}


void MainWindow::on_pushButton_2_clicked()
{
    std::string name = ui->lineEdit->text().toStdString();
    std::vector<ProcessInfo> find_vector = processes.find_process_array_by_processname(name);
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setRowCount(find_vector.size());


    for(int i = 0; i < find_vector.size(); ++i){
        QString pid_str, name_str, mem_str, thread_str, username_str;

        QTableWidgetItem *pid_item = new QTableWidgetItem();
        QTableWidgetItem *name_item = new QTableWidgetItem();
        QTableWidgetItem *mem_item = new QTableWidgetItem();
        QTableWidgetItem *thread_item = new QTableWidgetItem();
        QTableWidgetItem *username_item = new QTableWidgetItem();

        pid_str = QString::fromStdString(Parse::itoa(find_vector[i].get_pid()));
        pid_item->setText(pid_str);
        ui->tableWidget->setItem(i, 0, pid_item);

        name_str = QString::fromStdString(find_vector[i].get_name());
        name_item->setText(name_str);
        ui->tableWidget->setItem(i, 1, name_item);

        mem_str = QString::fromStdString(Parse::itomem(find_vector[i].get_mem()));
        mem_item->setText(mem_str);
        ui->tableWidget->setItem(i, 2, mem_item);

        thread_str = QString::fromStdString(Parse::itoa(find_vector[i].get_threads()));
        thread_item->setText(thread_str);
        ui->tableWidget->setItem(i, 3, thread_item);

        username_str = QString::fromStdString(find_vector[i].get_username());
        username_item->setText(username_str);
        ui->tableWidget->setItem(i, 4, username_item);
    }
}

