#include "aboutdialog.h"
#include "ui_aboutdialog.h"

#include "clientmodel.h"
#include "clientversion.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    // Set current copyright year
ui->copyrightLabel->setText(tr("Copyright") + QString(" &copy; 2009-2015 ").arg(COPYRIGHT_YEAR) + tr("The Bitcoin Core Developers") + QString("<br>") + tr("Copyright") + QString(" &copy; ") + tr("2014-2015 The Dash Core Developers").arg(COPYRIGHT_YEAR)
                                + QString("<br>") + tr("Copyright") + QString(" &copy; ") + tr("2015 - The Spreadcoin Core Developers").arg(COPYRIGHT_YEAR)  + QString("<br>") + tr("Copyright") + QString(" &copy; ") + tr("2015 - The Chipcoin Core Developers").arg(COPYRIGHT_YEAR));
}

void AboutDialog::setModel(ClientModel *model)
{
    if(model)
    {
        ui->versionLabel->setText(model->formatFullVersion());
    }
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    close();
}
