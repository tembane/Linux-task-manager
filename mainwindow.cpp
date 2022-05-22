#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include<QTimer>

void update_table(std::vector<ProcessInfo> vec, Ui::MainWindow *ui){
    ui->lineEdit->clear();
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setRowCount(vec.size());
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,250);
    ui->tableWidget->setColumnWidth(2, 10);
    ui->tableWidget->setColumnWidth(3,150);
    ui->tableWidget->setColumnWidth(4,50);
    ui->tableWidget->setColumnWidth(5,100);
    ui->tableWidget->verticalHeader()->setVisible(0);
    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "PID" << "Name" << "Status" << "Memory" << "Thread" << "Username");
    for(int i = 0; i < vec.size(); ++i){
        QString pid_str, name_str, mem_str, thread_str, username_str, status;

        QTableWidgetItem *pid_item = new QTableWidgetItem();
        QTableWidgetItem *name_item = new QTableWidgetItem();
        QTableWidgetItem *mem_item = new QTableWidgetItem();
        QTableWidgetItem *thread_item = new QTableWidgetItem();
        QTableWidgetItem *username_item = new QTableWidgetItem();
        QTableWidgetItem *process_status_item = new QTableWidgetItem();

        pid_str = QString::fromStdString(Parse::itoa(vec[i].get_pid()));
        pid_item->setText(pid_str);
        ui->tableWidget->setItem(i, 0, pid_item);

        name_str = QString::fromStdString(vec[i].get_name());
        name_item->setText(name_str);
        ui->tableWidget->setItem(i, 1, name_item);

        status = vec[i].get_status();
        process_status_item->setText(status);
        ui->tableWidget->setItem(i, 2, process_status_item);

        mem_str = QString::fromStdString(Parse::itomem(vec[i].get_mem()));
        mem_item->setText(mem_str);
        ui->tableWidget->setItem(i, 3, mem_item);

        thread_str = QString::fromStdString(Parse::itoa(vec[i].get_threads()));
        thread_item->setText(thread_str);
        ui->tableWidget->setItem(i, 4, thread_item);

        username_str = QString::fromStdString(vec[i].get_username());
        username_item->setText(username_str);
        ui->tableWidget->setItem(i, 5, username_item);
    }
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    load_process_into_label();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_process_into_label(){

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
    update_table(processes.get_process_array(), ui);
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
    switch(search_type){
        case 0:{
            QMessageBox messageBox;
            QString error_message;
            int pid = ui->lineEdit->text().toInt();
            if(pid == 0){
                messageBox.critical(0, "Error", "Enter internger value");
                messageBox.setFixedSize(1000, 300);
                ui->lineEdit->clear();
                return;
            }
            error_message += "There is no process with this \"" + QString::number(pid) + "\" pid";
            ProcessInfo obj;
            obj = processes.find_process_array_by_pid(pid);
            if(obj.empty()){
                messageBox.critical(0, "Error", error_message);
                messageBox.setFixedSize(1000, 300);
                ui->lineEdit->clear();
                return;
            } else {
                std::vector<ProcessInfo> tmp;
                tmp.push_back(obj);
                update_table(tmp, ui);
            }
            break;
        }
        case 1:{
            QMessageBox messageBox;
            QString error_message;
            std::string name = ui->lineEdit->text().toStdString();
            if(name.empty()){
                messageBox.critical(0, "Error", "String is empty");
                messageBox.setFixedSize(500, 200);
                ui->lineEdit->clear();
                return;
            }
            error_message += "There is no " + QString::fromStdString(name) + " process";
            std::vector<ProcessInfo> find_vector = processes.find_process_array_by_processname(name);
            if(find_vector.empty()){
                messageBox.critical(0, "Error", error_message);
                messageBox.setFixedSize(500, 200);
                ui->lineEdit->clear();
                return;
            }
            update_table(find_vector, ui);
            break;
        }
    }

    ui->lineEdit->clear();
}


void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox messageBox;
    QString error_message;
    int pid = ui->lineEdit->text().toInt();
    if(pid == 0){
        messageBox.critical(0, "Error", "Enter internger value");
        messageBox.setFixedSize(1000, 300);
        ui->lineEdit->clear();
        return;
    }
    error_message += "There is no process with this \"" + QString::fromStdString(Parse::itoa(pid)) + "\" pid";
    ProcessInfo obj;
    obj = processes.find_process_array_by_pid(pid);
    if(obj.empty()){
        messageBox.critical(0, "Error", error_message);
        messageBox.setFixedSize(1000, 300);
        ui->lineEdit->clear();
        return;
    } else {
        processes.delProcesses(pid);
    }
    update_table(processes.get_process_array(), ui);
    ui->lineEdit->clear();
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    if(arg1.toStdString() == "PID"){
        search_type = 0;
    }
    if(arg1.toStdString() == "Name"){
        search_type = 1;
    }
}

