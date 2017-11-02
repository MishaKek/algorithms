#include <iostream>

const int duration = 100000;




class Object_array
{
private:
    //Мощность универсума
    static int UNIVERSE_POWER;
    //Мощность множества
    int cardinality;
    //Тег и память для множества
    char tag, *array;
public:
    Object_array operator | (const Object_array&) const;
    Object_array operator & (const Object_array&) const;
    Object_array operator ~ () const;
    Object_array operator = (const Object_array &); //оператор присваивания
    Object_array operator = (Object_array &&);  //оператор присваивания с переносом
    void display(); //вывод на экран
    int get_cardinality() { return cardinality; }
    Object_array(); //конструктор по умолчанию
    Object_array(char); //конструктор по тегу
    Object_array(const Object_array &); //конструктор копии
    Object_array(Object_array &&); //конструктор копии с переносом
    ~Object_array() {   delete[] array;   } //деструктор
};




struct node {
    char symb;
    node *next;
    ~node() {   if(next) delete next;   }
};

class Object_list {
private:
    //Мощность универсума
    static int UNIVERSE_POWER;
    node *head;
    char tag;
public:
    Object_list operator | (const Object_list&) const;
    Object_list operator & (const Object_list&) const;
    Object_list operator ~ () const;
    Object_list operator = (const Object_list &); //оператор присваивания
    Object_list operator = (Object_list &&);  //оператор присваивания с переносом

    void display(); //вывод на экран
    Object_list();  //конструктор по умолчанию
    Object_list(char);  //конструктор по тегу
    Object_list(const Object_list &);  //конструктор копии
    Object_list(Object_list &&);    //конструктор копии с переносом
};



class Object_barray {
private:
    //Мощность универсума
    static int UNIVERSE_POWER;
    //Тег
    char tag;
    bool *bArray;
public:
    Object_barray operator | (const Object_barray &) const;
    Object_barray operator & (const Object_barray &) const;
    Object_barray operator ~ () const;
    Object_barray operator = (const Object_barray &);
    Object_barray operator = (Object_barray &&);
    void display();
    Object_barray();
    Object_barray(char);
    Object_barray(const Object_barray &);
    Object_barray(Object_barray &&);
    ~Object_barray() {  std::cout << "OK" << std::endl;
        delete [] bArray;    }
};

int Object_barray::UNIVERSE_POWER = 10;

void Object_barray :: display() {
    std::cout << this->tag << " =[";
    for (int i = 0; i < UNIVERSE_POWER; i++)
        std::cout << this->bArray[i];
    std::cout << "]" << std::endl;
}

Object_barray::Object_barray(): tag('0'), bArray(new bool[UNIVERSE_POWER]) {
    bArray[0] = 0;
}

Object_barray::Object_barray(char symb): tag(symb), bArray(new bool[UNIVERSE_POWER])  {
    for (int i = 0; i < UNIVERSE_POWER; i++) {
        bArray[i] = (rand() % 1024 >> i) & 1;
    }
    this->display();
}

Object_barray::Object_barray(const Object_barray & B): tag(B.tag), bArray(new bool[UNIVERSE_POWER]) {
    memcpy(bArray, B.bArray, (size_t)UNIVERSE_POWER);
}

Object_barray::Object_barray(Object_barray &&B) : tag(B.tag), bArray(B.bArray) {
    B.bArray = nullptr;
}

Object_barray Object_barray::operator&(const Object_barray &B) const {
    Object_barray *result = new Object_barray(*this);
    for (int i = 0; i < UNIVERSE_POWER; i++) {
        if (this->bArray[i] == B.bArray[i])
            (*result).bArray[i] = this->bArray[i];
        else
            (*result).bArray[i] = 0;
    }
    return *result;
}

Object_barray Object_barray::operator|(const Object_barray &B) const {
    Object_barray *result = new Object_barray(*this);
    for (int i = 0; i < UNIVERSE_POWER; i++) {
        if (this->bArray[i] || B.bArray[i])
            result->bArray[i] = 1;
        else result->bArray[i] = 0;
    }
    return *result;
}

Object_barray Object_barray::operator~() const {
    for (int i = 0; i < UNIVERSE_POWER; i++)
        bArray[i] = !bArray[i];
    return *this;
}

