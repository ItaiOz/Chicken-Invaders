#include "Board.h"



Board::Board()
{
    m_file.open("levels.txt");
    if (!m_file.is_open())
    {
        throw std::runtime_error("Can't load file");
    }
    // test file open   

    // get current line
    for (std::string name; getline(m_file, name, '\n');)
    {
        m_levels.push_back(name);
    }
    m_file.close();
    getnewline();

}

Board& Board::instance()
{
    static Board instance;
    return instance;
}

void Board::getnewline()
{
    if (m_levels.empty())
        return;
    int name;
    std::string T;
            T = m_levels.front();
            m_levels.pop_front();
            std::stringstream geek(T);

            while (geek >> name)m_line.push_back(name);
         
        //    for (auto& i : m_line)
          //      std::cout << i << "\n";
}

//returns database sizes
int Board::getData()
{
    int i;
     i = m_line.front();
     m_line.pop_front();
    
    // std::cout << i << "\n";
    return i;
}