#include "terminal.h"

Terminal::Terminal()
{
}

Terminal& Terminal::getInstance()
{
    static Terminal instance;

    return instance;
}


void Terminal::writeLine(QString line)
{
    terminalOutput->appendPlainText(line);
}

void Terminal::setObject(QPlainTextEdit *terminalOutput)
{
    this->terminalOutput = terminalOutput;
}
