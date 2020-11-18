#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>


namespace Ui {
    class InFormation;
}

/** Proof of meme page widget */
class InFormation : public QWidget
{
    Q_OBJECT

public:
    explicit InFormation(QWidget *parent = 0);
    ~InFormation();

public slots:

signals:

private:
    Ui::InFormation *ui;

private slots:
    
};

#endif