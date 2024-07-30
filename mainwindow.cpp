#include "mainwindow.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <algorithm>

MainWidget::MainWidget()
{
    resize(QSize(1000, 600));
    setWindowTitle("AI recognition faces");

    auto* main_v_box = new QVBoxLayout(this);
    auto* image_h_box = new QHBoxLayout(this);
    auto* image_left_v_box = new QVBoxLayout(this);
    auto* image_right_v_box = new QVBoxLayout(this);

    pix_image_left.load("../image/logo.png");
    set_pixmap_default_size(pix_image_left);
    pix_image_right.load("../image/logo.png");
    set_pixmap_default_size(pix_image_right);

    left_label->setPixmap(pix_image_left);
    left_label->setAlignment(Qt::AlignCenter);
    right_label->setPixmap(pix_image_right);
    right_label->setAlignment(Qt::AlignCenter);

    image_left_v_box->addWidget(left_label);
    image_left_v_box->addWidget(button_left);
    image_left_v_box->setSpacing(3);

    image_right_v_box->addWidget(right_label, Qt::AlignCenter);
    image_right_v_box->addWidget(button_right, Qt::AlignCenter);
    image_right_v_box->setSpacing(3);

    image_h_box->addLayout(image_left_v_box);
    image_h_box->addLayout(image_right_v_box);
    
    main_v_box->addLayout(image_h_box);
    main_v_box->addWidget(button_recognition);

    main_v_box->setSpacing(3);

    connect(button_left, &QPushButton::clicked, this, [this] { change_image(
                                                                                        pix_image_left, 
                                                                                        left_label, 
                                                                                        file_dir_left, 
                                                                                        format_left); });
    connect(button_right, &QPushButton::clicked, this, [this] { change_image(
                                                                                        pix_image_right, 
                                                                                        right_label,  
                                                                                        file_dir_right, 
                                                                                        format_right); });
    connect(button_recognition, &QPushButton::clicked, this, make_recognize);

    setLayout(main_v_box);
}

void MainWidget::change_image(
                                    QPixmap &pixmap, 
                                    QLabel* label, 
                                    std::string &file_dir, 
                                    std::string &format)
{
    QString image_name = QFileDialog::getOpenFileName(this, "Open a image", QDir::homePath());
    pixmap.load(image_name);
    file_dir = image_name.toStdString(); 
    std::size_t found_format = image_name.toStdString().find_last_of(".");
    format = image_name.toStdString().substr(found_format + 1);
    set_pixmap_default_size(pixmap);
    label->setPixmap(pixmap);
    // QMessageBox::information(this, "..", QString(image_name + "\nPath: " + file_dir.c_str() + "\nFormat: " + format.c_str()));
}

void MainWidget::set_pixmap_default_size(QPixmap &pixmap)
{
    pixmap = pixmap.scaled(QSize(500, 500), Qt::IgnoreAspectRatio);
}

void MainWidget::make_recognize()
{
    encoding();
}

MainWidget::~MainWidget()
{
    delete button_left;
    delete button_right;
    delete button_recognition;
    delete left_label;
    delete right_label;
}