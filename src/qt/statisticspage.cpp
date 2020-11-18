#include "statisticspage.h"
#include "ui_statisticspage.h"

#include "clientmodel.h"
#include "walletmodel.h"
#include "bitcoinunits.h"
#include "optionsmodel.h"
#include "main.h"
#include "bitcoinrpc.h"
#include "util.h"
#include "init.h"

#include <sstream>
#include <string>
double GetPoSKernelPS(const CBlockIndex* pindex);

using namespace json_spirit;



StatisticsPage::StatisticsPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsPage)
{
    ui->setupUi(this);
	ui->labelNetworkStatusCharts->setText(" (" + tr("Charts are turned off during syncing") + ")");
	
    // start with displaying the "out of sync" warnings
    showOutOfSyncWarning(true);
    if(GetBoolArg("-chart", true))
    {
		QFont label = font();
		
		//weight
        ui->diffplot_weight->addGraph();
		ui->diffplot_weight->setBackground(QBrush(QColor(255,255,255)));
        ui->diffplot_weight->xAxis->setLabel("Height");
        ui->diffplot_weight->yAxis->setLabel("Network Weight");
        ui->diffplot_weight->graph(0)->setPen(QPen(QColor(140,198,62), 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
		ui->diffplot_weight->graph(0)->setBrush(QBrush(QColor(140,198,62,30)));
        ui->diffplot_weight->xAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_weight->xAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_weight->xAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_weight->xAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_weight->xAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_weight->yAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_weight->yAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_weight->yAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_weight->yAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_weight->yAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_weight->yAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));		
        ui->diffplot_weight->xAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));
		ui->diffplot_weight->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->diffplot_weight->graph(0)->setLineStyle(QCPGraph::lsLine); 
        ui->diffplot_weight->xAxis->setLabelFont(label);
        ui->diffplot_weight->yAxis->setLabelFont(label);
		
		//difficulty pos
		ui->diffplot_pos->addGraph();
		ui->diffplot_pos->setBackground(QBrush(QColor(255,255,255)));
        ui->diffplot_pos->xAxis->setLabel("Height");
        ui->diffplot_pos->yAxis->setLabel("Difficulty PoS");
        ui->diffplot_pos->graph(0)->setPen(QPen(QColor(140,198,62), 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
		ui->diffplot_pos->graph(0)->setBrush(QBrush(QColor(140,198,62,30)));
        ui->diffplot_pos->xAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_pos->xAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_pos->xAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_pos->xAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pos->xAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pos->yAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_pos->yAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_pos->yAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_pos->yAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pos->yAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pos->yAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));		
        ui->diffplot_pos->xAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));
		ui->diffplot_pos->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->diffplot_pos->graph(0)->setLineStyle(QCPGraph::lsLine); 
		ui->diffplot_pos->xAxis->setLabelFont(label);
		ui->diffplot_pos->yAxis->setLabelFont(label);
		
		//Hash
        ui->diffplot_hash->addGraph();
		ui->diffplot_hash->setBackground(QBrush(QColor(255,255,255)));
        ui->diffplot_hash->xAxis->setLabel("Height");
        ui->diffplot_hash->yAxis->setLabel("Network Hashrate");
        ui->diffplot_hash->graph(0)->setPen(QPen(QColor(140,198,62), 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
		ui->diffplot_hash->graph(0)->setBrush(QBrush(QColor(140,198,62,30)));
        ui->diffplot_hash->xAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_hash->xAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_hash->xAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_hash->xAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_hash->xAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_hash->yAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_hash->yAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_hash->yAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_hash->yAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_hash->yAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_hash->yAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));		
        ui->diffplot_hash->xAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));
		ui->diffplot_hash->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->diffplot_hash->graph(0)->setLineStyle(QCPGraph::lsLine); 
        ui->diffplot_hash->xAxis->setLabelFont(label);
        ui->diffplot_hash->yAxis->setLabelFont(label);
		
		//difficulty pow
		ui->diffplot_pow->addGraph();
		ui->diffplot_pow->setBackground(QBrush(QColor(255,255,255)));
        ui->diffplot_pow->xAxis->setLabel("Height");
        ui->diffplot_pow->yAxis->setLabel("Difficulty PoW");
        ui->diffplot_pow->graph(0)->setPen(QPen(QColor(140,198,62), 3, Qt::SolidLine, Qt::SquareCap, Qt::BevelJoin));
		ui->diffplot_pow->graph(0)->setBrush(QBrush(QColor(140,198,62,30)));
        ui->diffplot_pow->xAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_pow->xAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_pow->xAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_pow->xAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pow->xAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pow->yAxis->setTickLabelColor(QColor(48,63,76));
        ui->diffplot_pow->yAxis->setBasePen(QPen(QColor(212,211,211)));
        ui->diffplot_pow->yAxis->setLabelColor(QColor(140,198,62));
        ui->diffplot_pow->yAxis->setTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pow->yAxis->setSubTickPen(QPen(QColor(212,211,211)));
        ui->diffplot_pow->yAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));		
        ui->diffplot_pow->xAxis->grid()->setPen(QPen(QColor(QColor(212,211,211)), 1, Qt::DotLine));
		ui->diffplot_pow->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->diffplot_pow->graph(0)->setLineStyle(QCPGraph::lsLine); 
		ui->diffplot_pow->xAxis->setLabelFont(label);
		ui->diffplot_pow->yAxis->setLabelFont(label);
	
    }

}

