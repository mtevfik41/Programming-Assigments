// concordance.cpp reassambles a text from a concordance, which is a list of words and their
// contexts

#include <bits/stdc++.h>
using namespace std;

#define WORD_SIZE 20

struct concordance
{
    int line;
    int context_size;

    char (*context)[WORD_SIZE];
    char *word;
    char *next_word;

    concordance();                       // constructor
    concordance(const concordance &obj); // copy constructor
    ~concordance() { delete[] context; } // destructor
    void set_word(int pos);
};
// this is an inserter for outputting a vector of concordance objects
ostream &operator<<(ostream &stream, vector<concordance> obj);
istream &operator>>(istream &stream, concordance &obj);

// check_context - takes two objects which it tests to see if the are adjacent words, obj1 should be lower
bool check_context(concordance obj1, concordance obj2);

// is_word - determines from a string if it is the word, depending on the presence of
//			   the * character
bool is_word(char *str);

// get_line - uses another vector to pick out and add concordances on a certain line
vector<concordance> get_line(vector<concordance> &v1, int l);

// find_next - tries to find the next word in the sequence, otherwise it returns
// an iterator to end()
vector<concordance>::iterator find_next(vector<concordance> &v1,
                                        vector<concordance>::iterator it);

// get_first - retrieves the first word of any given line, otherwise returns an
// iterator to end()
vector<concordance>::iterator get_first(vector<concordance> &v1, int l);

// MEMBER FUNCTIONS OF concordance --------------------------------------------------------------
concordance::concordance()
{
    line = 0;
    context_size = 5; // default value for context size
    context = NULL;
    word = next_word = NULL;
}

concordance::concordance(const concordance &obj)
{
    // copy the variables first
    line = obj.line;
    context_size = obj.context_size;

    context = new char[obj.context_size][WORD_SIZE];
    for (int i = 0; i < context_size; ++i) // copy context from obj to this
        strcpy(context[i], obj.context[i]);

    // word and next_word are first set to NULL
    word = next_word = NULL;
    // we then find the position of the word in the context
    for (int i = 0; i < context_size; ++i)
    {
        if (is_word(context[i]))
        {
            set_word(i);
            break;
        }
    }
}
//-----------------------------------------------------------------------------------------------

void concordance::set_word(int pos)
{
    if (word == NULL && pos < context_size)
        word = context[pos];
    else if (word != NULL)
        cerr << "Multiple words in one concordance!" << endl;

    if (pos + 1 < context_size)
        next_word = context[pos + 1];
}

int main(int argc, char *argv[])
{
    // SECTION 1 of main() - get input from the file and copy it into one vector.  At the end of
    //					   this section, the vector will contain every concordance in the file.
    // -----------------------------------------------------------------------------------------------
    if (argc < 3)
    {
        cerr << "concordance.exe requires 2 extra parameters \n";
        cerr << "- filename1 (for input) \n- filename2 (for output)";
        cerr << endl;
        exit(1);
    }

    ifstream text(argv[1]); // for input
    if (!text)
    {
        cerr << "Input file failed to open" << endl;
        exit(1);
    }

    ofstream out(argv[2]); // for output of reconstructed text
    if (!out)
    {
        cerr << "Output file failed to open" << endl;
        exit(1);
    }

    vector<concordance> conc; // this will hold all the concordances
    while (text)
    {
        concordance temp; // a temporary variable to push_back onto conc
        text >> temp;
        conc.push_back(temp);
    }

    // SECTION 2 of main() - while get_first() returns a valid iterator (meaning that line
    //					   must exist, call get_line().  The vector returned is sorted by
    //					   getting the first word of the line, and then using get_next() to
    //					   build up the line.  Then output the line once it is finished.
    // ------------------------------------------------------------------------------------------------
    vector<concordance>::iterator it, curr;
    for (int i = 1;; ++i) // line loop
    {
        // if the first word of the line can't be found, terminate the loop
        if (get_first(conc, i) == conc.end())
            break;

        vector<concordance> temp = get_line(conc, i); // populate t with all the items from that line
        vector<concordance> nline;                    // nline will hold all the words from that line, sorted

        it = get_first(temp, i); // search for the first word of that line
        nline.push_back(*it);    // bring that to the front of the newline vector

        for (;;) // word loop
        {
            it = find_next(temp, it); // keep finding the next in sequence
            if (it != temp.end())
                nline.push_back(*it); // add it to the end of the vector
            else
                break;
        }
        out << nline << endl; // you can use cout to print to console also, but this writes
                              // to the specified file
    }

    text.close();
    out.close();
    return 0;
}

