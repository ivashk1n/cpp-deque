#pragma once

#include <QMainWindow>
#include <QStringListModel>
#include <QListWidgetItem>

#include "model.h"
#include <random>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void ApplyModel();

    void ApplyIterator();

    void on_list_widget_currentRowChanged(int currentRow);

    void on_B_pop_back_clicked();

    void on_B_push_back_clicked();

    void on_B_clear_clicked();

    void on_B_tea_clicked();

    void on_B_erase_clicked();

    void on_B_insert_clicked();

    void on_B_minus_clicked();

    void on_B_plus_clicked();

    void on_B_begin_clicked();

    void on_B_end_clicked();

    void on_B_edit_clicked();

    void on_B_resize_clicked();

    void on_B_find_clicked();

    void on_B_count_clicked();

    void on_B_min_element_clicked();

    void on_B_max_element_clicked();

    void on_B_sort_clicked();

    void on_B_sOrT_clicked();

    void on_B_unique_clicked();

    void on_B_reverse_clicked();

    void on_B_shuffle_clicked();

    void on_B_pop_front_clicked();

    void on_B_push_front_clicked();

    void on_B_lower_bound_clicked();

    void on_B_upper_bound_clicked();

    void on_B_cake_clicked();

public:
    void SetRandomGen(const std::mt19937& random_gen) {
        random_gen_ = random_gen;
    }

private:
    Model deque_model_;
    Ui::MainWindow *ui;
    std::mt19937 random_gen_;
};