void StatisticsPage::updatePlot()
{
    static int64_t lastUpdate = 0;
    // Double Check to make sure we don't try to update the plot when it is disabled
    if(!GetBoolArg("-chart", true)) { return; }
    if (GetTime() - lastUpdate < 600) { return; } // This is just so it doesn't redraw rapidly during syncing

    if(fDebug) { printf("Plot: Getting Ready: pindexBest: %p\n", pindexBest); }
    	
		bool fProofOfStake = (nBestHeight > 1);
    if (fProofOfStake)
        ui->diffplot_weight->yAxis->setLabel("Network Weight");
		else
        ui->diffplot_weight->yAxis->setLabel("Network Weight");

    int numLookBack = 500;
    double diffMax = 0;
    const CBlockIndex* pindex = GetLastBlockIndex(pindexBest, fProofOfStake);
    int height = pindex->nHeight;
    int xStart = std::max<int>(height-numLookBack, 0) + 1;
    int xEnd = height;

    // Start at the end and walk backwards
    int i = numLookBack-1;
    int x = xEnd;

    // This should be a noop if the size is already 2000
    vX.resize(numLookBack);
    vY.resize(numLookBack);

    if(fDebug) {
        if(height != pindex->nHeight) {
            printf("Plot: Warning: nBestHeight and pindexBest->nHeight don't match: %d:%d:\n", height, pindex->nHeight);
        }
    }

    if(fDebug) { printf("Plot: Reading blockchain\n"); }

    const CBlockIndex* itr = pindex;
    while(i >= 0 && itr != NULL)
    {
        if(fDebug) { printf("Plot: Processing block: %d - pprev: %p\n", itr->nHeight, itr->pprev); }
        vX[i] = itr->nHeight;
        if (itr->nHeight < xStart) {
        	xStart = itr->nHeight;
        }
        vY[i] = fProofOfStake ? GetPoSKernelPS(itr) : GetDifficulty(itr);
        diffMax = std::max<double>(diffMax, vY[i]);

        itr = GetLastBlockIndex(itr->pprev, fProofOfStake);
        i--;
        x--;
    }

    if(fDebug) { printf("Plot: Drawing plot\n"); }

    ui->diffplot_weight->graph(0)->setData(vX, vY);

    // set axes ranges, so we see all data:
    ui->diffplot_weight->xAxis->setRange((double)xStart, (double)xEnd);
    ui->diffplot_weight->yAxis->setRange(0, diffMax+(diffMax/10));

    ui->diffplot_weight->xAxis->setAutoSubTicks(false);
    ui->diffplot_weight->yAxis->setAutoSubTicks(false);
    ui->diffplot_weight->xAxis->setSubTickCount(0);
    ui->diffplot_weight->yAxis->setSubTickCount(0);
	ui->diffplot_weight->yAxis->setNumberPrecision(10);

    ui->diffplot_weight->replot();
	
	    diffMax = 0;

    // Start at the end and walk backwards
    i = numLookBack-1;
    x = xEnd;
	// This should be a noop if the size is already 2000
    vX3.resize(numLookBack);
    vY3.resize(numLookBack);

    const CBlockIndex* itr3 = pindex;

    while(i >= 0 && itr3 != NULL)
    {
        vX3[i] = itr3->nHeight;
        vY3[i] = fProofOfStake ? GetDifficulty(itr3) : GetPoSKernelPS(itr3);
        diffMax = std::max<double>(diffMax, vY3[i]);

        itr3 = GetLastBlockIndex(itr3->pprev, fProofOfStake);
        i--;
        x--;
    }

    ui->diffplot_pos->graph(0)->setData(vX3, vY3);

    // set axes ranges, so we see all data:
    ui->diffplot_pos->xAxis->setRange((double)xStart, (double)xEnd);
    ui->diffplot_pos->yAxis->setRange(0, diffMax+(diffMax/10));

    ui->diffplot_pos->xAxis->setAutoSubTicks(false);
    ui->diffplot_pos->yAxis->setAutoSubTicks(false);
    ui->diffplot_pos->xAxis->setSubTickCount(0);
    ui->diffplot_pos->yAxis->setSubTickCount(0);
	ui->diffplot_pos->yAxis->setNumberFormat("f");
	ui->diffplot_pos->yAxis->setNumberPrecision(8);

    ui->diffplot_pos->replot();

    

    if(fDebug) { printf("Plot: Done!\n"); }
    	
    lastUpdate = GetTime();
}

