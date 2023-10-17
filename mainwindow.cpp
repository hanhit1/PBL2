#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include<QMessageBox>
#include <QRadioButton>
#include <QPushButton>
#include<QDebug>
#include <QDialog>
#include <QGridLayout>
#include <QLabel>
#include<Qt>
#include <QCalendarWidget>
#include <QDate>
#include<QProgressBar>
#include<QTime>
#include<QString>
#include<QToolButton>
#include "room.h"
#include "day.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    if (ui->one->isChecked()) {
        // Xử lý khi RadioButton "one" được chọn
       QMessageBox::information(this, "Thông báo", "Đã chọn RadioButton 'one'");
    } else if (ui->all->isChecked()) {
        // Xử lý khi RadioButton "all" được chọn
    QDialog window;
    window.setWindowTitle("Thông tin máy và thời gian");

    // Tạo layout cho cửa sổ
    QVBoxLayout layout(&window);

    // Dữ liệu mẫu về tên máy và tổng thời gian từ các mảng cho trước
    QStringList machineNames = {"Máy 1", "Máy 2", "Máy 3"};
    QList<int> timeInHours = {2, 4, 3}; // Thời gian tính bằng giờ (ví dụ)

    for (int i = 0; i < machineNames.size(); ++i) {
        QLabel *label = new QLabel(machineNames[i] + ": " + QString::number(timeInHours[i]) + " giờ", &window);
        label->setFixedSize(300, 50); // Đặt kích thước cố định (300x50 pixels)
        QProgressBar *progressBar = new QProgressBar(&window);

        // Đặt giá trị tối đa cho QProgressBar là số giờ tương ứng
        progressBar->setMaximum(timeInHours[i]);

        layout.addWidget(label);
        layout.addWidget(progressBar);
    }

    // Tạo QLabel cho mỗi máy
//    for (int i = 0; i < machineNames.size(); ++i) {
//        QLabel *label = new QLabel(machineNames[i] + ": " + QString::number(timeInHours[i]) + " giờ", &window);
//        label->setFixedSize(300, 50);
//        layout.addWidget(label);
//    }

    window.setLayout(&layout);
    window.show();
    window.exec();
    } else {
        // Xử lý trường hợp không có RadioButton nào được chọn
        QMessageBox::warning(this, "Thông báo", "Hãy chọn một RadioButton trước khi nhấn nút.");
    }
}

void MainWindow::on_calendarWidget_clicked(const QDate &date)
{

}