Object_barray Object_barray::operator=(const Object_barray &B) {
    if (this != &B) {
        bArray = B.bArray;
        memcpy(bArray, B.bArray, (size_t)UNIVERSE_POWER);
        tag = 'E';
    }
    return *this;
}

Object_barray Object_barray::operator = (Object_barray &&B) {
    if (this != &B) {
        bArray = B.bArray;
        tag = 'R'; //result
        B.bArray = nullptr;
        return *this;
    }
}




int Object_array :: UNIVERSE_POWER = 10;
int Object_list :: UNIVERSE_POWER = 10;


Object_array Object_array ::operator&(const Object_array & B) const {
    Object_array* set = new Object_array;
    for (int i = 0; i < cardinality; i++) {
        for (int j = 0; j < B.cardinality; j++) {
            if (array[i] == B.array[j]) {
                set->array[set->cardinality++] = array[i];
            }
        }
    }
    set->array[set->cardinality] = 0;
    return *set;
}

Object_array Object_array ::operator|(const Object_array & B) const {
    Object_array* set = new Object_array(*this);
    for (int i = 0; i < B.cardinality; i++) {
        bool flag = true;
        for (int j = 0; j < cardinality; j++) {
            if(B.array[i] == array[j]) {
                flag = false;
            }
        }
        if(flag) {
            set->array[set->cardinality++] = B.array[i];
        }
    }
    set->array[set->cardinality] = 0;
    return *set;
}

Object_array Object_array ::operator~() const {
    Object_array* set = new Object_array;
    for (char ch = '0'; ch <= '9'; ch++) {
        bool flag = true;
        for (int j = 0; j < cardinality; j++) {
            if (ch == array[j]) {
                flag = false;
                break;
            }
        }
        if(flag) {
            set->array[set->cardinality++] = ch;
        }
    }
    set->array[set->cardinality] = 0;
    return *set;
}

void Object_array :: display() {
    std::cout << tag << " = [" << array << "]" << std::endl;
}

Object_array::Object_array(): cardinality(0), tag('0'), array(new char[UNIVERSE_POWER + 1]) {
    array[0] = 0;
}

Object_array::Object_array(char symb): tag(symb), cardinality(0), array(new char[UNIVERSE_POWER + 1]) {
    for (int i = 0; i < UNIVERSE_POWER; i++) {
        if(rand() % 2) {
            array[cardinality++] =(char) (i +'0');
        }
    }
    array[cardinality] = 0;
    std::cout << tag << " =[" << array << "]" << std::endl;
}

Object_array::Object_array(const Object_array & B): tag(B.tag), cardinality(B.cardinality), array(new char[UNIVERSE_POWER + 1]) {
    memcpy(array, B.array, (size_t)UNIVERSE_POWER + 1);
}

Object_array Object_array :: operator = (const Object_array& B) {
    if(this != &B) {
        cardinality = B.cardinality;
        memcpy(array, B.array, (size_t)UNIVERSE_POWER + 1);
        tag = 'E';//result
    }
    return *this;
}

Object_array::Object_array(Object_array &&B) : tag(B.tag), cardinality(B.cardinality), array(B.array) {
    B.array = nullptr;
}

Object_array Object_array::operator = (Object_array &&B) {
    if (this != &B) {
        cardinality = B.cardinality;
        array = B.array;
        tag = 'R'; //result
        B.array = nullptr;
        return *this;
    }
}




Object_list Object_list :: operator | (const Object_list &B) const {
    node *tA = head, *tB, *E = B.head;
    node *link = nullptr;
    for (char x; tA != nullptr; tA = tA->next) {
        x = tA->symb;
        tB = B.head;
        bool f = true;
        for (char y; tB != nullptr; tB = tB->next) {
            y = tB->symb;
            if (x == y)
                f = false;
        }
        if (f) {
            link = E;
            E = new node;
            E->symb = x;
            E->next = link;
        }
    }
    Object_list A;
    A.head = E;
    return A;
}

Object_list Object_list :: operator & (const Object_list &B) const {
    node *E = nullptr;
    node *tA = head, *tB;
    node *link = nullptr;
    for (char x; tA != nullptr; tA = tA->next) {
        x = tA->symb;
        tB = B.head;
        for (char y; tB != nullptr; tB = tB->next) {
            y = tB->symb;
            if (x == y) {
                link = E;
                E = new node;
                E->symb = x;
                E->next = link;
            }
        }
    }
    Object_list A;
    A.head = E;
    return A;
}

