#include "information.h"
#include "ui_information.h"

#include "bitcoinunits.h"
#include "guiutil.h"
#include "guiconstants.h"

#include <QScrollArea>
#include <QScroller>

InFormation::InFormation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InFormation)
{
    ui->setupUi(this);

    
}

InFormation::~InFormation()
{
    delete ui;
}