#include "BoggleBoard.h"

BoggleBoard::BoggleBoard(const string& pathToDictionary)
: words(pathToDictionary)
{
    string faces[25][6]
    {
        { "N", "S", "C", "T", "E", "C" },
        { "A", "E", "A", "E", "E", "E" },
        { "H", "H", "L", "R", "O", "D" },
        { "O", "R", "W", "V", "G", "R" },
        { "S", "P", "R", "I", "Y", "Y" },
        { "S", "U", "E", "N", "S", "S" },
        { "M", "E", "A", "U", "E", "G" },
        { "S", "E", "P", "T", "I", "C" },
        { "D", "H", "H", "O", "W", "N" },
        { "L", "E", "P", "T", "I", "S" },
        { "S", "T", "L", "I", "E", "I" },
        { "A", "R", "S", "I", "Y", "F" },
        { "T", "E", "T", "I", "I", "I" },
        { "O", "T", "T", "T", "M", "E" },
        { "N", "M", "N", "E", "G", "A" },
        { "N", "N", "E", "N", "A", "D" },
        { "O", "U", "O", "T", "T", "O" },
        { "B", "Z", "J", "B", "X", "K" },
        { "A", "A", "F", "A", "S", "R" },
        { "T", "O", "O", "U", "W", "N" },
        { "O", "T", "H", "D", "D", "N" },
        { "R", "A", "A", "S", "F", "I" },
        { "H", "O", "D", "R", "L", "N" },
        { "E", "E", "E", "E", "A", "M" },
        { "He", "Qu", "Th", "In", "Er", "An" }
    };

    // randomly shuffles postion of die board.
    random_shuffle(faces[0], faces[24]);
    foundWords.resize(25);
    int k = 0;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            Die* a = new Die;
            // picks random side of die (result of a die roll)
            a->text = faces[k][rand() % 6]; k++;
            a->text[0] = char(int(a->text[0]) + 32);
            a->x = j;
            a->y = i;
            board[i][j] = a;
        }
    }
}
//--
BoggleBoard::~BoggleBoard()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            delete board[i][j];
        }
    }
}
//--
void BoggleBoard::solve()
{
    TrieElement* c = words.p_root;
    unordered_set < Die* > travelled;

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            solveHelper(board[i][j], traverse(board[i][j], c), travelled);
        }
    }
    printWords();
}
//--
void BoggleBoard::solveHelper(Die* d, TrieElement* c, unordered_set < Die* > travelled)
{
    travelled.insert(d);
    if (!c) return;
    if (c->isCompletedWord)
    {
        foundWords[c->wordSoFar.length() - 4].insert(c->wordSoFar);
    }
    Die* dir[8] {west(d), southWest(d), south(d), southEast(d), east(d), northEast(d), north(d), northWest(d)};

    for (int i = 0; i < 8; i++)
    {
        if (dir[i])
        {
            if (!travelled.count(dir[i]))
            {
                solveHelper(dir[i], traverse(dir[i], c), travelled);
            }   
        }
    }
    return;
}
//--
void BoggleBoard::printBoard()
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout<<char(int(board[i][j]->text[0])-32)<<" ";
        }
        cout<<endl;
    }
}
//--
void BoggleBoard::printWords()
{
    int sum = 0;

    for (int i = 0; i < 25; i++)
    {
        if (foundWords[i].size())
        {
            sum += foundWords[i].size();
            cout<<i+4<<" Letter Words: \n";

            for (auto j : foundWords[i])
            {
                
                for (int k = 0; k < j.length(); k++)
                {
                    cout<<char(int(j[k])-32);
                }
                cout<<endl;
            }
            cout<<endl;
        }
    }
    cout<<"I found "<<sum<<" words!\n";
}
//--
/* this method traverses from a point c on the trie through the text on a given die d.
For example if your point is root->subTries[0] (the a directly attached to the root)
and you give it the text "He", it will give you a pointer to p.root->a->h->e if it exists. */
TrieElement* BoggleBoard::traverse(Die* d, TrieElement* c)
{
    if (d->text.length() == 2)
    {
        if (c->subTries[int(d->text[0]) - 97])
        {
            if (c->subTries[int(d->text[0]) - 97]->subTries[int(d->text[1]) - 97])
            {
                return c->subTries[int(d->text[0]) - 97]->subTries[int(d->text[1]) - 97];
            }
        }
    }
    else if (d->text.length())
    {
        if (c->subTries[int(d->text[0]) - 97])
        {
            return c->subTries[int(d->text[0]) - 97];
        }
    }
    return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::west(BoggleBoard::Die* d)
{
    if (d->x > 0)
    {
        return board[d->y][d->x - 1];
    }
    else return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::southWest(BoggleBoard::Die* d)
{
    if (south(d) and west(d))
    {
        return board[d->y + 1][d->x - 1];
    }
    else return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::south(BoggleBoard::Die* d)
{
    if (d->y < 4)
    {
        return (board[d->y + 1][d->x]);
    }
    else return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::southEast(BoggleBoard::Die* d)
{
    if (south(d) and (east(d)))
    {
        return board[d->y + 1][d->x + 1];
    }
    else return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::east(BoggleBoard::Die* d)
{
    if (d->x < 4)
    {
        return board[d->y][d->x + 1];
    }
    else return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::northEast(BoggleBoard::Die* d)
{
    if (north(d) and east(d))
    {
        return board[d->y - 1][d->x + 1];
    }
    else return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::north(BoggleBoard::Die* d)
{
    if (d->y > 0)
    {
        return board[d->y - 1][d->x];
    }
    else return NULL;
}
//--
BoggleBoard::Die* BoggleBoard::northWest(BoggleBoard::Die* d)
{
    if (north(d) and west(d))
    {
        return board[d->y - 1][d->x - 1];
    }
    else return NULL;
}