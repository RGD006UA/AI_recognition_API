#include "mainwindow.h"
#include "json.hpp"

#include <chrono>
#include <string>
#include <QMessageBox>
#include <fstream>

using json = nlohmann::json;

void MainWidget::encoding()
{
    using namespace std::chrono;

    auto time = system_clock::now();

    std::string sign = "5fa0e82975533916ca87aada23c550d70f57509c13fd7a26b180629762vcjo74f2";
    std::string timestamp = /* "1697790877" */ std::to_string(duration_cast<seconds>(time.time_since_epoch()).count()).c_str();

    json js_create_encoding_left {
        {"file_1", file_dir_left},
        {"sign", sign},
        {"timestamp", timestamp},
    };

    std::ofstream file_create_encoding_right("../json_requests/create_encoding_left.json");
    file_create_encoding_right << std::setw(4) << js_create_encoding_left << std::endl;
    file_create_encoding_right.close();

    json js_create_encoding_right{
        {"file_1", file_dir_right},
        {"sign", sign},
        {"timestamp", timestamp},
    };

    std::ofstream file_create_encoding_left("../json_requests/create_encoding_right.json");
    file_create_encoding_left << std::setw(4) << js_create_encoding_right << std::endl;
    file_create_encoding_left.close();

    system("py requests_main.py");

    std::ifstream read_file("../json_requests/result.json");
    json data = json::parse(read_file);

    double similarity = data["similarity"];

    std::string result = "similarity: " + std::to_string(similarity);

    QMessageBox::information(new QWidget, "Result", result.c_str());
}