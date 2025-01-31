#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QListWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ApplyModel();
}

static std::deque<std::string> tea {
    "Чай Лунцзин",
    "Эрл Грей",
    "Сенча",
    "Пуэр",
    "Дарджилинг",
    "Ассам",
    "Матча",
    "Ганпаудер",
    "Оолонг",
    "Лапсанг Сушонг"
};

static std::deque<std::string> cakes {
    "Красный бархат",
    "Наполеон",
    "Медовик",
    "Тирамису",
    "Прага",
    "Чизкейк",
    "Захер",
    "Эстерхази",
    "Морковный торт",
    "Чёрный лес",
};

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() { // добавление элемента в QListWidget

    QString size = QString::number(deque_model_.items.size());
    ui->txt_size->setText(size);
    ui->list_widget->clear();

    for(int i = 0; i < deque_model_.items.size(); ++i) {

        ui->list_widget->addItem(QString::number(i) + ": " + QString::fromStdString(deque_model_.items[i]));
    }

    ui->list_widget->addItem("end");

    ApplyIterator();
}

void MainWindow::ApplyIterator() {  // размещение итератора и активность кнопок

    int dist = std::distance(deque_model_.items.begin(), deque_model_.iterator); // смещение итератора

    ui->list_widget->setCurrentRow(dist); // установить выделенную строку

    if (deque_model_.iterator == deque_model_.items.end()) {

        ui->B_edit->setDisabled(true); // выкл кнопку
        ui->B_erase->setDisabled(true);
        ui->B_plus->setDisabled(true);

        ui->txt_elem_content->setText("");
    }
    else if (deque_model_.iterator != deque_model_.items.end()){

        ui->B_edit->setDisabled(false); // вкл кнопку
        ui->B_erase->setDisabled(false);
        ui->B_plus->setDisabled(false);

        ui->txt_elem_content->setText(QString::fromStdString(*deque_model_.iterator)); // раизменованый итератор в строку и его вывод

    }

    if (deque_model_.items.empty()){

        ui->B_pop_back->setDisabled(true);
        ui->B_pop_front->setDisabled(true);
    }
    else if (deque_model_.items.size() > 0){

        ui->B_pop_back->setDisabled(false);
        ui->B_pop_front->setDisabled(false);
    }

    if (deque_model_.iterator == deque_model_.items.begin()) {

        ui->B_minus->setDisabled(true);
    }
    else  {
        ui->B_minus->setDisabled(false);
    }

}

void MainWindow::on_list_widget_currentRowChanged(int currentRow)
{
    if (currentRow >= 0) { //итератор выбран

        deque_model_.iterator = deque_model_.items.begin() + currentRow; // установка итератора на выделуную строку
        ApplyIterator();
    }

}

