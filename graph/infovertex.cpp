#include "infovertex.h"
InfoVertex::InfoVertex()
{
    countIn=4;
    countOut=4;
    for (int i = 0; i < countIn; ++i) {
        lineIns.append(1);
    }
    for (int i = 0; i < countOut; ++i) {
        lineOuts.append(1);
    }
}

InfoVertex::InfoVertex(int countIn, int countOut)
{
    this->countIn=countIn;
    this->countOut=countOut;
    for (int i = 0; i < countIn; ++i) {
        lineIns.append(1);
    }
    for (int i = 0; i < countOut; ++i) {
        lineOuts.append(1);
    }
}

InfoVertex::InfoVertex(int countIn, int countOut, QVector<int> lineIns, QVector<int> lineOuts)
{
    this->countIn=countIn;
    this->countOut=countOut;
    this->lineIns=lineIns;
    this->lineOuts=lineOuts;
}

InfoVertex::~InfoVertex()
{

}