void StatisticsPage::updatePlot2()
{
    static int64_t lastUpdate = 0;
    // Double Check to make sure we don't try to update the plot when it is disabled
    if(!GetBoolArg("-chart", true)) { return; }
    if (GetTime() - lastUpdate < 600) { return; } // This is just so it doesn't redraw rapidly during syncing

    if(fDebug) { printf("Plot: Getting Ready: pindexBest: %p\n", pindexBest); }
    	
		bool fProofOfStake = (nBestHeight > LAST_POW_BLOCK);
    if (fProofOfStake)
        ui->diffplot_pow->yAxis->setLabel("Difficulty PoW");
		else
        ui->diffplot_pow->yAxis->setLabel("Difficulty PoW");

    int numLookBack = 500;
    double diffMax = 0;
    const CBlockIndex* pindex = GetLastBlockIndex(pindexBest, fProofOfStake);
    int height = pindex->nHeight;
    int xStart = std::max<int>(height-numLookBack, 0) + 1;
    int xEnd = height;

    // Start at the end and walk backwards
    int i = numLookBack-1;
    int x = xEnd;

    // This should be a noop if the size is already 2000
    vX2.resize(numLookBack);
    vY2.resize(numLookBack);

    if(fDebug) {
        if(height != pindex->nHeight) {
            printf("Plot: Warning: nBestHeight and pindexBest->nHeight don't match: %d:%d:\n", height, pindex->nHeight);
        }
    }

    if(fDebug) { printf("Plot: Reading blockchain\n"); }

    const CBlockIndex* itr2 = pindex;
    while(i >= 0 && itr2 != NULL)
    {
        if(fDebug) { printf("Plot: Processing block: %d - pprev: %p\n", itr2->nHeight, itr2->pprev); }
        vX2[i] = itr2->nHeight;
        if (itr2->nHeight < xStart) {
        	xStart = itr2->nHeight;
        }
        vY2[i] = fProofOfStake ? GetPoSKernelPS(itr2) : GetDifficulty(itr2);
        diffMax = std::max<double>(diffMax, vY2[i]);

        itr2 = GetLastBlockIndex(itr2->pprev, fProofOfStake);
        i--;
        x--;
    }

    if(fDebug) { printf("Plot: Drawing plot\n"); }

    ui->diffplot_pow->graph(0)->setData(vX2, vY2);

    // set axes ranges, so we see all data:
    ui->diffplot_pow->xAxis->setRange((double)xStart, (double)xEnd);
    ui->diffplot_pow->yAxis->setRange(0, diffMax+(diffMax/10));

    ui->diffplot_pow->xAxis->setAutoSubTicks(false);
    ui->diffplot_pow->yAxis->setAutoSubTicks(false);
    ui->diffplot_pow->xAxis->setSubTickCount(0);
    ui->diffplot_pow->yAxis->setSubTickCount(0);
	ui->diffplot_pow->yAxis->setNumberFormat("f");
	ui->diffplot_pow->yAxis->setNumberPrecision(8);

    ui->diffplot_pow->replot();
	
	
	 diffMax = 0;

    // Start at the end and walk backwards
    i = numLookBack-1;
    x = xEnd;
	// This should be a noop if the size is already 2000
    vX4.resize(numLookBack);
    vY4.resize(numLookBack);

    const CBlockIndex* itr4 = pindex;

    while(i >= 0 && itr4 != NULL)
    {
        vX4[i] = itr4->nHeight;
        vY4[i] = fProofOfStake ? GetPoSKernelPS(itr4) : GetPoWMHashPS(itr4);
        diffMax = std::max<double>(diffMax, vY4[i]);

        itr4 = GetLastBlockIndex(itr4->pprev, fProofOfStake);
        i--;
        x--;
    }

    ui->diffplot_hash->graph(0)->setData(vX4, vY4);

    // set axes ranges, so we see all data:
    ui->diffplot_hash->xAxis->setRange((double)xStart, (double)xEnd);
    ui->diffplot_hash->yAxis->setRange(0, diffMax+(diffMax/10));

    ui->diffplot_hash->xAxis->setAutoSubTicks(false);
    ui->diffplot_hash->yAxis->setAutoSubTicks(false);
    ui->diffplot_hash->xAxis->setSubTickCount(0);
    ui->diffplot_hash->yAxis->setSubTickCount(0);
	ui->diffplot_hash->yAxis->setNumberPrecision(10);

    ui->diffplot_hash->replot();


    if(fDebug) { printf("Plot: Done!\n"); }
    	
    lastUpdate = GetTime();
}

void StatisticsPage::setModel(ClientModel *model)
{
    //updateStatistics();
    this->model = model;
}

void StatisticsPage::setModel2(ClientModel *model2)
{
    //updateStatistics();
    this->model2 = model2;
}

void StatisticsPage::showOutOfSyncWarning(bool fShow)
{
	ui->labelNetworkStatusCharts->setVisible(fShow);
}

StatisticsPage::~StatisticsPage()
{
    delete ui;
}
