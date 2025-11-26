#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QDateEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QLabel>
#include <QTabWidget>
#include "BudgetManager.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addTransaction();
    void deleteTransaction();
    void loadEditTransaction();
    void saveEditTransaction();
    void refreshTransactionTable();
    void refreshSummary();

private:
    BudgetManager manager;
    QString dataFile;

    // Tab widget
    QTabWidget *tabWidget;

    // Add Transaction Tab widgets
    QDateEdit *dateEdit;
    QComboBox *categoryCombo;
    QLineEdit *amountEdit;
    QLineEdit *descriptionEdit;
    QPushButton *addButton;

    // Edit / Delete Transaction Tab widgets
    QTableWidget *editTable;
    QDateEdit    *editDateEdit;
    QComboBox    *editCategoryCombo;
    QLineEdit    *editAmountEdit;
    QLineEdit    *editDescriptionEdit;
    QPushButton  *editSaveButton;
    QPushButton  *editDeleteButton;

    // View Transactions Tab widgets
    QTableWidget *transactionTable;

    // Dashboard Tab widgets
    QLabel *incomeLabel;
    QLabel *expenseLabel;
    QLabel *balanceLabel;

    void setupUI();
    void loadData();
    void saveData();
};

#endif // MAINWINDOW_H
