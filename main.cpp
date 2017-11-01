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
//    int get_cardinality() { return cardinality; }
    Object_array(); //конструктор по умолчанию
    Object_array(char); //конструктор по тегу
    Object_array(const Object_array &); //конструктор копии
    Object_array(Object_array &&); //конструктор копии с переносом
    ~Object_array() {   delete[] array;   } //деструктор
};




struct node {
    char symb;
    node *next;
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
//    ~Object_list(); //деструктор
};


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
//    std::cout << tag << " = ";
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

//    Object_list A('A'), B('B'), C('C'), D('D'), E;
//    A.show_list();
//    B.show_list();
//    C.show_list();
//    E = (A / B) & (D | C);
//    E.show_list();
//
//    Object_list A('A'), B('B');
//    A.display();
//    B.display();
//    Object_list C;
//    C = (A & B) | B;
//    C.display();

    clock_t start, end;

    Object_list A1('A'), B1('B'), C1('C'), D1('D'), E1;
    E1 = (A1 & ~B1) & (C1 | D1);
    std::cout << "List ";       E1.display();
    Object_list res1;
    start = clock();
    for (int i = 0; i < duration; i++) {
        res1 = (A1 & ~B1) & (C1 | D1);
    }
    end = clock();
    std::cout << "List time = " << end - start << std::endl;



    Object_array A2('A'), B2('B'), C2('C'), D2('D'), E2;
    E2 = (A2 & ~B2) & (C2 | D2);
    std::cout << "Array ";     E2.display();

    start = clock();
    Object_array res2;
    for (int i = 0; i < duration; i++) {
        res2 = (A2 & ~B2) & (C2 | D2);
    }
    end = clock();
    std::cout << "Array time = " << end - start << std::endl;





    return 0;
}






//class Object_list
//{
//private:
//    char symb;
//    Object_list* next;
//public:
//    Object_list() {}
//    Object_list(char s, Object_list* n = nullptr) : symb(s), next(n) {  std::cout << "+" << symb << std::endl;    }
//    ~Object_list() {
//        if (next) {
//            delete next;
//        }
//        std::cout << "-" << symb << std::endl;
//    }
//
//
//};

//
//
//class Object_node
//{
//private:
//    char symb;
////    Object_node* next;
//
//public:
//    Object_node* next;
//    char get_symb() {   return symb;    }
//
//    void set_next(Object_node* new_next) {
//        next = new_next;
//    }
//
//    Object_node* to_next(Object_node* link) {
//        if(link != nullptr) {
//            if(link != this) {
//                std::cout << "Указатель \"Link\" не связан с текущим объектом типа \"Object_node\"" << std::endl;
//            } else {
//                link = link->next;
//            }
//        } else {
//            std::cout << "Указатель \"Link\" пуст" << std::endl;
//        }
//        return link;
//    }
//
//    Object_node() : symb('0'), next(nullptr) {}
//
//    Object_node(char s, Object_node* n) : symb(s), next(n) {}
//
//    void show_node() {
//        std::cout << symb << std::endl;
//    }
//
//};
//
//class Object_list
//{
//    friend class Object_node;
//private:
//    static int UNIVERSE_POWER;
//    Object_node* head;
//    char tag;
//public:
//
//    Object_node* get_head() {   return head;  }
//
//    void set_head(Object_node* new_head) {
//        if (new_head != nullptr) {
//            head = new_head;
//        } else {
//            std::cout << "Обнуление головы! Возможна утечка памяти!" << std::endl;
//            head = nullptr;
//        }
//    }
//
//    void show_list() {
//        if (head != nullptr) {
//            Object_node* link = head;
//            do {
//                link->show_node();
//                link = link->to_next(link);
//            } while (link != nullptr);
//        } else {
//            std::cout << "Список пуст" << std::endl;
//        }
//        std::cout << "Вывод завершен" << std::endl;
//    }
//
//
//
//    //прописать конструкторы по тегу и тд
//    Object_list() : tag('0') {
//        head =  new Object_node();
//    }
//
//    Object_list(char tag) {
//        //0 лишний создается всегда-исправить
//        head = nullptr;
//        for (int i = UNIVERSE_POWER - 1; i >= 0; i--) {
//            if(rand() % 2) {
//                Object_node *link = head;
//                head = new Object_node((char)(i + '0'), link);
////                head->set_next(link);
//            }
//        }
//    }
//
//    Object_list(Object_node* new_head) {
//        if (new_head != nullptr) {
//            head = new_head;
//        } else {
//            std::cout << "Указатель пуст!" << std::endl;
//        }
//    }
//
//
//    Object_list operator & (Object_list & B) const {
//        Object_node *E = nullptr;
//        Object_node *tA = head, *tB;
//        for (char x; tA != nullptr; tA = tA->to_next(tA)) {
//            x = tA->get_symb();
//            tB = B.get_head();
//            for (char y; tB != nullptr; tB = tB->to_next(tB)) {
//                y = tB->get_symb();
//                if (x == y)
//                    E = new Object_node(x, E);
//            }
//        }
//        return Object_list(E);
//    }
//
//    Object_list operator | (Object_list & B) const {
//        Object_node *E = B.get_head();
//        Object_node *tA = head, *tB;
//        for (char x; tA != nullptr; tA = tA->to_next(tA)) {
//            x = tA->get_symb();
//            tB = E;
//            bool f = true;
//            for (char y; tB != nullptr; tB = tB->to_next(tB)) {
//                y = tB->get_symb();
//                if (x == y)
//                    f = false;
//            }
//            if (f) {
//                E = new Object_node(x, E);
//            }
//        }
//        return Object_list(E);
//    }
//
//    Object_list operator / (Object_list &B) const {
//        Object_node *E = nullptr;
//        Object_node *tA = head, *tB;
//        for (char x; tA != nullptr; tA = tA->to_next(tA)) {
//            x = tA->get_symb();
//            tB = B.get_head();
//            bool f = true;
//            for (char y; tB != nullptr; tB = tB->to_next(tB)) {
//                y = tB->get_symb();
//                if (x == y)
//                    f = false;
//            }
//            if (f)
//                E = new Object_node(x, E);
//        }
//        return Object_list(E);
//    }
//
//    Object_list operator = (Object_list &&B) {
//        if (this != &B) {
//            head = B.get_head();
//            B.head = nullptr;
//        }
//    }
//
//};
//
//
//
