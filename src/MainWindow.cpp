#include "MainWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QGroupBox>
#include <QDate>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), dataFile("budget_data.csv") {
    setupUI();
    loadData();
    refreshTransactionTable();
    refreshSummary();
}

MainWindow::~MainWindow() {
    saveData();
}

void MainWindow::setupUI() {
    setWindowTitle("Budget Tracker");
    resize(900, 600);

    // Create central widget and main layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create tab widget
    tabWidget = new QTabWidget(this);
    mainLayout->addWidget(tabWidget);

    // ===== TAB 1: Add Transaction =====
    QWidget *addTab = new QWidget();
    QVBoxLayout *addLayout = new QVBoxLayout(addTab);

    QGroupBox *inputGroup = new QGroupBox("Add New Transaction");
    QFormLayout *formLayout = new QFormLayout();

    dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    formLayout->addRow("Date:", dateEdit);

    categoryEdit = new QLineEdit();
    categoryEdit->setPlaceholderText("e.g., Food, Rent, Salary");
    formLayout->addRow("Category:", categoryEdit);

    amountEdit = new QLineEdit();
    amountEdit->setPlaceholderText("0.00");
    formLayout->addRow("Amount:", amountEdit);

    typeCombo = new QComboBox();
    typeCombo->addItems({"income", "expense"});
    formLayout->addRow("Type:", typeCombo);

    descriptionEdit = new QLineEdit();
    descriptionEdit->setPlaceholderText("Brief description");
    formLayout->addRow("Description:", descriptionEdit);

    addButton = new QPushButton("Add Transaction");
    addButton->setStyleSheet("background-color: #4CAF50; color: white; padding: 10px; font-weight: bold;");
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addTransaction);

    inputGroup->setLayout(formLayout);
    addLayout->addWidget(inputGroup);
    addLayout->addWidget(addButton);
    addLayout->addStretch();

    tabWidget->addTab(addTab, "Add Transaction");

    // ===== TAB 2: View All Transactions =====
    QWidget *viewTab = new QWidget();
    QVBoxLayout *viewLayout = new QVBoxLayout(viewTab);

    transactionTable = new QTableWidget();
    transactionTable->setColumnCount(5);
    transactionTable->setHorizontalHeaderLabels({"Date", "Category", "Type", "Amount", "Description"});
    transactionTable->horizontalHeader()->setStretchLastSection(true);
    transactionTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    transactionTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    transactionTable->setAlternatingRowColors(true);

    viewLayout->addWidget(transactionTable);
    tabWidget->addTab(viewTab, "View All Transactions");

    // ===== TAB 3: Dashboard =====
    QWidget *dashboardTab = new QWidget();
    QVBoxLayout *dashLayout = new QVBoxLayout(dashboardTab);

    QGroupBox *summaryGroup = new QGroupBox("Financial Summary");
    QVBoxLayout *summaryLayout = new QVBoxLayout();

    incomeLabel = new QLabel("Total Income: $0.00");
    incomeLabel->setStyleSheet("font-size: 18px; color: green; font-weight: bold;");
    summaryLayout->addWidget(incomeLabel);

    expenseLabel = new QLabel("Total Expense: $0.00");
    expenseLabel->setStyleSheet("font-size: 18px; color: red; font-weight: bold;");
    summaryLayout->addWidget(expenseLabel);

    balanceLabel = new QLabel("Balance: $0.00");
    balanceLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    summaryLayout->addWidget(balanceLabel);

    summaryGroup->setLayout(summaryLayout);
    dashLayout->addWidget(summaryGroup);
    dashLayout->addStretch();

    tabWidget->addTab(dashboardTab, "Dashboard");
}

void MainWindow::addTransaction() {
    // Validate input
    QString dateStr = dateEdit->date().toString("yyyy-MM-dd");
    QString category = categoryEdit->text().trimmed();
    QString amountStr = amountEdit->text().trimmed();
    QString type = typeCombo->currentText();
    QString description = descriptionEdit->text().trimmed();

    if (category.isEmpty() || amountStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields.");
        return;
    }

    bool ok;
    double amount = amountStr.toDouble(&ok);
    if (!ok || amount <= 0) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid positive amount.");
        return;
    }

    // Create transaction
    Transaction t(dateStr.toStdString(), category.toStdString(), 
                  amount, type.toStdString(), description.toStdString());
    manager.addTransaction(t);

    // Clear inputs
    categoryEdit->clear();
    amountEdit->clear();
    descriptionEdit->clear();

    // Refresh displays
    refreshTransactionTable();
    refreshSummary();
    saveData();

    QMessageBox::information(this, "Success", "Transaction added successfully!");
}

void MainWindow::refreshTransactionTable() {
    const auto& transactions = manager.getTransactions();
    transactionTable->setRowCount(transactions.size());

    for (size_t i = 0; i < transactions.size(); ++i) {
        const Transaction& t = transactions[i];
        
        transactionTable->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(t.date)));
        transactionTable->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(t.category)));
        transactionTable->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(t.type)));
        transactionTable->setItem(i, 3, new QTableWidgetItem(QString::number(t.amount, 'f', 2)));
        transactionTable->setItem(i, 4, new QTableWidgetItem(QString::fromStdString(t.description)));

        // Color code by type
        QColor rowColor = (t.type == "income") ? QColor(200, 255, 200) : QColor(255, 200, 200);
        for (int col = 0; col < 5; ++col) {
            transactionTable->item(i, col)->setBackground(rowColor);
        }
    }
}

void MainWindow::refreshSummary() {
    double income = manager.totalIncome();
    double expense = manager.totalExpense();
    double balance = manager.balance();

    incomeLabel->setText(QString("Total Income: $%1").arg(income, 0, 'f', 2));
    expenseLabel->setText(QString("Total Expense: $%1").arg(expense, 0, 'f', 2));
    balanceLabel->setText(QString("Balance: $%1").arg(balance, 0, 'f', 2));

    // Change balance color based on positive/negative
    if (balance >= 0) {
        balanceLabel->setStyleSheet("font-size: 20px; color: green; font-weight: bold;");
    } else {
        balanceLabel->setStyleSheet("font-size: 20px; color: red; font-weight: bold;");
    }
}

void MainWindow::loadData() {
    manager.loadFromFile(dataFile.toStdString());
}

void MainWindow::saveData() {
    manager.saveToFile(dataFile.toStdString());
}