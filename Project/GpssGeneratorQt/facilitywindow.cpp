#include "facilitywindow.h"
#include <QMessageBox>

namespace GeneratorGpss
{

FacilityWindow::FacilityWindow(int id, NetworkDescriptor *netDesc, QWidget *parent) : AbstractNavigatableWindow(parent)
{
    this->id=id;
    this->netDescriptor=netDesc;

    facilityName.setText(trUtf8("Устройство b%1").arg(id));
    mainLayout.addWidget(&facilityName);

    chanelsLabel.setText(trUtf8("Количество каналов: "));
    chanelLayout.addWidget(&chanelsLabel);
    chanelLayout.addWidget(&chanels);
    chanelLayout.addStretch(1);
    mainLayout.addLayout(&chanelLayout);

    memoryTypeLbl.setText(trUtf8("Тип накопителя: "));
    memoryType.addItem(trUtf8("Бесконечный"));
    memoryType.addItem(trUtf8("Ограниченный"));
    memoryValueLbl.setText(trUtf8("Объем накопителя: "));
    memoryLayout.addWidget(&memoryTypeLbl);
    memoryLayout.addWidget(&memoryType);
    memoryLayout.addWidget(&memoryValueLbl);
    memoryLayout.addWidget(&memoryValue);
    memoryValueLbl.hide();
    memoryValue.hide();
    memoryLayout.addStretch(1);
    mainLayout.addLayout(&memoryLayout);
    connect(&memoryType,SIGNAL(currentIndexChanged(int)),this,SLOT(memoryTypeChanged(int)));

    addStatisticNodeAllThreads.setText(trUtf8("Собирать статистику для всего узла (для всех потоков)"));
    addStatisticNodeAllThreads.setChecked(true);
    addStatisticQueueAllThreads.setText(trUtf8("Собирать статистику для накопителя узла (для всех потоков)"));
    addStatisticQueueAllThreads.setChecked(true);
    statisticAllThreadsLayout.addWidget(&addStatisticNodeAllThreads);
    statisticAllThreadsLayout.addWidget(&addStatisticQueueAllThreads);
    mainLayout.addLayout(&statisticAllThreadsLayout);

    vector<ThreadDescriptor> *pThreads=netDescriptor->getThreads();
    for(int i=0;i<pThreads->size();i++)
    {
        facilityThreadParams.push_back(new FacilityThreadParams((*pThreads)[i].getId()));
        threadTabs.addTab(facilityThreadParams.back(),trUtf8("Поток №%1").arg((*pThreads)[i].getId()));
    }
    mainLayout.addWidget(&threadTabs);

    addNavigation();
    this->setLayout(&mainLayout);
}

void FacilityWindow::memoryTypeChanged(int i)
{
    switch(i)
    {
    case 0:
        memoryValueLbl.hide();
        memoryValue.hide();
        break;
    case 1:
        memoryValueLbl.show();
        memoryValue.setText("");
        memoryValue.show();
        break;
    }
}

int FacilityWindow::getId()
{
    return id;
}

int FacilityWindow::getChanelAmount()
{
    return chanels.text().toInt();
}

vector<FacilityThreadParams*> *FacilityWindow::getFacilityThreadParams()
{
    return &facilityThreadParams;
}

bool FacilityWindow::statNodeAllThreads()
{
    return addStatisticNodeAllThreads.isChecked();
}

bool FacilityWindow::statQueueAllThreads()
{
    return addStatisticQueueAllThreads.isChecked();
}

void FacilityWindow::updateDescriptor()
{
}

void FacilityWindow::updateInterface()
{
    vector<ThreadDescriptor> *pThreads=netDescriptor->getThreads();

    //добавляемм табы для новых потоков
    for(int i=0;i<pThreads->size();i++)
    {
        bool found=false;
        for(int j=0;j<facilityThreadParams.size();j++)
        {
            if(facilityThreadParams[j]->getId()==(*pThreads)[i].getId())
            {
                found=true;
                break;
            }
        }
        if(!found)
        {
            facilityThreadParams.push_back(new FacilityThreadParams((*pThreads)[i].getId()));
            threadTabs.addTab(facilityThreadParams.back(),trUtf8("Поток №%1").arg((*pThreads)[i].getId()));
        }
    }

    bool wereChanges=true;
    while(wereChanges)
    {
        wereChanges=false;
        for(int i=0;i<facilityThreadParams.size();i++)
        {
            bool exist=false;
            for(int j=0;j<pThreads->size();j++)
            {
                if(facilityThreadParams[i]->getId()==(*pThreads)[j].getId())
                {
                    exist=true;
                    break;
                }
            }
            if(!exist)
            {
                threadTabs.removeTab(i);
                facilityThreadParams.erase(facilityThreadParams.begin()+i);
                wereChanges=true;
                break;
            }
        }
    }
}

FacilityWindow::~FacilityWindow()
{
    for(int i=0;i<facilityThreadParams.size();i++)
    {
        delete facilityThreadParams[i];
    }
}

FacilityThreadParams::FacilityThreadParams(int id, QWidget *parent):QWidget(parent)
{
    this->id=id;
    usingInThread.setText(trUtf8("Используется в потоке"));
    usingInThread.setChecked(false);
    connect(&usingInThread,SIGNAL(clicked(bool)),this,SLOT(usingInThreadChecked(bool)));
    mainLayout.addWidget(&usingInThread);

    funcParams.setDisabled(true);
    mainLayout.addWidget(&funcParams);

    addStatisticNode.setDisabled(true);
    addStatisticNode.setText(trUtf8("Собирать статистику для всего узла"));
    addStatisticNode.setChecked(true);
    mainLayout.addWidget(&addStatisticNode);

    addStatisticQueue.setDisabled(true);
    addStatisticQueue.setText(trUtf8("Собирать статистику для накопителя узла"));
    addStatisticQueue.setChecked(true);
    mainLayout.addWidget(&addStatisticQueue);

    mainLayout.addStretch(1);
    this->setLayout(&mainLayout);
}

int FacilityThreadParams::getId()
{
    return id;
}

bool FacilityThreadParams::IsUsingInThread()
{
    return usingInThread.isChecked();
}

bool FacilityThreadParams::statNode()
{
    return addStatisticNode.isChecked();
}

bool FacilityThreadParams::statQueue()
{
    return addStatisticQueue.isChecked();
}

FacilityFunctionWidget *FacilityThreadParams::getFuncParams()
{
    return &funcParams;
}

void FacilityThreadParams::usingInThreadChecked(bool checked)
{
    funcParams.setDisabled(!checked);
    addStatisticNode.setDisabled(!checked);
    addStatisticQueue.setDisabled(!checked);
}

FacilityFunctionWidget::FacilityFunctionWidget(QWidget *parent)
{
    funcTypeLbl.setText(trUtf8("Закон обработки: "));
    funcType.addItem(trUtf8("Экспоненциальный"),QVariant::fromValue((int)EXPONENTIAL));
    funcType.addItem(trUtf8("Равномерный"),QVariant::fromValue((int)UNIFORM));
    funcType.addItem(trUtf8("Треугольный"),QVariant::fromValue((int)TRIANGLE));
    param1Lbl.setText(trUtf8("Лямбда: "));
    param2Lbl.setText(trUtf8("Смещение: "));

    mainLayout.addWidget(&funcTypeLbl);
    mainLayout.addWidget(&funcType);
    mainLayout.addWidget(&param1Lbl);
    mainLayout.addWidget(&param1);
    mainLayout.addWidget(&param2Lbl);
    mainLayout.addWidget(&param2);
    mainLayout.addWidget(&param3Lbl);
    mainLayout.addWidget(&param3);
    mainLayout.addStretch(1);
    param3Lbl.hide();
    param3.hide();

    this->setLayout(&mainLayout);
    connect(&funcType,SIGNAL(currentIndexChanged(int)),this,SLOT(functionTypeChanged(int)));
}

void FacilityFunctionWidget::functionTypeChanged(int i)
{
    switch(i)
    {
    case 0:
        param1Lbl.setText(trUtf8("Лямбда: "));
        param2Lbl.setText(trUtf8("Смещение: "));
        param3Lbl.hide();
        param3.hide();
        break;
    case 1:
        param1Lbl.setText(trUtf8("Минимум: "));
        param2Lbl.setText(trUtf8("Максимум: "));
        param3Lbl.hide();
        param3.hide();
        break;
    case 2:
        param1Lbl.setText(trUtf8("Минимум: "));
        param2Lbl.setText(trUtf8("Максимум: "));
        param3Lbl.setText(trUtf8("Вершина"));
        param3Lbl.show();
        param3.show();
        break;
    }
}

FunctionTypeEnum FacilityFunctionWidget::getFuncType()
{
    return (FunctionTypeEnum)funcType.itemData(funcType.currentIndex()).toInt();
}

QString FacilityFunctionWidget::getParam1()
{
    return param1.text();
}

QString FacilityFunctionWidget::getParam2()
{
    return param2.text();
}

QString FacilityFunctionWidget::getParam3()
{
    return param3.text();
}

}