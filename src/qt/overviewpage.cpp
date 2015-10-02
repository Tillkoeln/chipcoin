#include "overviewpage.h"
#include "ui_overviewpage.h"

#include "bitcoingui.h"

#include "guiheader.h"

#include <QDebug>

OverviewPage::OverviewPage(QWidget *parent, BitcoinGUI *_gui):
    QWidget(parent),
    gui(_gui),
    ui(new Ui::OverviewPage)
{
    ui->setupUi(this);

    //#a13469 #6c3d94

    ui->labelIntroText->setStyleSheet(".QLabel{color:#000000; border: 1px solid black;background-color: #87878D; padding:10px;}");
    ui->labelIntroText->setText("<b>Welcome back to your own private Chipcoin bank! - "
                                ""
                                "Don't forget to back-up your wallet on a regular basis.</b>");
#ifdef Q_OS_WIN32
    ui->labelIntroText->setFixedHeight(50);
#else
    ui->labelIntroText->setFixedHeight(60);
#endif

    ClickableLabel *JumpSelector = new ClickableLabel();//Label(this);
    ClickableLabel *JumpSelector2 = new ClickableLabel();
    ClickableLabel *JumpSelector3 = new ClickableLabel();


    JumpSelector->setStyleSheet(".ClickableLabel{background-color: #87878D; border: none; border-radius: 10px; padding:10px;}");
    JumpSelector2->setStyleSheet(".ClickableLabel{background-color: #87878D; border: none; border-radius: 10px; padding:10px;}");
    JumpSelector3->setStyleSheet(".ClickableLabel{background-color: #87878D; border: none; border-radius: 10px; padding:10px;}");


    JumpSelector->setWordWrap(true);
    JumpSelector2->setWordWrap(true);
    JumpSelector3->setWordWrap(true);


    JumpSelector->setCursor(QCursor(Qt::PointingHandCursor));
    JumpSelector2->setCursor(QCursor(Qt::PointingHandCursor));
    JumpSelector3->setCursor(QCursor(Qt::PointingHandCursor));


    JumpSelector->setText("<span style='font-size:12pt; color:#FFFFFF;'><b>Chip Bank</b></span><br><br>"
                   "<span style='font-size:10pt; color:#FFFFFF;'>Your Private Wallet.</span>");
    JumpSelector2->setText("<span style='font-size:12pt; color:#FFFFFF;'><b>Mining</b></span><br><br>"
                    "<span style='font-size:10pt; color:#FFFFFF;'>Network Information And Mining Panel</span>");
    JumpSelector3->setText("<span style='font-size:12pt; color:#FFFFFF;'><b>Configuration</b></span><br><br>"
                    "<span style='font-size:10pt; color:#FFFFFF;'>Customize The Wallet To Your Own Needs.</span>");

    JumpSelector->setAlignment(Qt::AlignCenter);
    JumpSelector2->setAlignment(Qt::AlignCenter);
    JumpSelector3->setAlignment(Qt::AlignCenter);


    JumpSelector->setFixedWidth(200);
    JumpSelector->setMinimumHeight(100);
    JumpSelector2->setFixedWidth(200);
    JumpSelector2->setMinimumHeight(100);
    JumpSelector3->setFixedWidth(200);
    JumpSelector3->setMinimumHeight(100);


    ui->gridLayout->addWidget(JumpSelector,0,0,Qt::AlignCenter);
  
    ui->gridLayout->addWidget(JumpSelector2,0,1,Qt::AlignCenter);
    ui->gridLayout->addWidget(JumpSelector3,0,2,Qt::AlignCenter);

    connect(JumpSelector, SIGNAL(clicked()), this,SLOT(gotoSendCoinsPage()));
    connect(JumpSelector2, SIGNAL(clicked()), this,SLOT(gotoMiningInfoPage()));
    connect(JumpSelector3, SIGNAL(clicked()), this,SLOT(gotoSettings()));


    ui->linkLabel1->setStyleSheet(".QLabel{color:#FFFFFF; background-color: #87878D; border: none; border-radius: 10px; padding:10px;}");
    ui->linkLabel2->setStyleSheet(".QLabel{color:#FFFFFF; background-color: #87878D; border: none; border-radius: 10px; padding:10px;}");
    ui->linkLabel3->setStyleSheet(".QLabel{color:#FFFFFF; background-color: #87878D; border: none; border-radius: 10px; padding:10px;}");	

    ui->linkLabel1->setOpenExternalLinks(true);
    ui->linkLabel2->setOpenExternalLinks(true);
    ui->linkLabel3->setOpenExternalLinks(true);

    ui->linkLabel1->setTextFormat(Qt::RichText);

    ui->linkLabel1->setText("<a style='text-decoration:none; ' href='http://www.chipcoin.info'>"
                            "<span style='font-size:12pt; font-weight:300; color:#FFFFFF;'><b>Official Chipcoin Website</b></span><br>"
                            "<span style='font-size:8pt; font-weight:300; color:#FFFFFF;'>Home For All Your Needs</span>"
                            "</a>");
    ui->linkLabel2->setText("<a style='text-decoration:none; ' href='https://bitcointalk.org/index.php?topic=1188983.0'>"
                            "<span style='font-size:12pt; font-weight:300; color:#FFFFFF;'><b>Bitcointalk.org Discussion Thread</b></span><br>"
                            "<span style='font-size:8pt; font-weight:300; color:#FFFFFF;'>Community Discussions And Support Thread</span>"
                            "</a>");
    ui->linkLabel3->setText("<a style='text-decoration:none; ' href='http://chip.blockpioneers.pw'>"
                            "<span style='font-size:12pt; font-weight:300; color:#FFFFFF;'><b>Block Explorer</b></span><br>"
                            "<span style='font-size:8pt; font-weight:300; color:#FFFFFF;'>Transactions And Richlist</span>"
                            "</a>");
}

OverviewPage::~OverviewPage()
{
    delete ui;
}

void OverviewPage::gotoSendCoinsPage()
{

    gui->gotoSendCoinsPage();
}



void OverviewPage::gotoMiningInfoPage()
{
    gui->gotoMiningInfoPage();
}

void OverviewPage::gotoSettings()
{
    gui->optionsClicked();
}