void MainWindow::on_pushButton_2_clicked()
{
    room x;
    //int a[10] = {22, 23, 50, 34, 12, 45, 31, 27, 45, 12};
    QString b[10] = {"C103", "C204", "C206", "C207", "C224", "C112", "C105", "C107", "C201", "C202"};
    QDate date = ui->dkcalendar->selectedDate();
    int value1 = ui->bd->currentText().toInt();
    int value2 = ui->kt->currentText().toInt();
    int slhs = ui->slsv->value();
    time_t now = time(0);
    tm *t = localtime(&now);
    Date tt,z;
    z.NGAY(t->tm_mday);
    z.THANG(t->tm_mon+1);
    z.NAM(t->tm_year+1900);
    tt.NGAY(date.day());
    tt.THANG(date.month());
    tt.NAM(date.year());
    int m= diff(z,tt);
    int r = value2 - value1;

    if (r < 0) {
        QMessageBox::warning(this, "Thông báo", "Vui lòng nhập tiết phù hợp, tiết bắt đầu <= tiết kết  ");
    }
    if (x.check_t(m,value1)==false){
        QMessageBox::warning(this, "Thông báo", "Vui lòng nhập tiết phù hợp, tiết bắt đầu đã quá giờ trong hôm nay");
    }
    else {
        x.check_room(m,value1-1,value2-1,slhs);
        int a[10] = {x.Get_check(0),x.Get_check(1),x.Get_check(2),x.Get_check(3),x.Get_check(4),x.Get_check(5),x.Get_check(6),x.Get_check(7),x.Get_check(8),x.Get_check(9)};
        QDialog dialog;
        dialog.setWindowTitle("Đăng kí mượn máy ");

        QGridLayout layout(&dialog);

        QSize buttonSize(200 , 200 );

        for (int i = 0; i < 10; ++i) {
        QToolButton *button = new QToolButton;
        button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // Hiển thị icon phía trên chữ
        button->setIcon(QIcon("E:/Test/cpt.png")); // Đảm bảo đường dẫn đúng
        button->setIconSize(QSize(100, 100)); // Kích thước của biểu tượng
        button->setText(QString("Phòng máy %1\nSố máy: %2\nSố máy trống: %3").arg(b[i]).arg(x.Size(i)).arg(x.AV(i)));

        if (a[i] ==0) {
                button->setStyleSheet("background-color: rgb(85,255,0);");
                QObject::connect(button, &QPushButton::clicked, [i, &a, &dialog,&x,m,value1,value2,slhs]() {
                    int result = QMessageBox::question(nullptr, "Confirm", "Bạn có muốn Đăng kí vào phòng máy này?", QMessageBox::Yes | QMessageBox::No);
                    if (result == QMessageBox::Yes) {
                        // a[i] = 1; // Chuyển giá trị thành 1
                         x.dangky(m,value1-1,value2-1,i,slhs);
                        QMessageBox::information(nullptr, "Đăng kí thành công ", "Bạn đã đăng ký thành công");
                        dialog.accept();
                    }
                });
            }
        else
        if (a[i] ==2) {
                button->setStyleSheet("background-color: rgb(255, 255, 0);");
                QObject::connect(button, &QPushButton::clicked, [i, &a, &dialog,&x,m,value1,value2,slhs]() {
                    int result = QMessageBox::question(nullptr, "Confirm", "Bạn có muốn Đăng kí vào phòng máy này?", QMessageBox::Yes | QMessageBox::No);
                    if (result == QMessageBox::Yes) {
                        // a[i] = 1; // Chuyển giá trị thành 1
                         x.dangky(m,value1-1,value2-1,i,slhs);
                        QMessageBox::information(nullptr, "Đăng kí thành công ", "Bạn đã đăng ký thành công");
                        dialog.accept();
                    }
                });
            }else {
                button->setStyleSheet("background-color: rgb(255,72,55);");
                QObject::connect(button, &QPushButton::clicked, [i, &a]() {
                    QMessageBox::information(nullptr, "Cannot Select", "Không thể đăng ký phòng máy này");
                });
            }
            layout.addWidget(button, i / 5, i % 5);
        }

        QLabel label;
        QString info = QString("Mượn máy ngày: %1, Số lượng sinh viên: %2, Tiết bắt đầu: %3, Tiết kết thúc: %4")
                          .arg(date.toString("dd/MM/yyyy"))
                          .arg(slhs)
                          .arg(value1)
                          .arg(value2);
        label.setText(info);
        layout.addWidget(&label, 2, 0, 1, 5);
        dialog.setLayout(&layout);
        dialog.exec();
    }
}

void MainWindow::on_exit_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Exit","Bạn có muốn thoát khỏi chương trình",QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes)
    {
        QApplication::quit();
    } else
    {
        qDebug() << "No is clicked" ;
    }
}


