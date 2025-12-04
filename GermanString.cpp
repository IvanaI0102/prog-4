#include <bits/stdc++.h>
using namespace std;


class GermanString {
private:
    char* text;
    int32_t size;
    char* prefix;

public:
    GermanString() {
        size = 0;
        text = nullptr;
        prefix = nullptr;
    } 

    GermanString(const char* str) {
        if (str) {
            size = strlen(str);

            if(size <= 12)
            {
                text = new char[size + 1];
                prefix = new char[5];

                for (int i = 0; i < size; i++) 
                text[i] = str[i];

                text[size] = '\0';

                for(int i=0; i<min(4,size); i++)
                prefix[i]=str[i];

                prefix[min(4,size)] = '\0';
            }
            else
            {
                text = new char[size + 1];
                prefix = nullptr;

                for (int i = 0; i < size; i++) 
                text[i] = str[i];

                text[size] = '\0';

            }

        
        
        } 
        else {
            text = nullptr;
            prefix = nullptr;
            size = 0;
        }
    }

    GermanString(const GermanString& other) {
        size = other.size;
        if (size > 0) {
            text = new char[size + 1];
             for (int i = 0; i < size; i++) 
                text[i] = other.text[i];

               text[size]='\0';

            if(size<=12)
            {
            prefix = new char [5];
           

            for (int i = 0; i < min(4,size); i++) 
                prefix[i] = other.prefix[i];

         
            prefix[min(4,size)] = '\0';}
            else
            {
                prefix = nullptr;
            }
        }
        else {
            text = nullptr;
            prefix = nullptr;
        }
    }


    GermanString& operator=(const GermanString& other) {
        if (this == &other) return *this;

        delete[] text;
        delete [] prefix;
        size = other.size;

        if (size > 0) {
            text = new char[size + 1];
            for (int i = 0; i < size; i++) 
                text[i] = other.text[i];
            
             text[size]='\0';

            if(size<=12)
            {
            prefix = new char [5];
            

            for (int i = 0; i < 4; i++) 
                prefix[i] = other.prefix[i];

           
            prefix[min(4,size)] = '\0';}
            else
            {
                prefix = nullptr;
            }
        }
        else {
            text = nullptr;
            prefix = nullptr;
        }

        return *this;
    }

    ~GermanString() {
        delete[] text;

        if(prefix)
        delete[] prefix;
    }

    int size_of() const
    {
        return size;
    }

    void print()
    {
        for (int i = 0; i < size; i++) 
            cout << text[i];

        cout << '\n';
    }

    void empty()
    {
        size = 0;
        delete [] text;

        text = nullptr;

        if(prefix)
        delete [] prefix;

        prefix = nullptr;
    }

    const char& operator[](int index) const {
        
    
        return text[index];
    

    }

int find(char c) const {
    if (!text || size == 0) {
        return -1;
    }
    
    for (int i = 0; i < size; ++i) {
        if (text[i] == c) {
            return i;
        }
    }
    
    return -1; 
}

char& operator[](int index) {
        return text[index]; 
}

    

};

   
    




 GermanString operator+(const GermanString& one, const GermanString& other) {

    int old_size = one.size_of();
    int new_size = old_size + other.size_of();
    
    char* new_text = new char[new_size + 1];
    
    for (int i = 0; i < old_size; i++) {
        new_text[i] = one[i];
    }
    
    for (int i = 0; i < other.size_of(); i++) {
        new_text[old_size + i] = other[i];
    }
    
    new_text[new_size] = '\0';

    GermanString newobject(new_text);

    delete [] new_text;
    
    return newobject;
}




int main()
{
    GermanString s("Negotino ");
    GermanString k("Makedonija");

    cout << s.size_of();
    cout << endl;

    s.print();

    cout << s[1];

    cout << endl;

    s[1] = 'p';

    cout << s[1];

    cout << endl;
    char f = 'a';
    cout << s.find(f);

    cout << endl;

    GermanString c = s+k;

    c.print();

    return 0;
}