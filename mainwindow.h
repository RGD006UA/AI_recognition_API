#include <QtWidgets>
#include <QPushButton>
#include <QLabel>
#include <QPixmap>
#include <QFile>


class MainWidget : public QWidget
{
private:
    QPushButton* button_left = new QPushButton("&Upload image", this);
    QPushButton* button_right = new QPushButton("&Upload image", this);
    QPushButton* button_recognition = new QPushButton("&Recognize", this);    
    QLabel* left_label = new QLabel();
    QLabel* right_label = new QLabel();
    QPixmap pix_image_left;
    QPixmap pix_image_right;
    QUrl url_create_encoding = QUrl("https://api.passport.evergreens.com.ua/dbapi/create_encoding/");
    std::string  file_dir_left, file_dir_right, format_left, format_right;

    void change_image(QPixmap &pixmap, QLabel *label, std::string &file_dir, std::string &format);
    void set_pixmap_default_size(QPixmap &pixmap);
    void make_recognize();
    void encoding();
public:
    MainWidget();
    ~MainWidget();
};