void MainWindow::on_B_pop_back_clicked()
{
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_push_back_clicked()
{
    QString elem = ui->txt_elem_content->text();
    deque_model_.items.push_back(elem.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}


void MainWindow::on_B_clear_clicked()
{
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_tea_clicked()
{
    deque_model_.items = tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_B_cake_clicked()
{
    deque_model_.items = cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_erase_clicked()
{
    deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}


void MainWindow::on_B_insert_clicked()
{
    deque_model_.items.insert(deque_model_.iterator, ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();

}


void MainWindow::on_B_minus_clicked()
{
    --deque_model_.iterator;
    ApplyModel();

}


void MainWindow::on_B_plus_clicked()
{
    ++deque_model_.iterator;
    ApplyModel();
}


void MainWindow::on_B_begin_clicked()
{
    deque_model_.iterator = deque_model_.items.begin();
    on_list_widget_currentRowChanged(0);
    ApplyIterator();
}


void MainWindow::on_B_end_clicked()
{
    deque_model_.iterator = deque_model_.items.end();
    on_list_widget_currentRowChanged(deque_model_.items.size());
    ApplyIterator();
}


void MainWindow::on_B_edit_clicked()
{
    std::string on_edit = ui->txt_elem_content->text().toStdString();
    auto index = std::distance(deque_model_.items.begin(), deque_model_.iterator);
    deque_model_.items[index] = on_edit;
    ApplyModel();
}


void MainWindow::on_B_resize_clicked()
{
    deque_model_.items.resize(ui->txt_size->text().toInt());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_find_clicked()
{
    auto find_in_list = [&](const std::string& item) {
        QString txt_el = ui->txt_elem_content->text();
        return item == txt_el.toStdString();
    };
    auto res_find = std::find_if(deque_model_.items.begin(), deque_model_.items.end() , find_in_list);

    if (res_find != deque_model_.items.end()) {
        deque_model_.iterator = res_find;
    }
    else {
        deque_model_.iterator = deque_model_.items.end();
    }

    ApplyModel();

}


void MainWindow::on_B_count_clicked()
{
    auto comp = [&](const std::string& item) {
        QString le_c = ui->le_count->text();
        return item == le_c.toStdString();
    };

    int count_post = std::count_if(deque_model_.items.begin(), deque_model_.items.end() , comp);

    QString counts = QString::number(count_post);
    ui->lbl_count->setText(counts);

    ApplyIterator();
}


void MainWindow::on_B_min_element_clicked()
{
    if (deque_model_.items.empty()) {
        deque_model_.iterator = deque_model_.items.end();
    }

    auto comp = [&](const std::string& a, const std::string& b) {
        return a < b;};

    auto min_elem = std::min_element(deque_model_.items.begin(), deque_model_.items.end(), comp);

    if (min_elem != deque_model_.items.end()) {
        deque_model_.iterator = min_elem;
        ui->txt_elem_content->setText(QString::fromStdString(*min_elem));
    }
    else {
        deque_model_.iterator = deque_model_.items.end();
    }

    ApplyIterator();

}


void MainWindow::on_B_max_element_clicked()
{
    if (deque_model_.items.empty()) {
        deque_model_.iterator = deque_model_.items.end();
    }

    auto comp = [&](const std::string& a, const std::string& b) {
        return a < b;};

    auto max_elem = std::max_element(deque_model_.items.begin(), deque_model_.items.end(), comp);

    if (max_elem != deque_model_.items.end()) {
        deque_model_.iterator = max_elem;
        ui->txt_elem_content->setText(QString::fromStdString(*max_elem));
    }
    else {
        deque_model_.iterator = deque_model_.items.end();
    }

    ApplyIterator();
}


void MainWindow::on_B_sort_clicked()
{
    auto comp = [](const std::string& a, const std::string& b) {
        return a < b;
    };

    deque_model_.items = MergeSort(deque_model_.items, comp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_sOrT_clicked()
{
    auto comp = [](const std::string& s1, const std::string& s2) {
        auto qs1 = QString::fromStdString(s1);
        auto qs2 = QString::fromStdString(s2);

        return QString::compare(qs1, qs2, Qt::CaseInsensitive) < 0;
    };

    deque_model_.items = MergeSort(deque_model_.items, comp);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_unique_clicked()
{
    if (std::is_sorted(deque_model_.items.begin(),deque_model_.items.end())) {

        auto del_rep = std::unique(deque_model_.items.begin(), deque_model_.items.end());
        deque_model_.items.erase(del_rep, deque_model_.items.end());
        deque_model_.iterator = deque_model_.items.begin();
        ApplyModel();
    }
}


void MainWindow::on_B_reverse_clicked()
{
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}


void MainWindow::on_B_shuffle_clicked()
{
    std::shuffle(deque_model_.items.begin(), deque_model_.items.end(), random_gen_);
    ApplyModel();
}

void MainWindow::on_B_pop_front_clicked()
{
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_push_front_clicked()
{
    QString elem = ui->txt_elem_content->text();
    deque_model_.items.push_front(elem.toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}


void MainWindow::on_B_lower_bound_clicked()
{
    if(std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {

        std::string serch_word = ui->txt_elem_content->text().toStdString();
        auto low = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), serch_word);

        if(low != deque_model_.items.end()){
            deque_model_.iterator = low;
            ApplyModel();
        }
    }
}


void MainWindow::on_B_upper_bound_clicked()
{
    if(std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {

        std::string serch_word = ui->txt_elem_content->text().toStdString();
        auto upper = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), serch_word);

        deque_model_.iterator = upper;
        ApplyModel();

    }
}







