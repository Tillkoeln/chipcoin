#ifndef BLOCKEXPLORER_H
#define BLOCKEXPLORER_H

#include <QMainWindow>

#include "uint256.h"
#include "base58.h"

namespace Ui {
class BlockBrowser;
}

class CBlockIndex;
class CTransaction;

class BlockBrowser : public QMainWindow
{
    Q_OBJECT

public:
    explicit BlockBrowser(QWidget *parent = 0);
    ~BlockBrowser();

protected:
    void keyPressEvent(QKeyEvent *event);
    void showEvent(QShowEvent*);

private slots:
    void onSearch();
    void goTo(const QString& query);
    void back();
    void forward();

private:
    Ui::BlockBrowser *ui;
    bool m_NeverShown;
    int m_HistoryIndex;
    QStringList m_History;

    void setBlock(CBlockIndex* pBlock);
    bool switchTo(const QString& query);
    void setContent(const std::string &content);
    void updateNavButtons();
};

#endif // BLOCKEXPLORER_H