void MainWindow::on_timmay_clicked()
{
// Mảng a với 10 phần tử gồm các giá trị 0 và 1
    int a[10] = {0, 1, 0, 1, 0, 1, 0, 1, 0, 1};
    // Tạo dialog tùy chỉnh
    QDialog dialog;
    dialog.setWindowTitle("Đăng kí mượn máy ");

    // Tạo layout grid cho dialog
    QGridLayout layout(&dialog);

    // Kích thước mỗi button
    QSize buttonSize(150 , 50);

    // Thêm 10 button vào dialog
    for (int i = 0; i < 10; ++i) {
        QPushButton *button = new QPushButton(QString("Máy %1").arg(i+1));
        // Đặt kích thước cho button
        button->setFixedSize(buttonSize);

        // Thiết lập màu của button dựa vào giá trị trong mảng a
        if (a[i] == 0) {
            button->setStyleSheet("background-color: rgb(85,255,0);");
            QObject::connect(button, &QPushButton::clicked, [i, &a, button]() {
                int result = QMessageBox::question(nullptr, "Confirm", "Bạn có muốn Đăng kí máy ?", QMessageBox::Yes | QMessageBox::No);
                if (result == QMessageBox::Yes) {
                    a[i] = 1; // Chuyển giá trị thành 1
                    button->setStyleSheet("background-color: rgb(255,72,55);"); // Đổi màu thành đỏ
                    QObject::disconnect(button, &QPushButton::clicked, nullptr, nullptr);
                    QObject::connect(button, &QPushButton::clicked, [i, &a]() {
                        QMessageBox::information(nullptr, "Cannot Select", "Máy này đã được đăng kí trước đó rồi");
                    });
                }
            });
        } else {
            button->setStyleSheet("background-color: rgb(255,72,55);");
            QObject::connect(button, &QPushButton::clicked, [i, &a]() {
                QMessageBox::information(nullptr, "Cannot Select", "Máy này đã được đăng kí trước đó rồi");
            });
        }
            layout.addWidget(button, i / 5, i % 5);
    }
    dialog.setLayout(&layout);
    dialog.exec();
}

void MainWindow::on_dkcalendar_clicked(const QDate &date)
{

    QDate selectedDate = ui->dkcalendar->selectedDate();
    QDate currentDate = QDate::currentDate();

    if (selectedDate < currentDate) {
            QMessageBox messageBox;
            messageBox.setWindowTitle("Chọn ngày: ");
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("Không thể chọn ngày nhỏ hơn ngày hôm nay.");
            messageBox.exec();
            ui->dkcalendar->setSelectedDate(currentDate);
            return;
    }
 }


void MainWindow::on_slsv_valueChanged(int arg1)
{
    if (arg1 <= 0 || arg1 > 100) {
            // Số lượng sinh viên không hợp lệ
            // Hiển thị thông báo hoặc thực hiện xử lý khác tùy thuộc vào yêu cầu của bạn
            QMessageBox messageBox;
            messageBox.setIcon(QMessageBox::Warning);
            messageBox.setText("Số lượng sinh viên không hợp lệ.");
            messageBox.exec();

            // Đặt lại giá trị mặc định hoặc thực hiện xử lý khác để sửa lỗi
           ui->slsv->setValue(1); // Đặt giá trị mặc định là 0
    }
}


void MainWindow::on_showpm_clicked()
{
    QDate Date = ui->showcalendar->selectedDate();
    QString b[10] = {"C103", "C204", "C206", "C207", "C224", "C112", "C105", "C107", "C201", "C202"};
    QDialog dialog;
    dialog.setWindowTitle(QString ("Xem thông tin máy ngày  %1 :").arg(Date.toString("dd/MM/yyyy")));

    QGridLayout layout(&dialog);

    QSize buttonSize(200 , 200 );

    for (int i = 0; i < 10; ++i) {

           QToolButton *button = new QToolButton;
           button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon); // Hiển thị icon phía trên chữ
           button->setIcon(QIcon("E:/QT C++/window test/images/Lovepik_com.png")); // Đảm bảo đường dẫn đúng
           button->setIconSize(QSize(100, 100)); // Kích thước của biểu tượng
           button->setText(QString("Phòng máy %1\n").arg(b[i]));
            layout.addWidget(button, i / 5, i % 5);
        }
        dialog.setLayout(&layout);
        dialog.exec();
}

