#ifndef HISTORYDIALOG_H
#define HISTORYDIALOG_H

#include <QDialog>
#include "User.h"
#include "GameRecord.h"
#include <vector>

namespace Ui {
class HistoryDialog;
}

class HistoryDialog : public QDialog {
    Q_OBJECT

public:
    explicit HistoryDialog(const User& user, QWidget *parent = nullptr);
    ~HistoryDialog();

private slots:
    void onReplayClicked();

private:
    void populateHistory();

    Ui::HistoryDialog *ui;
    User currentUser_;
    std::vector<GameRecord> gameRecords_;
};

#endif