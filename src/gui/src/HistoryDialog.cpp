#include "HistoryDialog.h"
#include "ui_historydialog.h"
#include "DatabaseManager.h"
#include "ReplayWindow.h"
#include <QMessageBox>
#include <QPushButton>

HistoryDialog::HistoryDialog(const User& user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HistoryDialog),
    currentUser_(user)
{
    ui->setupUi(this);
    
    QPushButton* replayButton = new QPushButton("Replay Selected Game", this);
    ui->verticalLayout->insertWidget(1, replayButton);

    connect(replayButton, &QPushButton::clicked, this, &HistoryDialog::onReplayClicked);

    populateHistory();
}

HistoryDialog::~HistoryDialog()
{
    delete ui;
}

void HistoryDialog::onReplayClicked() {
    QModelIndexList selection = ui->historyTableWidget->selectionModel()->selectedRows();
    if (selection.isEmpty()) {
        QMessageBox::warning(this, "No Selection", "Please select a game from the table to replay.");
        return;
    }
    
    int selectedRow = selection.first().row();
    const QString& movesString = gameRecords_[selectedRow].moves;

    if (movesString.isEmpty()) {
        QMessageBox::information(this, "No Replay", "This game record does not contain replay data (from before this feature was added).");
        return;
    }

    ReplayWindow replayWindow(movesString, this);
    replayWindow.exec();
}

void HistoryDialog::populateHistory() {
    gameRecords_ = DatabaseManager::getInstance().getGameHistory(currentUser_.getId());
    
    ui->historyTableWidget->setRowCount(gameRecords_.size());
    ui->historyTableWidget->setSortingEnabled(false);
    
    int row = 0;
    for (const auto& record : gameRecords_) {
        ui->historyTableWidget->setItem(row, 0, new QTableWidgetItem(record.date));
        ui->historyTableWidget->setItem(row, 1, new QTableWidgetItem(record.opponent));
        ui->historyTableWidget->setItem(row, 2, new QTableWidgetItem(record.winner));
        row++;
    }
    ui->historyTableWidget->resizeColumnsToContents();
}
