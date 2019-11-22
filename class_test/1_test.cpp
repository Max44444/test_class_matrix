#include <iostream>
#include <ctime>
#define TEST

using namespace std;

class Matrix
{
private:
       int length;
       int width;
       int** matrix;
public:
       //===================*CONSTRUCTOR*========================
       
       Matrix(int length, int width)
       {
               cout << "Викликано конструктор\t" << this << endl;
               this->length = length; 
               this->width = width;
               matrix = new int*[length];

               for(int i = 0; i < length; i++)
               {
                       matrix[i] = new int[width];
               }
       }

       Matrix(const Matrix &other)
       {
               cout << "Викликано конструктор копіювання\t" << this << endl;
               this->length = other.length;
               this->width = other.width;
               this->matrix = new int*[other.length];
               for(int i = 0; i < other.length; i++)
               {
                       this->matrix[i] = new int[other.width];
               }
               for(int i = 0; i < other.length; i++)
               {
                       for(int j = 0; j < other.width; j++)
                       {
                               this->matrix[i][j] = other.matrix[i][j];
                       }
               }
       }

       //====================*SIZE*==================================
       
       int mwidth()
       {
               return width;
       }

       int mlength()
       {
               return length;
       }

       //===================*FILLING*================================

       void random(int from, int before)
       {
               srand(time(NULL));
               if(from > before) swap(from, before); 
               for(int i = 0; i < length; i++)
               {
                       for(int j = 0; j < width; j++) matrix[i][j] = rand() % (before - from + 1) + from;
               }
       }

       void input(int i_1, int j_1, int i_2, int j_2)
       {
               i_1--;
               j_1--;
               i_2--;
               j_2--;
               do
               {
                       cin >> matrix[j_1][i_1];
                       i_1++;

                       if(i_1 == width)
                       {
                               i_1 = 0;
                               j_1++;
                       }

                       if(i_1 == i_2 && j_1 == j_2) cin >> matrix[j_1][i_1];
               } while(i_1 != i_2 || j_1 != j_2);
       }

       //===================*OUTPUT*=================================

       void print()
       {
               for(int i = 0; i < length; i++)
               {
                       for(int j = 0; j < width; j++) cout << matrix[i][j] << '\t';
                       cout << endl;
               }
       }

       //==================*DESTRUCTOR*============================

       ~Matrix()
       {
               cout << "Викликано деструктор\t" << this << endl;
               delete[] matrix;
       }
};

int main()
{
        Matrix a(4, 4);
        a.input(1, 1, 2, 2);
        a.print();
        Matrix b = a;
        return 0;
}