istream &operator>>(istream &stream, concordance &obj)
{
    stream.ignore(20, ':'); // the first two characters of a line are the text number and a colon
    stream >> obj.line;

    obj.context = new char[obj.context_size][WORD_SIZE];

    for (int i = 0; i < obj.context_size && stream.peek() != '\n'; ++i) // get every word from the line in file
    {
        stream >> obj.context[i];
        // check to see if input is the word
        if (is_word(obj.context[i]))
            obj.set_word(i);
    }
    return stream;
}

ostream &operator<<(ostream &stream, vector<concordance> obj)
{
    vector<concordance>::iterator it;

    for (it = obj.begin(); it != obj.end(); ++it)
        stream << it->word + 1 << " "; // output the current word minus the * character

    return stream;
}

vector<concordance> get_line(vector<concordance> &v1, int l)
{
    vector<concordance> line_vector; // this will hold all words in line l
    vector<concordance>::iterator it;

    // we will be iterating through the entire vector
    for (it = v1.begin(); it != v1.end(); ++it)
    {
        if (it->line == l)
            line_vector.push_back(*it);
    }

    // the vector should now be populated with all the elements from line l
    return line_vector;
}

vector<concordance>::iterator find_next(vector<concordance> &v1,
                                        vector<concordance>::iterator it)
{
    vector<concordance>::iterator curr;

    // "curr" is an iterator to the concordance to be added next, "it" is an iterator
    // to the previous concordance that has already been added
    for (curr = v1.begin(); curr != v1.end(); ++curr)
    {
        // first test to see if they are a match, then, if they are check the contexts
        if (strcmp(curr->word + 1, it->next_word) == 0)
            if (check_context(*it, *curr))
                return curr;
    }

    // if this point has been reached, the object hasn't been found, therefore,
    // end() must be returned
    return v1.end();
}

vector<concordance>::iterator get_first(vector<concordance> &v1, int l)
{
    vector<concordance>::iterator it;

    for (it = v1.begin(); it != v1.end(); ++it)
    {
        // the test for the first word is it has no preceding context - therefore
        // is it's the first word in the context
        if (it->word == it->context[0] && it->line == l)
            return it;
    }

    // if this point has been reached, the object hasn't been found, also meaning
    // that this line doesn't exist in the text
    return v1.end();
}

bool is_word(char *str)
{
    if (!str)
        return false; // if there is no word, return straight away

    for (int i = 0; i < (int)strlen(str); ++i)
    {
        // if the * character is found within the string
        if (*(str + i) == '*')
            return true;
    }
    // the * character hasn't been found
    return false;
}

bool check_context(concordance obj1, concordance obj2)
{
    char *upper, *lower;
    int u, l;
    u = l = 0;

    while (!is_word(obj1.context[l]))
        l++;
    while (!is_word(obj2.context[u]))
        u++;

    // as long as lower isn't below 0, we can decrement both numbers and compare
    while (u > 0 && l > 0)
    {
        u--;

        lower = obj1.context[l];
        upper = obj2.context[u];
        if (is_word(lower))
            lower++; // ignore * character
        if (is_word(upper))
            upper++; // "				   "

        if (strcmp(lower, upper) != 0)
            return false; // if the two strings are different
        else
            l--;
    }
    // if this point is reached, the contexts are the same
    return true;
}