Object_list Object_list :: operator ~ () const {
    node *main_head = nullptr;
    node *link = main_head;
    node *nhead = head;
    for (int i = UNIVERSE_POWER - 1; i >= 0; i--) {
        node *link = main_head;
        nhead = head;
        bool flag = true;
        for (; nhead != nullptr; nhead = nhead->next) {
            if (nhead->symb == (i + '0'))
                flag = false;
        }
        if (flag) {
            main_head = new node;
            main_head->symb = (char) (i + '0');
            main_head->next = link;
        }
    }
    Object_list A;
    A.head = main_head;
    return A;
}

Object_list Object_list :: operator = (const Object_list &B) {

    if  (this != &B) {
        tag = B.tag;
        node *nhead = new node;
        nhead->next = nullptr;
        node *bhead = B.head;
        for (node *nlink = nhead; bhead != nullptr; bhead = bhead->next) {
            nlink->symb = bhead->symb;
            nlink->next = new node;
            nlink = nlink->next;
            nlink->next = nullptr;
        }

        this->head = nhead;
    }
    return *this;
}

Object_list Object_list :: operator = (Object_list &&B) {
    if (this != &B) {
        head = B.head;
        tag = 'R';
        B.head = nullptr;
        return *this;
    }
}

void Object_list ::display() {
    if (head != nullptr) {
        std::cout << tag << " = [";
        node *link = head;
        while (link != nullptr) {
            std::cout << link->symb;
            link = link->next;
        }
        std::cout << "]" << std::endl;
    } else {
        std::cout << "Список пуст" << std::endl;
    }
}

Object_list :: Object_list() : tag('0') {
    head = nullptr;
}

Object_list ::Object_list(char t) : tag(t) {
    head = nullptr;
    node *link = head;
    for (int i = UNIVERSE_POWER - 1; i >= 0; i--) {
        if (rand() % 2) {
            node *link = head;
            head = new node;
            head->symb = (char)(i + '0');
            head->next = link;
        }
    }
    this->display();
}

Object_list::Object_list(const Object_list &B): tag(B.tag) {
    node *nhead = nullptr;
    if (B.head != nullptr) {
        nhead = new node;
        nhead->next = nullptr;
        node *bhead = B.head;
        node *nlink = nhead;
        for (; bhead->next != nullptr; bhead = bhead->next) {
            nlink->symb = bhead->symb;
            nlink->next = new node;
            nlink = nlink->next;
        }
        nlink->symb = bhead->symb;
        nlink->next = nullptr;
    }
    head = nhead;
}

Object_list ::Object_list(Object_list &&B) : tag(B.tag), head(B.head) {
    B.head = nullptr;
}




int main() {
    std::cout << "Hello, World!" << std::endl;
    srand(time(nullptr));
    clock_t start, end;



    //объект-список
//    Object_list A1('A'), B1('B'), C1('C'), D1('D'), E1;
//    E1 = (A1 & ~B1) & (C1 | D1);
//    std::cout << "List ";
//    E1.display();
//    Object_list res1;
//    start = clock();
//    for (int i = 0; i < duration; i++) {
//        res1 = (A1 & ~B1) & (C1 | D1);
//    }
//    end = clock();
//    std::cout << "List time = " << end - start << std::endl;



    //объект-массив
//    Object_array A2('A'), B2('B'), C2('C'), D2('D'), E2;
//    E2 = (A2 & ~B2) & (C2 | D2);
//    std::cout << "Array ";
//    E2.display();
//
//    start = clock();
//    Object_array res2;
//    for (int i = 0; i < duration; i++) {
//        res2 = (A2 & ~B2) & (C2 | D2);
//    }
//    end = clock();
//    std::cout << "Array time = " << end - start << std::endl;




    //объект массив битов
    Object_barray A3('A'), B3('B'), C3('C'), D3('D'), E3;
    E3 = (A3 & ~B3) & (C3 | D3);
    std::cout << "Bool Array ";
    E3.display();

    start = clock();
    Object_barray res3;
    for (int i = 0; i < duration; i++) {
        res3 = (A3 & ~B3) & (C3 | D3);
    }
    end = clock();
    std::cout << "Bool Array time = " << end - start << std::endl;

    return 0;
}

