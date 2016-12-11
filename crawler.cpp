#include "crawler.h"
#include <log.h>
#include <QFile>
#include <QTextStream>
#include "terminal.h"
#include <QDebug>

WordPosition::WordPosition()
{

}

WordPosition::WordPosition(int file_id, int line_num, int sentence_num, std::__cxx11::string last_word, std::__cxx11::string next_word)
{
    this->file_id = file_id;
    this->line_num = line_num;
    this->sentence_num = sentence_num;
    this->last_word = last_word;
    this->next_word = next_word;
}

Crawler::Crawler()
{

}

FileWordNode::FileWordNode()
{
    this->next = NULL;
    this->last = NULL;
}

FileWordNode::FileWordNode(QString word,int line_num)
{
    FileWordNode();
    this->word = word;
    this->line_num = line_num;
}

void Word::add_position(WordPosition position)
{
    this->positions.push_back(position);
}

Crawler& Crawler::getInstance()
{
    static Crawler instance;
    return instance;
}

void Crawler::buildTree()
{
    qDebug() << "This is done";
    for (int i = 0; i < file_words_starts.size(); ++i)
    {
        if(file_words_starts[i])
            qDebug() << i;

        FileWordNode *pointer = file_words_starts[i]->next;


        while(pointer)
        {
            qDebug() << "point is not null";
            Terminal::getInstance().writeLine(pointer->word);
            pointer = pointer->next;
        }
    }
}

void Crawler::tokenizeString(QStringList &tokens,QString &line)
{
    tokens = line.split(QRegExp("\\W+"), QString::SkipEmptyParts);
}

bool Crawler::crawlFile(QString file_path)
{
    QFile file(file_path);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        Terminal::getInstance().writeError("error : Can't open \"" + file_path + "\"");
        return false;
    }

    this->file_words_starts.push_back(new FileWordNode());

    FileWordNode *last = this->file_words_starts[this->file_words_starts.size() - 1];

    QTextStream input(&file);
    QString line;
    QStringList wordsList;

    int line_num = 1;
    int wordCount = 1;

    while(!input.atEnd())
    {
        line = input.readLine();
        tokenizeString(wordsList, line);
        for(int i = 0; i < wordsList.size(); i++)
        {
            last->next = new FileWordNode(wordsList[i], line_num);
            last->next->last = last;
            last = last->next;
            wordCount ++;
        }

        line_num++;
    }

    Terminal::getInstance().writeLine(QString("File \"" + file_path + "\" crawled and %1 words detected.").arg(wordCount));

    return true;
}

void Crawler::add_directory(std::__cxx11::string dir_path)
{

}

void Crawler::crawlAll()
{
    Terminal::getInstance().writeLine("Start crawling on files ....");
    for(int i = 0; i < files_paths.size(); i++)
    {
        crawlFile(files_paths[i]);
    }
    Terminal::getInstance().writeLine(QString("%1 file(s) crawled.").arg(files_paths.size()));
}

bool Crawler::add_file_to_list(QString file_path)
{
    QFile file(file_path);
    if(file.exists())
    {
        files_paths.push_back(file_path);
        Terminal::getInstance().writeLine("File : \"" + file_path + "\" successfully added to the files' list.");
    }
    else {
        Terminal::getInstance().writeLine("File : \"" + file_path + "\" does not exist.");
    }
}

void Crawler::build(int type)
{
    switch (type) {
    case BST_TREE_TYPE:

        break;

    case TST_TREE_TYPE:

        break;

    case TRIE_TREE_TYPE:

        break;
    default:
        break;
    }
}

Crawler::~Crawler()
{

}
